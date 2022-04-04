#pragma once

#include "PluginProcessor.h"

//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:

    enum
    {
        paramControlHeight = 40,
        paramLabelWidth = 80,
        paramSliderWidth = 300
    };

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::AudioProcessorValueTreeState& mValueTreeState;

    juce::Label mGainLabel;
    juce::Slider mGainSlider;
    std::unique_ptr<SliderAttachment> mGainAttachment;

    juce::Label mDriveLabel;
    juce::Slider mDriveSlider;
    std::unique_ptr<SliderAttachment> mDriveAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};