#include "AudioSystem.h"

AudioSystem::AudioSystem()
{

}


AudioSystem::~AudioSystem()
{
}

bool AudioSystem::OnCreate()
{
	m_pSystem = NULL; 
	result = FMOD::System_Create(&m_pSystem);
	if (result != FMOD_OK)
	{
		ErrorCheck(result);
		return false;
	}
	result = m_pSystem->init(512, FMOD_INIT_NORMAL, NULL);
	if (result != FMOD_OK) 
{ 
		ErrorCheck(result);
		return false;
	}
	return true;
}

void AudioSystem::LoadAudio(const char* audio)
{
	result = m_pSystem->createSound(audio, FMOD_CREATESTREAM, 0, &m_pSound);
}

void AudioSystem::PlayAudio()
{
	result = m_pSystem->playSound(m_pSound, 0, false, &m_pChannel);
}

void AudioSystem::UpdateAudio()
{
	m_pSystem->update();
}

void AudioSystem::OnDestroy()
{
	m_pSound->release();
	m_pSystem->close();
	m_pSystem->release();
}

int AudioSystem::ErrorCheck(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		std::cout << "FMOD ERROR " << result << std::endl;
		return 1;
	}
	// cout << "FMOD all good" << endl;
	return 0;
}
