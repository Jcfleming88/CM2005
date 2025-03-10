#include <JuceHeader.h>
#include "WaveformDisplay.h"

WaveformDisplay::WaveformDisplay(
    juce::AudioFormatManager& formatManager,
    juce::AudioThumbnailCache& thumbnailCache
) :
	audioThumb{ 1000, formatManager, thumbnailCache },
    isFileLoaded{ false },
    position(0)
{
	audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    // clear the background
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   

    // draw an outline around the component
    g.setColour(juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);
    
	// Check if there is a file loaded
    if (!isFileLoaded) {
		// If there isn't, print a message
        g.setColour(juce::Colours::white);
        g.setFont(juce::FontOptions(20.0f));
        g.drawText("File not loaded", getLocalBounds(), juce::Justification::centred, true);   // draw some placeholder text
    }
    else {
		// If there is, draw the waveform
		g.setColour(juce::Colours::green);
        audioThumb.drawChannel(
            g,
            getLocalBounds(),
            0.0,
            audioThumb.getTotalLength(),
            0,
            1.0f
        );

		// Draw the playhead
        g.setColour(juce::Colours::red);
        g.drawLine(position * getWidth(), 0, position * getWidth(), getHeight());
    }
}

void WaveformDisplay::resized()
{

}

void WaveformDisplay::loadURL(juce::URL audioURL)
{
	DBG("WaveformDisplay::loadURL: Loading URL " << audioURL.toString(false));

    audioThumb.clear();
    isFileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));

	if (isFileLoaded)
	{
		DBG("WaveformDisplay::loadURL: Loaded URL " << audioURL.toString(false));
        repaint();
	}
	else
	{
		DBG("WaveformDisplay::loadURL: Failed to load URL " << audioURL.toString(false));
	}
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster *source)
{
	DBG("WaveformDisplay::changeListenerCallback: Change detected");
	repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos != position && pos > 0)
    {
        position = pos;
        repaint();
    }
}