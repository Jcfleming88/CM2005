#include "DJAudioPlayer.h"
DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& audioFormatManager) : 
	formatManager(audioFormatManager)
{
}

DJAudioPlayer::~DJAudioPlayer()
{
}

void DJAudioPlayer::loadURL(juce::URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource (new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}

void DJAudioPlayer::play()
{
	transportSource.setPosition(0);
    transportSource.start();
}

void DJAudioPlayer::stop()
{
    transportSource.stop();
}

void DJAudioPlayer::setGain(double gain)
{
	if (gain < 0 || gain > 1) {
		DBG("DJAudioPlayer::setGain: Set gain of " << gain \
			<< " is outside of range 0 to 1");
		return;
	}
    else 
    {
        transportSource.setGain(gain);
    }
}

void DJAudioPlayer::setPosition(double posInSecs)
{
    if (posInSecs < 0 || posInSecs > transportSource.getLengthInSeconds()) {
        DBG("DJAudioPlayer::setPosition: warning set position " << posInSecs \
            << " greater than length " << transportSource.getLengthInSeconds());
        return;
    }
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos)
{
    double posInSecs = pos * transportSource.getLengthInSeconds();
    setPosition(posInSecs);
}

void DJAudioPlayer::setSpeed(double ratio)
{
    if (ratio < 0 || ratio > 100.0) 
    {
		DBG("DJAudioPlayer::setSpeed: Set speed of " << ratio \
			<< " is outside of range 0 to 100");
		return;
	}
    else
    {
        resamplingSource.setResamplingRatio(ratio);
    }
}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
	resamplingSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource.get() == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    resamplingSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources(); 
	resamplingSource.releaseResources();
}

bool DJAudioPlayer::hasTrack()
{
	return readerSource.get() != nullptr;
}

double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

double DJAudioPlayer::getTrackLength()
{
    if (hasTrack())
    {
        return transportSource.getLengthInSeconds();
    }
    else 
    {
        return 0;
    }
}