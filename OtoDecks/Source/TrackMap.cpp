#include <JuceHeader.h>
#include "TrackMap.h"

TrackMap::TrackMap(
	std::vector<TrackInfo>& aTracks,
	TrackSettings& ts
) :
	selectedTracks(aTracks),
	trackSettings(ts)
{
	table.getHeader().addColumn("Track Title", 1, 200);
	table.getHeader().addColumn("", 2, 1000);

	table.setHeaderHeight(0);

	table.setModel(this);

	removeButton.addListener(this);

	addAndMakeVisible(table);
	addAndMakeVisible(removeButton);
}

TrackMap::~TrackMap()
{
}

void TrackMap::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);
}

void TrackMap::resized()
{
	table.getHeader().setColumnWidth(2, getWidth() - 200);
    table.setBounds(0, 0, getWidth(), getHeight() - 50);

	removeButton.setBounds(0, getHeight() - 50, getWidth(), 50);
}

int TrackMap::getNumRows()
{
    return selectedTracks.size();
}

void TrackMap::paintRowBackground(
	juce::Graphics& g,
	int rowNumber,
	int width,
	int height,
	bool rowIsSelected)
{
	if (rowIsSelected && rowNumber != 0)
	{
		g.fillAll(juce::Colours::darkorange);
	}
	else
	{
		g.fillAll(juce::Colours::black);
	}
}

void TrackMap::paintCell(
	juce::Graphics& g,
	int rowNumber,
	int columnId,
	int width,
	int height,
	bool rowIsSelected)
{
	g.setColour(juce::Colours::white);

	// Check if the rowNumber is within the selected tracks (added to remove an error when removing tracks)
	if (rowNumber >= 0 && rowNumber < selectedTracks.size())
	{
		// If the first column, add the track name
		if (columnId == 1)
		{
			g.drawText(
				selectedTracks[rowNumber].title,
				2,
				0,
				width - 4,
				height,
				juce::Justification::centredLeft
			);
		}
		// If the second, draw the map
		else if (columnId == 2)
		{
			// The first row is a fake row used to draw a scale for the time
			if (rowNumber == 0)
			{
				drawScale(g, width, height);
			}
			// All other rows are used to draw a bar to show the track on the scale
			else
			{
				drawTrack(g, width, height, selectedTracks[rowNumber]);

				// Add in the red line tracker, showing the current time on the track
				g.setColour(juce::Colours::red);
				g.drawLine(time * scale, 0, time * scale, getHeight());
			}
		}
	}
}

void TrackMap::drawScale(juce::Graphics& g, int width, int height)
{
	// Creates a number of lines used to show the time along the currently playing track
	for (int i = 0; i < width / scale; i++)
	{
		// Sets the size of the line. Larger lines are used for 5 second marks
		int lineHeight = (i % 5 == 0) ? height / 2 : height / 4;

		g.setColour(juce::Colours::white);
		g.drawLine(
			i * scale,
			0,
			i * scale,
			lineHeight,
			1
		);
	}
}

void TrackMap::drawTrack(juce::Graphics& g, int width, int height, TrackInfo track)
{
	// Find dimension of the rectange you want to draw
	int startOfTrack = track.startTime * scale;
	int trackLength = track.duration * scale / track.speed;
	int barHeight = height / 2;
	int topLeftCorner = height / 4;

	// Draw the track
	juce::Rectangle<int> trackBar = juce::Rectangle<int>(startOfTrack, topLeftCorner, trackLength, barHeight);
	g.setColour(track.colour);
	g.fillRect(trackBar);
	g.setColour(juce::Colours::white);
	g.drawRect(trackBar);
}

juce::Component* TrackMap::refreshComponentForCell(
	int rowNumber,
	int columnId,
	bool isRowSelected,
	juce::Component* componentToUpdate)
{
	return componentToUpdate;
}

void TrackMap::updateMap(double newTime)
{
	// If the time is equal to or above 0 then update
	if (newTime >= 0) 
	{
		time = newTime;
	}

	// Update content
	table.updateContent();
	repaint();
}

void TrackMap::selectedRowsChanged(int lastRowSelected) 
{
	// Update the selected row based on the lastRowSelected
	if (lastRowSelected >= 0 && lastRowSelected < selectedTracks.size()) {
	    trackSettings.selectedTrack = &selectedTracks[lastRowSelected];
	}
	// If out of scope, set to track zero (this is a scale bar and not a real track. This is ignored)
	else 
	{
		trackSettings.selectedTrack = &selectedTracks[0];
	}

	table.updateContent();
	trackSettings.updateContent();
}

void TrackMap::buttonClicked(juce::Button* button) 
{
	if (button == &removeButton)
	{
		// Get the index of the selected row
		int index = table.getSelectedRow();

		// Deselect the row
		table.deselectAllRows();

		// Remove the track from the selectedTracks
		if (index > 0 && index < selectedTracks.size()) 
		{
			selectedTracks.erase(selectedTracks.begin() + index);
		}
	}
}