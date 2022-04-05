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

    mDriveLabel.setText("Drive", juce::dontSendNotification);
    addAndMakeVisible(mDriveLabel);

    addAndMakeVisible(mDriveSlider);
    mDriveAttachment.reset(new SliderAttachment(mValueTreeState, "drive", mDriveSlider));

    mToneLabel.setText("Tone", juce::dontSendNotification);
    addAndMakeVisible(mToneLabel);

    addAndMakeVisible(mToneSlider);
    mToneAttachment.reset(new SliderAttachment(mValueTreeState, "tone", mToneSlider));

    setSize(paramSliderWidth + paramLabelWidth, juce::jmax(100, paramControlHeight * 3));

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

    auto driveRect = r.removeFromTop(paramControlHeight);
    mDriveLabel.setBounds(driveRect.removeFromLeft(paramLabelWidth));
    mDriveSlider.setBounds(driveRect);

    auto toneRect = r;
    mToneLabel.setBounds(toneRect.removeFromLeft(paramLabelWidth));
    mToneSlider.setBounds(toneRect);

}

