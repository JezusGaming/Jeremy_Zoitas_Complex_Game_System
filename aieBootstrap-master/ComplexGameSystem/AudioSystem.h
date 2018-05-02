#pragma once
#include <fmod.h>
#include <fmod.hpp>
#include <iostream>

class AudioSystem
{
public:
	AudioSystem();
	~AudioSystem();
	bool OnCreate();
	void LoadAudio(const char* audio);
	void PlayAudio();
	void UpdateAudio();
	void Pause(bool paused);
	void OnDestroy();
	float FrequencyAnalysis(bool bPlaying);
	int AudioSystem::ErrorCheck(FMOD_RESULT result);
	float GetIntensity();
	void SetIntensity(float Intensity);
	void SetVolume(float Volume);
	void ReleaseSound();

	float SpectrumData[256];
	
private:
	FMOD::System* m_pSystem;
	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;
	FMOD::ChannelGroup* m_pChannelGroup;
	FMOD::DSP* m_pDSP;
	FMOD_RESULT result;
	float m_fIntensity;
};

