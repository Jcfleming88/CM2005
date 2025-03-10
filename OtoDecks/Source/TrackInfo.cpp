#include "TrackInfo.h"

TrackInfo::TrackInfo(std::string trackPath) :
	filePath(trackPath)
{
	// Return a null track used for the scale bar is the input is "Tracks"
	if (trackPath == "Tracks") 
	{
		title = "Tracks";
		isNull = true;
		return;
	}
	// Otherwise, try to set the title
	else 
	{
		// Get the track name
		title = getFileName(filePath);
	}

	// Give a random colour
	colour = juce::Colour(juce::Random::getSystemRandom().nextInt());

	// Return null if there's an empty string
	if (title == "")
	{
		isNull = true;
		return;
	}

	// Try to find the duration of the track
	try 
	{
		// Get the file
		juce::File file{ trackPath };

		// Get a new formatManager temporarily
		juce::AudioFormatManager formatManager;
		formatManager.registerBasicFormats();

		// Get the total number of samples and divide by the sample rate to get the full duration of the track
		if (auto reader = formatManager.createReaderFor(file))
		{
			duration = reader->lengthInSamples / reader->sampleRate;
		}
	}
	catch (...)
	{
		// If something fails then return a null track
		isNull = true;
	}
}

TrackInfo::~TrackInfo()
{
}

std::string TrackInfo::getFileName(std::string filePath) {
	// Get the filename by splitting the filepath by the slashes and return the last element
	std::string fileName = filePath.substr(filePath.find_last_of("/\\") + 1);

    return fileName;
}