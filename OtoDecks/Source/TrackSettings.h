#pragma once

#include <JuceHeader.h>
#include "TrackInfo.h"

/** Used to change the settings for the selected track in the TrackMap */
class TrackSettings  : 
    public juce::Component,
    public juce::Slider::Listener
{
public:
    TrackSettings();
    ~TrackSettings() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void updateContent();

    /** The currently selected track */
    TrackInfo* selectedTrack = NULL;

private:

    // Labels on the settings
    juce::Label trackName{ "trackName", "Unknown" };
    juce::Label startLabel{ "trackStart", "Start Time" };
    juce::Label volumeLabel{ "trackVolume", "Volume" };
    juce::Label speedLabel{ "trackSpeed", "Speed" };

    // Sliders for controlling the settings
    juce::Slider startSlider;
    juce::Slider volumeSlider;
    juce::Slider speedSlider;

    // Event Listener
    void sliderValueChanged(juce::Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackSettings)
};
