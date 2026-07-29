#include "PluginProcessor.h"
#include "PluginEditor.h"

using APVTS = juce::AudioProcessorValueTreeState;

static juce::AudioProcessorValueTreeState::ParameterLayout
KeystoneProcessor_makeLayout()
{
    using P = juce::AudioParameterFloat;
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> p;
    auto pct   = juce::NormalisableRange<float> (0.0f, 1.0f, 0.001f);
    p.push_back (std::make_unique<P>("size",   "Size",       juce::NormalisableRange<float>(0.3f, 3.0f, 0.01f), 1.0f));
    p.push_back (std::make_unique<P>("width",  "Width",      juce::NormalisableRange<float>(1.0f, 40.0f, 0.1f), 5.23f));
    p.push_back (std::make_unique<P>("height", "Height",     juce::NormalisableRange<float>(1.0f, 60.0f, 0.1f), 5.81f));
    p.push_back (std::make_unique<P>("depth",  "Depth",      juce::NormalisableRange<float>(1.0f, 80.0f, 0.1f), 10.47f));
    p.push_back (std::make_unique<P>("round",  "Roundness",  pct, 0.05f));
    p.push_back (std::make_unique<P>("absorb", "Absorption", juce::NormalisableRange<float>(0.02f, 0.6f, 0.005f), 0.03f));
    p.push_back (std::make_unique<P>("proj",   "Projection", pct, 0.4f));
    p.push_back (std::make_unique<P>("mix",    "Mix",        pct, 0.35f));
    return { p.begin(), p.end() };
}

juce::AudioProcessorValueTreeState::ParameterLayout KeystoneProcessor::createLayout()
{
    return KeystoneProcessor_makeLayout();
}

KeystoneProcessor::KeystoneProcessor()
    : AudioProcessor (BusesProperties()
        .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "PARAMS", createLayout())
{
}

void KeystoneProcessor::prepareToPlay (double sampleRate, int)
{
    engine.prepare (sampleRate);
}

bool KeystoneProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const auto out = layouts.getMainOutputChannelSet();
    if (out != juce::AudioChannelSet::stereo() && out != juce::AudioChannelSet::mono())
        return false;
    return layouts.getMainInputChannelSet() == out;
}

void KeystoneProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    const int numCh = buffer.getNumChannels();
    const int n = buffer.getNumSamples();

    auto g = [this] (const char* id) { return apvts.getRawParameterValue (id)->load(); };
    engine.setParams (g("size"), g("width"), g("height"), g("depth"),
                      g("round"), g("absorb"), g("proj"), g("mix"));

    float* L = buffer.getWritePointer (0);
    float* R = numCh > 1 ? buffer.getWritePointer (1) : nullptr;
    engine.process (L, R, n);
}

juce::AudioProcessorEditor* KeystoneProcessor::createEditor()
{
    return new KeystoneEditor (*this);
}

void KeystoneProcessor::getStateInformation (juce::MemoryBlock& dest)
{
    if (auto state = apvts.copyState(); state.isValid())
        if (auto xml = state.createXml())
            copyXmlToBinary (*xml, dest);
}

void KeystoneProcessor::setStateInformation (const void* data, int size)
{
    if (auto xml = getXmlFromBinary (data, size))
        apvts.replaceState (juce::ValueTree::fromXml (*xml));
}

// Plugin entry point
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KeystoneProcessor();
}
