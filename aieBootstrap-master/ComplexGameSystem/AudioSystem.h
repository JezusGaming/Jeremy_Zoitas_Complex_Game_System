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
	void OnDestroy();
	int AudioSystem::ErrorCheck(FMOD_RESULT result);

	FMOD::System* m_pSystem;
	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;
	FMOD::ChannelGroup* m_pChannelGroup;
	FMOD::DSP* m_pDSP;
	FMOD_RESULT result;
};

