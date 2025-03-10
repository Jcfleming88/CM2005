#pragma once

#include <JuceHeader.h>
#include <string>
#include "DJAudioPlayer.h"

class TrackInfo
{
public:
    TrackInfo(std::string trackPath);
	~TrackInfo();

    // File Info
    /** The filepath for the sound file */
    std::string filePath;

    /** The name of the file */
    std::string title;

    /** The duration of the sound file. Will default to zero if it can't be loaded */
    double duration = 0;

    // Track Settings
    /** The time at which the track will start to play */
    double startTime = 0;

    /** The gain of the track, used to control the volume */
    double gain = 0.5;

    /** The speed at which the track will be played */
    double speed = 1;

    /** The colour of the track as shown in the TrackMap */
	juce::Colour colour;

    // States
    /** Used to show if there's a track loaded or not */
	bool isNull = false;

    /** Indicats if the track has started playing in the TrackMixer */
    bool hasStarted = false;

    /** Indicated if the track has stopped playing in the TrackMixer */
    bool hasEnded = false;

private:
    /** Used to find the filename from a file path */
	std::string getFileName(std::string filePath);
};