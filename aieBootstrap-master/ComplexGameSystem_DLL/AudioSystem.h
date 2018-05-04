//----------------------------------------------------------------------------------------------
// AudioSystem.h
// Brief: Is a wrapper for fmod, it manages functions dealing with fmod such as play audio,
// load audio, pause, getting the spectrum data, etc. This class is used in AudioSystemUI so it 
// is easy for people to use because it creates UI based around these functions.
// Edited By: Jeremy Zoitas.
//----------------------------------------------------------------------------------------------
#pragma once
#include <fmod.h>
#include <fmod.hpp>
#include <iostream>

class AudioSystem
{
public:
	//----------------------------------------------------------------------------------------------
	// Default constructor.
	//----------------------------------------------------------------------------------------------
	AudioSystem();

	//----------------------------------------------------------------------------------------------
	// Default destructor.
	//----------------------------------------------------------------------------------------------
	~AudioSystem();

	//----------------------------------------------------------------------------------------------
	// Creates the system and checks if the system is created successfully. 
	//
	// Return:
	//		 Returns a bool based on whether fmod is created successfully.
	//----------------------------------------------------------------------------------------------
	bool OnCreate();

	//----------------------------------------------------------------------------------------------
	// Loads the audio based on the name that has been passed in.
	//
	// Param:
	//		audio: Is a const char pointer that is used to find the audio and load it.
	//----------------------------------------------------------------------------------------------
	void LoadAudio(const char* audio);

	//----------------------------------------------------------------------------------------------
	// Plays audio, also creates a master channel which creates and adds a dsp which is used to get
	// the audio pectrum data later on.
	//----------------------------------------------------------------------------------------------
	void PlayAudio();

	//----------------------------------------------------------------------------------------------
	// Updates the audio being played.
	//----------------------------------------------------------------------------------------------
	void UpdateAudio();

	//----------------------------------------------------------------------------------------------
	// Sets the music to be paused/unpaused.
	//
	// Param:
	//		paused: A bool which is used to pause the audio.
	//----------------------------------------------------------------------------------------------
	void Pause(bool paused);

	//----------------------------------------------------------------------------------------------
	// Used on shutdown to destroy/shutdown fmod system.
	//----------------------------------------------------------------------------------------------
	void OnDestroy();

	//----------------------------------------------------------------------------------------------
	// Sets the music spectrum intensity so it can display more exaggerated then it is.
	//
	// Param:
	//		Intensity: A float which is multiplied by the spectrum data to increase the output.
	//----------------------------------------------------------------------------------------------
	void SetIntensity(float Intensity);

	//----------------------------------------------------------------------------------------------
	// Sets the volume of the music.
	//
	// Param:
	//		Volume: A float which used to set the volume which should be from 0.0f - 1.0f
	//----------------------------------------------------------------------------------------------
	void SetVolume(float Volume);

	//----------------------------------------------------------------------------------------------
	// Releases the sound, so another sound can be load in its spot.
	//----------------------------------------------------------------------------------------------
	void ReleaseSound();

	//----------------------------------------------------------------------------------------------
	// Used to calculate the frequency/spectrum data of the currently played audio.
	//
	// Param:
	//		bPlaying: A bool which lets it know if the audio is playing.
	//----------------------------------------------------------------------------------------------
	float FrequencyAnalysis(bool bPlaying);

	//----------------------------------------------------------------------------------------------
	// Gets the music spectrum intensity so it can be used in the UI.
	//
	// Returns:
	//		  Returns the m_fIntensity.
	//----------------------------------------------------------------------------------------------
	float GetIntensity();

	//----------------------------------------------------------------------------------------------
	// Used to check if fmod has any errors.
	//
	// Param:
	//		result: is an enum of fmods errors, if it does not equal fmod_ok then an error occurs.
	//
	// Return: 
	//		 Returns an int based on if the error check is successful.
	//----------------------------------------------------------------------------------------------
	int AudioSystem::ErrorCheck(FMOD_RESULT result);
	
	//----------------------------------------------------------------------------------------------
	// A public array of floats which holds spectrum data spread out over a range of 2048.
	//----------------------------------------------------------------------------------------------
	float SpectrumData[2048];
	
private:
	//----------------------------------------------------------------------------------------------
	// A pointer to fmod system.
	//----------------------------------------------------------------------------------------------
	FMOD::System* m_pSystem;

	//----------------------------------------------------------------------------------------------
	// A pointer to fmod sound.
	//----------------------------------------------------------------------------------------------
	FMOD::Sound* m_pSound;

	//----------------------------------------------------------------------------------------------
	// A pointer to fmod channel.
	//----------------------------------------------------------------------------------------------
	FMOD::Channel* m_pChannel;

	//----------------------------------------------------------------------------------------------
	// A pointer to fmod channel group.
	//----------------------------------------------------------------------------------------------
	FMOD::ChannelGroup* m_pChannelGroup;

	//----------------------------------------------------------------------------------------------
	// A pointer to fmod dsp.
	//----------------------------------------------------------------------------------------------
	FMOD::DSP* m_pDSP;

	//----------------------------------------------------------------------------------------------
	// An enum of erroe fmod codes.
	//----------------------------------------------------------------------------------------------
	FMOD_RESULT result;
	
	//----------------------------------------------------------------------------------------------
	// A float used for the intensity of the data.
	//----------------------------------------------------------------------------------------------
	float m_fIntensity;
};

