#include <JuceHeader.h>
#include "DeckGUI.h"

DeckGUI::DeckGUI(
	int _id,
    DJAudioPlayer* _djAudioPlayer,
    juce::AudioFormatManager& formatManager,
    juce::AudioThumbnailCache& thumbnailCache
) : 
	id{ _id },
    player{ _djAudioPlayer },
	waveformDisplay{ formatManager, thumbnailCache }
{
    // Set the initial volume
	volumeSlider.setRange(0.0, 1.0);
	volumeSlider.setValue(0.5);
	player->setGain(0.5);

	// Set the initial position
	positionSlider.setRange(0.0, 1.0);

	// Set the initial speed
	speedSlider.setRange(0.0, 10.0);
	speedSlider.setValue(1.0);
	player->setSpeed(1.0);

    // Add the listners
    playButton.addListener(this);
    volumeSlider.addListener(this);
    positionSlider.addListener(this);
    speedSlider.addListener(this);
    loadButton.addListener(this);
    
    // Set the timer
    startTimer(200);

	// Add the components to the view
    addAndMakeVisible(playButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(waveformDisplay);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId)); // clear g.setColour (Colours::grey);
    g.drawRect(getLocalBounds(), 1); // draw an outline around the component
    
    g.setColour(juce::Colours::white);
    g.setFont(juce::FontOptions(20.0f));

	std::string title = "Preview Player " + std::to_string(id);
    g.drawText(title, getLocalBounds(),
        juce::Justification::topLeft, true);
}

void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    int rowH = getHeight() / 6;
    int rowW = getWidth();

	waveformDisplay.setBounds(0, 20, rowW, (rowH * 3) - 20);

    volumeSlider.setBounds(0, rowH * 3, rowW - std::max(rowH, 80), rowH);
    positionSlider.setBounds(0, rowH * 4, rowW - std::max(rowH, 80), rowH);
    speedSlider.setBounds(0, rowH * 5, rowW - std::max(rowH, 80), rowH);

    playButton.setBounds(rowW - std::max(rowH, 80), rowH * 3, std::max(rowH, 80), rowH * 2);
    loadButton.setBounds(rowW - std::max(rowH, 80), rowH * 5, std::max(rowH, 80), rowH);
}

void DeckGUI::playTrack()
{
    player->play();
    isPlaying = true;
    playButton.setButtonText("Stop");
}

void DeckGUI::stopTrack()
{
    player->stop();
    isPlaying = false;
    playButton.setButtonText("Play");
}

void DeckGUI::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
		if (isPlaying)
		{
			stopTrack();
		}
		else
		{
            playTrack();
		}
    }
}

void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
    {
        player->setGain(slider->getValue());
    }
    if (slider == &positionSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
    if (slider == &speedSlider)
    {
		if (slider->getValue() == 0)
		{
			stopTrack();
		}
        else if (slider->getValue() > 0 && player->hasTrack())
        {
            playTrack();
        }

        player->setSpeed(slider->getValue());
    }
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}

void DeckGUI::loadURL(juce::URL audioURL)
{
	player->loadURL(audioURL);
	waveformDisplay.loadURL(audioURL);
}