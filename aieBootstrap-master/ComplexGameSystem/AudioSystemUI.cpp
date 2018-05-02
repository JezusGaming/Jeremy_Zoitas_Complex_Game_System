#include "AudioSystemUI.h"

AudioSystemUI::AudioSystemUI()
{
	m_pAudioSystem = new AudioSystem();

	m_pAudioSystem->OnCreate();

	m_bPause = false;

	m_bPlaying = false;

	m_fIntensity = m_pAudioSystem->GetIntensity();
	
	m_fVolume = 1.0f;

	m_chBuf = new char[256]{"SKRILLEX.mp3"};

	m_chFileDir = new char[256]{ "../bin/audio/" };

	m_pAudioSystem->LoadAudio("../bin/audio/SKRILLEX.mp3");
}


AudioSystemUI::~AudioSystemUI()
{
	m_pAudioSystem->OnDestroy();

	delete m_pAudioSystem;
}

void AudioSystemUI::Update()
{
	m_pAudioSystem->UpdateAudio();
	m_pAudioSystem->FrequencyAnalysis(m_bPlaying);

	for (int i = 0; i < 256; ++i)
	{
		m_fSpectrumData[i] = m_pAudioSystem->SpectrumData[i];
	}

	ImGui::Begin("Audio Options");
	ImGui::Indent(100);
	bool bPlay = ImGui::Button("Play", ImVec2(100, 20));
	if (bPlay)
	{
		if (!m_bPlaying)
		{
			m_pAudioSystem->PlayAudio();
			m_bPlaying = true;
			
		}
	}

	bool bPaused = ImGui::Button("Pause/UnPause", ImVec2(100, 20));
	if (bPaused)
	{
		if (!m_bPause)
		{
			m_pAudioSystem->Pause(true);
			m_bPause = true;
			m_bPlaying = false;
		}
		else
		{
			m_pAudioSystem->Pause(false);
			m_bPause = false;
			m_bPlaying = true;
		}
	}

	ImGui::SliderFloat("Intensity", &m_fIntensity, 0.0f, 5000.0f);
	m_pAudioSystem->SetIntensity(m_fIntensity);

	ImGui::SliderFloat("Volume", &m_fVolume, 0.0f, 5.0f);
	m_pAudioSystem->SetVolume(m_fVolume);

	ImGui::InputText("File Directory", m_chBuf, 256);
	bool bPressed = ImGui::Button("Load", ImVec2(100, 20));
	if (bPressed)
	{
		m_pAudioSystem->ReleaseSound();
		std::string FileDir = m_chFileDir;
		std::string FileName = m_chBuf;
		std::string FullFile = FileDir + FileName;
		const char* chFullFile = FullFile.c_str();
		m_pAudioSystem->LoadAudio(chFullFile);
		m_bPlaying = false;
	}
	ImGui::End();
}

