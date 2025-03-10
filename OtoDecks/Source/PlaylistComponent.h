#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "TrackInfo.h"
#include "TrackMixer.h"
#include "DeckGUI.h"

class PlaylistComponent  : 
    public juce::Component,
	public juce::TableListBoxModel,
    public juce::Button::Listener,
    public juce::FileDragAndDropTarget
{
public:
    PlaylistComponent(
        std::vector<TrackInfo>& tracks,
        std::vector<TrackInfo>& activeTracks,
		TrackMixer& mixer,
        DeckGUI& Deck1,
        DeckGUI& Deck2
    );
    ~PlaylistComponent() override;

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

	void buttonClicked(juce::Button* button) override;

    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;

	void updateContent();

private:

	juce::TableListBox table;

    // References
    std::vector<TrackInfo>& allTitles;
    std::vector<TrackInfo>& trackTitles;
	TrackMixer& trackMixer;
    DeckGUI& player1;
    DeckGUI& player2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
