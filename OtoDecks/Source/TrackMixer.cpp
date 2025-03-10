#include <JuceHeader.h>
#include "TrackMixer.h"

TrackMixer::TrackMixer(
    std::vector<TrackInfo>& aTracks,
    std::vector<TrackInfo>& pTracks
) :
	activeTracks(aTracks),
	playingTracks(pTracks),
    trackMap{ aTracks, trackSettings }
{
	addAndMakeVisible(trackMap);
	addAndMakeVisible(trackSettings);
}

TrackMixer::~TrackMixer()
{
}

void TrackMixer::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("TrackMixer", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void TrackMixer::resized()
{
	trackMap.setBounds(0, 0, getWidth(), getHeight() * 3 / 4);
	trackSettings.setBounds(0, getHeight() * 3 / 4, getWidth() * 7 / 8, getHeight() / 4);
}

void TrackMixer::updateContent(double time)
{
	trackMap.updateMap(time);
}