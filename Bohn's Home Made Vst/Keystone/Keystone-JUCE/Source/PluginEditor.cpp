#include "PluginEditor.h"

KeystoneEditor::KeystoneEditor (KeystoneProcessor& p)
    : AudioProcessorEditor (&p), proc (p)
{
    titleLabel.setText ("KEYSTONE  \xC2\xB7  Geo-Verb", juce::dontSendNotification);
    titleLabel.setFont (juce::Font (22.0f, juce::Font::bold));
    titleLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (titleLabel);

    envLabel.setText ("Now entering an environment", juce::dontSendNotification);
    envLabel.setJustificationType (juce::Justification::centred);
    envLabel.setColour (juce::Label::textColourId, juce::Colours::grey);
    addAndMakeVisible (envLabel);

    for (auto& pr : presets) presetBox.addItem (pr.name, presetBox.getNumItems() + 1);
    presetBox.setSelectedId (1, juce::dontSendNotification);
    presetBox.onChange = [this] { applyPreset (presetBox.getSelectedId() - 1); };
    addAndMakeVisible (presetBox);

    const char* ids[8]  = { "size","width","height","depth","round","absorb","proj","mix" };
    const char* text[8] = { "Size","Width","Height","Depth (Breath)","Roundness","Absorption","Projection","Mix" };
    for (int i = 0; i < 8; ++i) addKnob (knobs[(size_t) i], ids[i], text[i]);

    setSize (560, 420);
}

void KeystoneEditor::addKnob (Knob& k, const juce::String& paramID, const juce::String& text)
{
    k.slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    k.slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 70, 16);
    addAndMakeVisible (k.slider);
    k.label.setText (text, juce::dontSendNotification);
    k.label.setJustificationType (juce::Justification::centred);
    k.label.setFont (juce::Font (12.0f));
    addAndMakeVisible (k.label);
    k.attach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
                   (proc.apvts, paramID, k.slider);
}

void KeystoneEditor::applyPreset (int index)
{
    if (index < 0 || index >= (int) presets.size()) return;
    const auto& pr = presets[(size_t) index];
    auto set = [this] (const char* id, float v)
    {
        if (auto* p = proc.apvts.getParameter (id))
            p->setValueNotifyingHost (proc.apvts.getParameterRange (id).convertTo0to1 (v));
    };
    set ("size", 1.0f);
    set ("width",  pr.w);
    set ("height", pr.h);
    set ("depth",  pr.d);
    set ("absorb", pr.absorb);
    set ("round",  pr.round);
    envLabel.setText (juce::String ("Now entering: ") + pr.name, juce::dontSendNotification);
}

void KeystoneEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour (0xff14110c));
    g.setColour (juce::Colour (0xffd9a534).withAlpha (0.15f));
    g.drawRect (getLocalBounds().reduced (6), 1);
}

void KeystoneEditor::resized()
{
    auto r = getLocalBounds().reduced (14);
    titleLabel.setBounds (r.removeFromTop (30));
    envLabel.setBounds   (r.removeFromTop (20));
    presetBox.setBounds  (r.removeFromTop (30).reduced (60, 0));
    r.removeFromTop (10);

    auto grid = r;
    const int cols = 4, rows = 2;
    const int cw = grid.getWidth() / cols;
    const int ch = grid.getHeight() / rows;
    for (int i = 0; i < 8; ++i)
    {
        auto cell = juce::Rectangle<int> (grid.getX() + (i % cols) * cw,
                                          grid.getY() + (i / cols) * ch, cw, ch).reduced (6);
        knobs[(size_t) i].label.setBounds  (cell.removeFromTop (16));
        knobs[(size_t) i].slider.setBounds (cell);
    }
}
