#include <JuceHeader.h>
#include "PlaylistComponent.h"

PlaylistComponent::PlaylistComponent(
	std::vector<TrackInfo>& tracks,
	std::vector<TrackInfo>& activeTracks,
	TrackMixer& mixer,
	DeckGUI& d1,
	DeckGUI& d2
) :
	allTitles(tracks),
	trackTitles(activeTracks),
	trackMixer(mixer),
	player1(d1),
	player2(d2)
{
    table.getHeader().addColumn("Track Title", 1, 300);
    table.getHeader().addColumn("", 2, 75);
    table.getHeader().addColumn("", 3, 75);
	table.getHeader().addColumn("", 4, 75);
	table.getHeader().addColumn("", 5, 75);

    table.setModel(this);

	addAndMakeVisible(table);
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void PlaylistComponent::resized()
{
	table.setBounds(getLocalBounds());
}

int PlaylistComponent::getNumRows() 
{
	return allTitles.size();
}

void PlaylistComponent::paintRowBackground(
    juce::Graphics& g,
    int rowNumber,
    int width,
    int height,
    bool rowIsSelected)
{
	if (rowIsSelected)
	{
		g.fillAll(juce::Colours::orange);
	}
	else
	{
		g.fillAll(juce::Colours::saddlebrown);
	}
}

void PlaylistComponent::paintCell(
    juce::Graphics& g,
    int rowNumber,
    int columnId,
    int width,
    int height,
    bool rowIsSelected)
{
    if (rowIsSelected) 
    {
        g.setColour(juce::Colours::black);
    }
    else
    {
        g.setColour(juce::Colours::white);
    }

	if (columnId == 1) 
	{
		g.drawText(
			allTitles[rowNumber].title,
			2,
			0,
			width - 4,
			height,
			juce::Justification::centredLeft
		);
	}
}

juce::Component* PlaylistComponent::refreshComponentForCell(
    int rowNumber,
    int columnId,
    bool isRowSelected,
    juce::Component* componentToUpdate)
{
	if (columnId == 2)
	{
		if (componentToUpdate == nullptr)
		{
            // Create a button
			juce::TextButton* btn = new juce::TextButton("To Player 1");

			// Set the button's id to the row number
			juce::String id{ "P1" + std::to_string(rowNumber)};
			btn->setComponentID(id);
			btn->addListener(this);

            componentToUpdate = btn;
		}
	}
	else if (columnId == 3)
	{
		if (componentToUpdate == nullptr)
		{
			juce::TextButton* btn = new juce::TextButton("To Player 2");
			juce::String id{ "P2" + std::to_string(rowNumber)};
			btn->setComponentID(id);
			btn->addListener(this);
			componentToUpdate = btn;
		}
	}
	else if (columnId == 4)
	{
		if (componentToUpdate == nullptr)
		{
			juce::TextButton* btn = new juce::TextButton("To Main Track");
			juce::String id{ "AT" + std::to_string(rowNumber)};
			btn->setComponentID(id);
			btn->addListener(this);
			componentToUpdate = btn;
		}
	}
	else if (columnId == 5)
	{
		if (componentToUpdate == nullptr)
		{
			juce::TextButton* btn = new juce::TextButton("Remove");
			juce::String id{ "RM" + std::to_string(rowNumber) };
			btn->setComponentID(id);
			btn->addListener(this);
			componentToUpdate = btn;
		}
	}

	return componentToUpdate;
}

void PlaylistComponent::buttonClicked(juce::Button* button)
{
	std::string ref = button->getComponentID().toStdString();
    DBG("PlaylistComponent::buttonClicked: " << ref);

	std::string buttonType = ref.substr(0, 2);
	int trackIndex = std::stoi(ref.substr(2));

	juce::URL url = juce::URL(juce::File(allTitles[trackIndex].filePath));

	if (buttonType == "P1")
	{
		player1.loadURL(url);
	}
	else if (buttonType == "P2")
	{
		player2.loadURL(url);
	}
	else if (buttonType == "AT")
	{
		trackTitles.push_back(allTitles[trackIndex]);
		trackMixer.updateContent(-1);
	}
	else if (buttonType == "RM")
	{
		allTitles.erase(allTitles.begin() + trackIndex);
		table.updateContent();
	}
}

bool PlaylistComponent::isInterestedInFileDrag(const juce::StringArray& files)
{
	DBG("DeckGUI::isInterestedInFileDrag");
	return true;
}

void PlaylistComponent::filesDropped(const juce::StringArray& files, int x, int y)
{
	DBG("DeckGUI::filesDropped");
	for (juce::String file : files)
	{
		std::string filePath = file.toStdString();
		allTitles.push_back(TrackInfo{ filePath });
	}

	table.updateContent();
}

void PlaylistComponent::updateContent()
{
	table.updateContent();
}