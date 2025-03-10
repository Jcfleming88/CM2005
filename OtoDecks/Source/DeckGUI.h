#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

class DeckGUI : 
    public juce::Component, 
    public juce::Button::Listener,
    public juce::Slider::Listener,
    public juce::Timer
{
public:
	/** Constructor for the Deck GUI component */
    DeckGUI(
		int _id,
        DJAudioPlayer* _djAudioPlayer,
		juce::AudioFormatManager& formatManager,
		juce::AudioThumbnailCache& thumbnailCache
    );

	/** Destructor for the Deck GUI component */
    ~DeckGUI() override;

	// Drawing and Resizing
    void paint (juce::Graphics&) override;
    void resized() override;

    void loadURL(juce::URL audioURL);

private:
    // Variables
    int id;

    // Components
    juce::TextButton playButton{ "Play" };
    juce::TextButton loadButton{ "Load" };

    juce::Slider volumeSlider;
    juce::Slider positionSlider;
    juce::Slider speedSlider;

	WaveformDisplay waveformDisplay;

    // Player
    DJAudioPlayer* player;

	// Listners & Callbacks6
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
	void timerCallback() override;

    // States
	bool isPlaying = false;

	// Functions
	void playTrack();
	void stopTrack();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
