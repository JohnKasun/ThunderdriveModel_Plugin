#pragma once

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

#include <JuceHeader.h>

class MainComponent : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
