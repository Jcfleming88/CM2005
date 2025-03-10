#include "MainComponent.h"

#define GLOBAL_SETUP \
    std::cout << "Hello World!" << std::endl;

MainComponent::MainComponent()
{
    setSize (1200, 800);

	GLOBAL_SETUP;
	
    startTimer(10);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }

    addTracks.addListener(this);
    playButton.addListener(this);

    // Create a fake track for the header
    activeTracks.push_back(TrackInfo("Tracks"));

	addAndMakeVisible(trackMixer);
    addAndMakeVisible(deck1);
    addAndMakeVisible(deck2);
	addAndMakeVisible(playlist);
	addAndMakeVisible(addTracks);
    addAndMakeVisible(playButton);

	formatManager.registerBasicFormats();   
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);
    mixerSource.addInputSource(&player3, false);
    mixerSource.addInputSource(&player4, false);
    mixerSource.addInputSource(&player5, false);
    mixerSource.addInputSource(&player6, false);
    mixerSource.addInputSource(&player7, false);
    mixerSource.addInputSource(&player8, false);
    mixerSource.addInputSource(&player9, false);
    mixerSource.addInputSource(&player10, false);

    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    mixerSource.removeAllInputs();
    mixerSource.releaseResources();

    player1.releaseResources();
    player2.releaseResources();
    player3.releaseResources();
    player4.releaseResources();
    player5.releaseResources();
    player6.releaseResources();
    player7.releaseResources();
    player8.releaseResources();
    player9.releaseResources();
    player10.releaseResources();
}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    int buttonHeight = getHeight() / 6;
    int buttonDepth = getHeight() * 2 / 3 - buttonHeight;
    int buttonWidth = getWidth() / 8;

    trackMixer.setBounds(0, 0, getWidth(), getHeight() * 2 / 3);

    playButton.setBounds(
        getWidth() * 3 / 4 + getWidth() * 1 / 8,
        buttonDepth,
        buttonWidth,
        buttonHeight
    );

    deck1.setBounds(0, (getHeight() * 4 / 6), getWidth() / 2, (getHeight() / 6));
    deck2.setBounds(0, (getHeight() * 5 / 6), getWidth() / 2, (getHeight() / 6));

	playlist.setBounds(getWidth() / 2, getHeight() * 2 / 3, getWidth() / 2, (getHeight() / 3) - 50);

	addTracks.setBounds(getWidth() / 2, getHeight() - 50, getWidth() / 2, 50);
}

void MainComponent::buttonClicked(juce::Button* button)
{
	if (button == &addTracks)
	{
        auto fileChooserFlags = juce::FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
        {
            juce::File chosenFile = chooser.getResult();
			std::string path = chosenFile.getFullPathName().toStdString();

            if (path != "") 
            {
                tracks.push_back(TrackInfo(path));
                playlist.updateContent();
            }
        });
	}
    if (button == &playButton)
    {
        if (isPlaying)
        {
            isPlaying = false;
            time = 0;
            playButton.setButtonText("Play");

            for (int i = 0; i < playingTracks.size(); i++)
            {
                stopPlayer(i + 1);
            }

            playingTracks.clear();
        }
        else 
        {
            isPlaying = true;
            playButton.setButtonText("Stop");

            for (int i = 1; i < activeTracks.size(); i++)
            {
                addToPlayer(i, activeTracks[i]);
            }
        }
    }
}

void MainComponent::timerCallback()
{
    if (isPlaying)
    {
        checkTracksPlaying();
        time += 0.01;
    }

    trackMixer.updateContent(time);
}

void MainComponent::addToPlayer(int index, TrackInfo track)
{
    switch (index)
    {
        case 1:
            playingTracks.push_back(track);
            break;
        case 2:
            playingTracks.push_back(track);
            break;
        case 3:
            playingTracks.push_back(track);
            break;
        case 4:
            playingTracks.push_back(track);
            break;
        case 5:
            playingTracks.push_back(track);
            break;
        case 6:
            playingTracks.push_back(track);
            break;
        case 7:
            playingTracks.push_back(track);
            break;
        case 8:
            playingTracks.push_back(track);
            break;
        default:
            DBG("No avaliable players.");
            break;
    }
}

void MainComponent::checkTracksPlaying() 
{
    for (int i = 0; i < playingTracks.size(); i++)
    {
        if (i >= 8)
        {
            break;
        }
        if (time > playingTracks[i].startTime && !playingTracks[i].hasStarted)
        {
            playingTracks[i].hasStarted = true;
            startPlayer(i + 1, playingTracks[i]);
        }
        if (
            time > playingTracks[i].startTime + playingTracks[i].duration / playingTracks[i].speed &&
            !playingTracks[i].hasEnded
            ) 
        {
            playingTracks[i].hasEnded = true;
            stopPlayer(i + 1);
        }
    }
}

void MainComponent::startPlayer(int index, TrackInfo track)
{
    juce::URL url = juce::URL(juce::File(track.filePath));

    switch (index)
    {
    case 1:
        player3.loadURL(url);
        player3.setGain(track.gain);
        player3.setSpeed(track.speed);
        player3.play();
        break;
    case 2:
        player4.loadURL(url);
        player4.setGain(track.gain);
        player4.setSpeed(track.speed);
        player4.play();
        break;
    case 3:
        player5.loadURL(url);
        player5.setGain(track.gain);
        player5.setSpeed(track.speed);
        player5.play();
        break;
    case 4:
        player6.loadURL(url);
        player6.setGain(track.gain);
        player6.setSpeed(track.speed);
        player6.play();
        break;
    case 5:
        player7.loadURL(url);
        player7.setGain(track.gain);
        player7.setSpeed(track.speed);
        player7.play();
        break;
    case 6:
        player8.loadURL(url);
        player8.setGain(track.gain);
        player8.setSpeed(track.speed);
        player8.play();
        break;
    case 7:
        player9.loadURL(url);
        player9.setGain(track.gain);
        player9.setSpeed(track.speed);
        player9.play();
        break;
    case 8:
        player10.loadURL(url);
        player10.setGain(track.gain);
        player10.setSpeed(track.speed);
        player10.play();
        break;
    default:
        DBG("Can't find player.");
        break;
    }
}

void MainComponent::stopPlayer(int index)
{
    switch (index)
    {
    case 1:
        player3.stop();
        break;
    case 2:
        player4.stop();
        break;
    case 3:
        player5.stop();
        break;
    case 4:
        player6.stop();
        break;
    case 5:
        player7.stop();
        break;
    case 6:
        player8.stop();
        break;
    case 7:
        player9.stop();
        break;
    case 8:
        player10.stop();
        break;
    default:
        DBG("Can't find player.");
        break;
    }
}