#pragma once
#include <fmod.h>
#include <fmod.hpp>
#include <iostream>
#include <queue>

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
	float FrequencyAnalysis();
	int AudioSystem::ErrorCheck(FMOD_RESULT result);
	float f[32];
private:
	FMOD::System* m_pSystem;
	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;
	FMOD::ChannelGroup* m_pChannelGroup;
	FMOD::DSP* m_pDSP;
	FMOD_RESULT result;
	
	
	 //Normalization toggle and sample size
	//bool enableNormalize;
	//int sampleSize;

	 //Beat detection parameters
	//float beatThresholdVolume;
	//int beatThresholdBar;
	//unsigned int beatSustain;
	//unsigned int beatPostIgnore;

	//int beatLastTick;
	//int beatIgnoreLastTick;

	 //List of how many ms ago the last beats were
	//std::queue<int> beatTimes;
	//unsigned int beatTrackCutoff;

	 //When the music was last unpaused
	//int musicStartTick;
};

