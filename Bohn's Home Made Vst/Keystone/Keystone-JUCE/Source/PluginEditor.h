#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"

class KeystoneEditor : public juce::AudioProcessorEditor
{
public:
    explicit KeystoneEditor (KeystoneProcessor&);
    ~KeystoneEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    struct Knob
    {
        juce::Slider slider;
        juce::Label  label;
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attach;
    };
    void addKnob (Knob&, const juce::String& paramID, const juce::String& text);

    KeystoneProcessor& proc;
    juce::ComboBox presetBox;
    juce::Label    titleLabel, envLabel;
    std::array<Knob, 8> knobs;

    struct Preset { const char* name; float w, h, d, absorb, round; };
    std::array<Preset, 7> presets {{
        { "King's Chamber",       5.23f, 5.81f, 10.47f, 0.03f, 0.05f },
        { "Queen's Chamber",      5.23f, 6.26f,  5.75f, 0.04f, 0.10f },
        { "Grand Gallery",        2.06f, 8.60f, 46.70f, 0.04f, 0.15f },
        { "Subterranean Chamber", 8.00f, 3.50f, 14.00f, 0.08f, 0.20f },
        { "Oracle Room",          3.50f, 2.50f,  5.00f, 0.05f, 0.30f },
        { "Newgrange Chamber",    6.00f, 6.00f,  6.00f, 0.06f, 0.55f },
        { "Hagia Sophia",        31.00f,55.00f, 70.00f, 0.06f, 0.70f },
    }};
    void applyPreset (int index);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeystoneEditor)
};
