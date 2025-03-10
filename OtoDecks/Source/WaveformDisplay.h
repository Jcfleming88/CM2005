#pragma once

#include <JuceHeader.h>

class WaveformDisplay  : 
    public juce::Component,
	public juce::ChangeListener
{
public:
    WaveformDisplay(
        juce::AudioFormatManager& formatManager,
        juce::AudioThumbnailCache& thumbnailCache
    );
    ~WaveformDisplay() override;

	/** Paint the waveform display */
    void paint (juce::Graphics&) override;

	/** Called when the component is resized */
    void resized() override;
    
    /** Use to perform an action when a change is reported */
	void changeListenerCallback(juce::ChangeBroadcaster *source) override;

	/** Load an audio file from a URL */
    void loadURL(juce::URL audioURL);

    /** set the relative position of the play head*/
    void setPositionRelative(double pos);

private:
	// Components
    juce::AudioThumbnail audioThumb;

    // States
	bool isFileLoaded;
    double position;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};
