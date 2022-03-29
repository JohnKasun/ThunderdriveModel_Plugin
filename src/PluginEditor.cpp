#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), 
      processorRef (p), 
      mValueTreeState(vts)
{


    mGainLabel.setText("Gain", juce::dontSendNotification);
    addAndMakeVisible(mGainLabel);

    addAndMakeVisible(mGainSlider);
    mGainAttachment.reset(new SliderAttachment(mValueTreeState, "gain", mGainSlider));

    setSize(paramSliderWidth + paramLabelWidth, juce::jmax(100, paramControlHeight * 2));

}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto r = getLocalBounds();

    auto gainRect = r.removeFromTop(paramControlHeight);
    mGainLabel.setBounds(gainRect.removeFromLeft(paramLabelWidth));
    mGainSlider.setBounds(gainRect);

}

