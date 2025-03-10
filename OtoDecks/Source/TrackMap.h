#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "TrackInfo.h"
#include "TrackSettings.h"

class TrackMap : 
    public juce::Component,
    public juce::TableListBoxModel,
    public juce::Button::Listener
{
public:
    TrackMap(
        std::vector<TrackInfo>& aTracks,
        TrackSettings& ts
    );
    ~TrackMap() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    int getNumRows() override;
    void paintRowBackground(
        juce::Graphics& g,
        int rowNumber,
        int width,
        int height,
        bool rowIsSelected
    ) override;
    void paintCell(
        juce::Graphics& g,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected
    ) override;
    juce::Component* refreshComponentForCell(
        int rowNumber,
        int columnId,
        bool isRowSelected,
        juce::Component* componentToUpdate
    ) override;

	void updateMap(double newTime);

private:

    juce::TableListBox table;

    /** Instance of the TrackSettings used to control the settings for the selected row */
    TrackSettings& trackSettings;

    /** The tracks currently showing in the TrackMap */
    std::vector<TrackInfo>& selectedTracks;

    /** The ratio of seconds to pixels, used to draw images correctly */
    int scale = 3;

    /** The number of seconds into the currently playing track */
    double time = 0;

    /** Draws the scale seen on the top of the TrackMixer */
    void drawScale(juce::Graphics& g, int width, int height);

    /** Draws a bar for the track based on the track info and element dimensions */
    void drawTrack(juce::Graphics& g, int width, int height, TrackInfo track);

    /** Button used to trigger a track removal */
    juce::TextButton removeButton{ "Remove Track" };

    // Event Listners
    void selectedRowsChanged(int lastRowSelected) override;
    void buttonClicked(juce::Button* button) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackMap)
};
