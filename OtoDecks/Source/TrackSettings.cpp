#include <JuceHeader.h>
#include "TrackSettings.h"

TrackSettings::TrackSettings()
{
    startSlider.setRange(0, 500, 0.01);
    startSlider.addListener(this);

    volumeSlider.setRange(0, 1, 0.01);
    volumeSlider.addListener(this);

    speedSlider.setRange(0.1, 10, 0.01);
    speedSlider.addListener(this);

	addAndMakeVisible(trackName);

    addAndMakeVisible(startLabel);
    addAndMakeVisible(startSlider);
    
    addAndMakeVisible(speedLabel);
    addAndMakeVisible(speedSlider);

    addAndMakeVisible(volumeLabel);
    addAndMakeVisible(volumeSlider);
}

TrackSettings::~TrackSettings()
{
}

void TrackSettings::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);
}

void TrackSettings::resized()
{
    // Add the title for the track
	trackName.setBounds(5, 5, 200, 20);

    // Add the sliders for modifying the track settings
    int componentBoxHeight = getHeight() - 30;
    startLabel.setBounds(5, 30, 95, componentBoxHeight / 3);
    startSlider.setBounds(100, 30, getWidth() * 5 / 6 - 100, componentBoxHeight / 3);

    speedLabel.setBounds(5, 30 + componentBoxHeight / 3, 95, componentBoxHeight / 3);
    speedSlider.setBounds(100, 30 + componentBoxHeight / 3, getWidth() * 5 / 6 - 100, componentBoxHeight / 3);

    volumeLabel.setBounds(5, 30 + componentBoxHeight * 2 / 3, 95, componentBoxHeight / 3);
    volumeSlider.setBounds(100, 30 + componentBoxHeight * 2 / 3, getWidth() * 5 / 6 - 100, componentBoxHeight / 3);
}

void TrackSettings::updateContent() 
{
    if (selectedTrack != NULL)
    {
        if (selectedTrack->isNull) {
            trackName.setText(
                juce::String("No Track Selected"),
                juce::NotificationType::dontSendNotification
            );

            volumeSlider.setValue(0.5);
            speedSlider.setValue(1);
            startSlider.setValue(0);
        }
        else
        {
            trackName.setText(
                juce::String(selectedTrack->title),
                juce::NotificationType::dontSendNotification
            );

            volumeSlider.setValue(selectedTrack->gain);
            speedSlider.setValue(selectedTrack->speed);
            startSlider.setValue(selectedTrack->startTime);
        }
    }
    else 
    {
        trackName.setText(
            juce::String("No Track Selected"),
            juce::NotificationType::dontSendNotification
        );

        volumeSlider.setValue(0.5);
        speedSlider.setValue(1);
        startSlider.setValue(0);
    }
}

void TrackSettings::sliderValueChanged(juce::Slider* slider)
{
    // Skip if there's no track selected
    if (selectedTrack == NULL) 
    {
        return;
    }

    // Perform actions based on the slider used
    if (slider == &volumeSlider)
    {
        selectedTrack->gain = slider->getValue();
    }
    else if (slider == &speedSlider)
    {
        selectedTrack->speed = slider->getValue();
    }
    else if (slider == &startSlider) 
    {
        selectedTrack->startTime = slider->getValue();
    }
}