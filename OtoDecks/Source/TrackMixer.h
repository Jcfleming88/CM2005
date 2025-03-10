#pragma once

#include <JuceHeader.h>
#include "TrackMap.h"
#include "TrackSettings.h"
#include "TrackInfo.h"


class TrackMixer  : 
    public juce::Component
{
public:
    TrackMixer(
        std::vector<TrackInfo>& aTracks, 
        std::vector<TrackInfo>& pTracks
    );
    ~TrackMixer() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void updateContent(double time);

private:

    // Components
    TrackMap trackMap;
    TrackSettings trackSettings;

    // References
	std::vector<TrackInfo>& activeTracks;
	std::vector<TrackInfo>& playingTracks;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackMixer)
};
