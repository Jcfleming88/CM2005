#pragma once

#include "JuceHeader.h"
#include "../JuceLibraryCode/JuceHeader.h"

class DJAudioPlayer : 
    public juce::AudioSource
{
private:
    juce::AudioFormatManager& formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
	juce::ResamplingAudioSource resamplingSource{ &transportSource, false, 2 };

public:
    /** Constructor for the DJ Audio Player component */
    DJAudioPlayer(juce::AudioFormatManager& audioFormatManager);

	/** Destructor for the DJ Audio Player component */
    ~DJAudioPlayer();

	/** Load a file from a URL */
    void loadURL(juce::URL file);

	/** Play the audio file */
    void play();

	/** Stop the audio file */
    void stop();

    /** Check if the player has a track loaded */
    bool hasTrack();

    /** Gets the length of the track in seconds */
    double getTrackLength();

    /** get the relative position of the play head */
    double getPositionRelative();

    /** Gets the next audio block to be paid */
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

	/** Prepare the player to play */
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    /** Set the gain of the audio file */
    void setGain(double gain);

	/** Set the position of the audio file */
    void setPosition(double posInSecs);

	/** Set the position of the audio file using a number between 0 and 1 */
	void setPositionRelative(double pos);

	/** Set the speed of the audio file */
	void setSpeed(double speed);

	/** Release the resources of the player */
    void releaseResources() override;
};