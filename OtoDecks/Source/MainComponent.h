#pragma once

#include "JuceHeader.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"
#include "TrackMixer.h"

/** The main component for running the app */
class MainComponent  : 
    public juce::AudioAppComponent,
	public juce::Button::Listener,
    public juce::Timer
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint (juce::Graphics& g) override;
    void resized() override;

    juce::AudioFormatManager formatManager;

private:

    /** Audio mixer for multiple players */
    juce::MixerAudioSource mixerSource;

    /** Thumbnail cache for the waveform images */
    juce::AudioThumbnailCache thumbnailCache{100};

    /** Button clicked event listener */
	void buttonClicked(juce::Button* button) override;

    /** Timer callback for triggering events */
    void timerCallback() override;

    // Tracks
    /** All tracks loaded into the playlist */
    std::vector<TrackInfo> tracks;

    /** All tracks added to the TrackMixer */
    std::vector<TrackInfo> activeTracks;

    /** All tracks currently being played */
    std::vector<TrackInfo> playingTracks;

    /** Used to show all the tracks currently loaded into the application */
    PlaylistComponent playlist{ tracks, activeTracks, trackMixer, deck1, deck2 };

    /** The TrackMixer component that shows and controlls the track mixing */
    TrackMixer trackMixer{ activeTracks, playingTracks };

    // Buttons
	juce::TextButton addTracks{ "Add Tracks" };
    juce::TextButton playButton{ "Play" };

    // File Chooser Dialog Box
    juce::FileChooser fChooser{ "Select a file..." };

	// Audio Players
    /** Play for Preview Player 1 */
    DJAudioPlayer player1{ formatManager };
    DeckGUI deck1{ 1, &player1, formatManager, thumbnailCache };

    /** Play for Preview Player 2 */
    DJAudioPlayer player2{ formatManager };
    DeckGUI deck2{ 2, &player2, formatManager, thumbnailCache };

    // Various audio players for the TrackMixer
    // Note:- Attempted to create a vector of players, however, this didn't work. As a POC, I created a set number of players.
    DJAudioPlayer player3{ formatManager };
    DJAudioPlayer player4{ formatManager };
    DJAudioPlayer player5{ formatManager };
    DJAudioPlayer player6{ formatManager };
    DJAudioPlayer player7{ formatManager };
    DJAudioPlayer player8{ formatManager };
    DJAudioPlayer player9{ formatManager };
    DJAudioPlayer player10{ formatManager };

    /** States if the TrackMixer is currently playing */
    bool isPlaying = false;

    /** The current time when the TrackMixer is playing */
    double time = 0;

    /** Used to add tracks to specific players */
    void addToPlayer(int index, TrackInfo track);

    /** Used to check if a track should start be started and stopped based on the time */
    void checkTracksPlaying();

    /** Starts a specific player */
    void startPlayer(int index, TrackInfo track);

    /** Stops a specific player */
    void stopPlayer(int index);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};