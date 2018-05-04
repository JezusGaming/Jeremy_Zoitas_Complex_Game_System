#include "AudioSystem.h"

//----------------------------------------------------------------------------------------------
// Default constructor.
//----------------------------------------------------------------------------------------------
AudioSystem::AudioSystem()
{
	m_fIntensity = 1000;
}

//----------------------------------------------------------------------------------------------
// Default destructor.
//----------------------------------------------------------------------------------------------
AudioSystem::~AudioSystem()
{
}

//----------------------------------------------------------------------------------------------
// Creates the system and checks if the system is created successfully. 
//
// Return:
//		 Returns a bool based on whether fmod is created successfully.
//----------------------------------------------------------------------------------------------
bool AudioSystem::OnCreate()
{
	// Initializes the system to null.
	m_pSystem = NULL; 
	// Creates fmod system on m_pSystem.
	result = FMOD::System_Create(&m_pSystem);
	// Checks if the create worked, if it didn't then call error check which prints the error.
	if (result != FMOD_OK)
	{
		ErrorCheck(result);
		return false;
	}
	// Initializes the system object, and the sound device. 
	result = m_pSystem->init(512, FMOD_INIT_NORMAL, NULL);
	// Checks if the Initialize worked, if not then call error check which prints the error.
	if (result != FMOD_OK) 
	{ 
		ErrorCheck(result);
		return false;
	}
	// Return true if the system stated properly.
	return true;
}

//----------------------------------------------------------------------------------------------
// Loads the audio based on the name that has been passed in.
//
// Param:
//		audio: Is a const char pointer that is used to find the audio and load it.
//----------------------------------------------------------------------------------------------
void AudioSystem::LoadAudio(const char* audio)
{
	// Creates a sound which loops based on the passed in file directory.
	result = m_pSystem->createSound(audio, FMOD_LOOP_NORMAL, 0, &m_pSound);
}

//----------------------------------------------------------------------------------------------
// Plays audio, also creates a master channel which creates and adds a dsp which is used to get
// the audio pectrum data later on.
//----------------------------------------------------------------------------------------------
void AudioSystem::PlayAudio()
{
	// Sets the volume to 1.0f so the audio can be heared.
	result = m_pChannel->setVolume(1.0f);

	// Plays the sound which has been created in the load function.
	result = m_pSystem->playSound(m_pSound, 0, false, &m_pChannel);

	// Is the size of the spectrum data spread out, which is double down below when creating 
	// the DSP.
	const uint32_t windowSize = 1024;

	// gets the master channel.
	result = m_pSystem->getMasterChannelGroup(&m_pChannelGroup);

	// Create a DSP by type and adds to master channel group
	result = m_pSystem->createDSPByType(FMOD_DSP_TYPE_FFT, &m_pDSP);
	result = m_pDSP->setParameterInt(FMOD_DSP_FFT_WINDOWTYPE, FMOD_DSP_FFT_WINDOW_HANNING);
	result = m_pDSP->setParameterInt(FMOD_DSP_FFT_WINDOWSIZE, windowSize * 2);
	result = m_pChannelGroup->addDSP(FMOD_CHANNELCONTROL_DSP_HEAD, m_pDSP);
}

//----------------------------------------------------------------------------------------------
// Updates the audio being played.
//----------------------------------------------------------------------------------------------
void AudioSystem::UpdateAudio()
{
	// Updates the system which updates the audio.
	m_pSystem->update();
}

//----------------------------------------------------------------------------------------------
// Sets the music to be paused/unpaused.
//
// Param:
//		paused: A bool which is used to pause the audio.
//----------------------------------------------------------------------------------------------
void AudioSystem::Pause(bool paused)
{
	// Toggles  setPaused based on the bool beinng passed in.
	m_pChannel->setPaused(paused);
}

//----------------------------------------------------------------------------------------------
// Used on shutdown to destroy/shutdown fmod system.
//----------------------------------------------------------------------------------------------
void AudioSystem::OnDestroy()
{
	// Frees a sound object.
	m_pSound->release();

	// Closes the system object without freeing the object's memory, so the system handle will 
	// still be valid.
	m_pSystem->close();
	
	// Closes and frees a system object and its resources.
	m_pSystem->release();
}

//----------------------------------------------------------------------------------------------
// Used to calculate the frequency/spectrum data of the currently played audio.
//
// Param:
//		bPlaying: A bool which lets it know if the audio is playing.
//----------------------------------------------------------------------------------------------
float AudioSystem::FrequencyAnalysis(bool bPlaying)
{
	// Initializes m_pFFT which is a Structure for data parameters of type 
	// FMOD_DSP_PARAMETER_DATA_TYPE_FFT.
	FMOD_DSP_PARAMETER_FFT *m_pFFT;
	// Used to Retrieve the DSP unit's data block, so m_pFFT can be used to get spectrum data.
	result = m_pDSP->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void **)&m_pFFT, 0, 0, 0);
	if (m_pFFT && bPlaying)
	{
		// A double for loop to get the data of the one channel and go through the length of it.  
		for (int channel = 0; channel<1; ++channel)
		{
			for ( int bin = 0; bin<m_pFFT->length; ++bin)
			{	
				// As the for loop goes through the length of the FFT it gets the spectrumdata 
				// and then sets it in the spectrum data array.
				float freqVal = m_pFFT->spectrum[channel][bin];
				SpectrumData[bin] = freqVal * m_fIntensity;	
			}
			return 0;
		}
	}
	return 0;
}

//----------------------------------------------------------------------------------------------
// Used to check if fmod has any errors.
//
// Param:
//		result: is an enum of fmods errors, if it does not equal fmod_ok then an error occurs.
//
// Return: 
//		 Returns an int based on if the error check is successful.
//----------------------------------------------------------------------------------------------
int AudioSystem::ErrorCheck(FMOD_RESULT result) 
{
	// If fmod_result does not equal fmod_ok then print the error that has occoured.
	if (result != FMOD_OK) 
	{
		std::cout << "FMOD ERROR " << result << std::endl;
		return 1;
	}
	// otherwise FMOD all good.
	return 0;
}

//----------------------------------------------------------------------------------------------
// Gets the music spectrum intensity so it can be used in the UI.
// 
// Returns:
//		  Returns the m_fIntensity.
//----------------------------------------------------------------------------------------------
float AudioSystem::GetIntensity()
{
	return m_fIntensity;
}

//----------------------------------------------------------------------------------------------
// Sets the music spectrum intensity so it can display more exaggerated then it is.
//
// Param:
//		Intensity: A float which is multiplied by the spectrum data to increase the output.
//----------------------------------------------------------------------------------------------
void AudioSystem::SetIntensity(float Intensity)
{
	m_fIntensity = Intensity;
}

//----------------------------------------------------------------------------------------------
// Sets the volume of the music.
//
// Param:
//		Volume: A float which used to set the volume which should be from 0.0f - 1.0f
//----------------------------------------------------------------------------------------------
void AudioSystem::SetVolume(float Volume)
{
	result = m_pChannel->setVolume(Volume);
}

//----------------------------------------------------------------------------------------------
// Releases the sound, so another sound can be load in its spot.
//----------------------------------------------------------------------------------------------
void AudioSystem::ReleaseSound()
{
	// Frees a sound object.
	m_pSound->release();
}
