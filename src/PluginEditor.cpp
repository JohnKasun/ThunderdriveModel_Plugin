#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    addAndMakeVisible(mLevelSlider);
    mLevelSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    mLevelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    mLevelSlider.setTextValueSuffix("%");
    mLevelSlider.setRange(0, 100);
    mLevelSlider.addListener(this);

    addAndMakeVisible(mGainSlider);
    mGainSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    mGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    mGainSlider.setTextValueSuffix("%");
    mGainSlider.setRange(0, 100);

    addAndMakeVisible(mLevelLabel);
    mLevelLabel.attachToComponent(&mLevelSlider, false);
    mLevelLabel.setJustificationType(juce::Justification::centred);
    mLevelLabel.setText("Level", juce::NotificationType::dontSendNotification);

    addAndMakeVisible(mGainLabel);
    mGainLabel.attachToComponent(&mGainSlider, false);
    mGainLabel.setJustificationType(juce::Justification::centred);
    mGainLabel.setText("Gain", juce::NotificationType::dontSendNotification);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto area = getBounds().reduced(10);

    auto LevelSliderArea = area.removeFromLeft(getWidth() / 2);
    auto LevelLabelArea = LevelSliderArea.removeFromTop(LevelSliderArea.getHeight() / 4);
    mLevelSlider.setBounds(LevelSliderArea);
    mLevelLabel.setBounds(LevelLabelArea);

    auto GainSliderArea = area;
    auto GainLabelArea = GainSliderArea.removeFromTop(GainSliderArea.getHeight() / 4);
    mGainSlider.setBounds(GainSliderArea);
    mGainLabel.setBounds(GainLabelArea);
}

void AudioPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &mLevelSlider)
        processorRef.mGain = slider->getValue() / 100.0f;
}
