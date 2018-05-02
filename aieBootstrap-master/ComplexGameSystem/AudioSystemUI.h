#pragma once
#include <imgui.h>
#include "AudioSystem.h"
class AudioSystemUI
{
public:
	AudioSystemUI();
	~AudioSystemUI();

	void Update();

	float m_fSpectrumData[256];
protected:
	AudioSystem * m_pAudioSystem;
	bool m_bPause;
	bool m_bPlaying;
	float m_fIntensity;
	char* m_chBuf;
	const char* m_chFileDir;
	float m_fVolume;
};

