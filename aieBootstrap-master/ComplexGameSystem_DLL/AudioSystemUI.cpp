#include "AudioSystemUI.h"

//----------------------------------------------------------------------------------------------
// Default constructor.
//----------------------------------------------------------------------------------------------
AudioSystemUI::AudioSystemUI()
{
	m_pAudioSystem = new AudioSystem();

	// Creates the audio system.
	m_pAudioSystem->OnCreate();

	// Initializes m_bPause false.
	m_bPause = false;

	// Initializes m_bPlaying false.
	m_bPlaying = false;

	// Initializes m_fIntensity to the systems intensity.
	m_fIntensity = m_pAudioSystem->GetIntensity();
	
	// Initializes m_fVolume 1.0f.
	m_fVolume = 1.0f;

	// Initializes m_chBuf to an example of what to put in the input text.
	m_chBuf = new char[256]{"SKRILLEX.mp3"};

	// Initializes m_chFileDir to the folder location of the audio.
	m_chFileDir = new char[256]{ "../bin/audio/" };

	// Loads an audio file to start to prevent errors.
	m_pAudioSystem->LoadAudio("../bin/audio/SKRILLEX.mp3");
}

//----------------------------------------------------------------------------------------------
// Default destructor.
//----------------------------------------------------------------------------------------------
AudioSystemUI::~AudioSystemUI()
{
	// Calls the audio system destroy which releases things, and etc.
	m_pAudioSystem->OnDestroy();

	// Deletes m_chBuf.
	delete m_chBuf;

	// Deletes m_chFileDir.
	delete m_chFileDir;

	// Deletes m_pAudioSystem.
	delete m_pAudioSystem;
}

//----------------------------------------------------------------------------------------------
// Updates and creates the UI being used, it also calls some functions from audio system, such
// as update, and frequency analysis.
//----------------------------------------------------------------------------------------------
void AudioSystemUI::Update()
{
	// Updates Audio
	m_pAudioSystem->UpdateAudio();

	// Analyses audio to get spectrum data.
	m_pAudioSystem->FrequencyAnalysis(m_bPlaying);

	// Gets spectrum data.
	for (int i = 0; i < 2048; ++i)
	{
		m_fSpectrumData[i] = m_pAudioSystem->SpectrumData[i];
	}

	// Creates an ImGui window.
	ImGui::Begin("Audio Options");

	// Indents the buttons
	ImGui::Indent(85);

	// Creates a Play Button.
	bool bPlay = ImGui::Button("Play", ImVec2(100, 20));
	if (bPlay)
	{
		if (!m_bPlaying)
		{
			// If the Play button is pressed and playing is not true then play audio.
			m_pAudioSystem->PlayAudio();
			// Sets playing to true.
			m_bPlaying = true;
		}
	}

	// Creates a Pause/UnPause Button.
	bool bPaused = ImGui::Button("Pause/UnPause", ImVec2(100, 20));
	if (bPaused)
	{
		if (!m_bPause)
		{
			// If the Pause/UnPause button it pressed then pause the audio.
			m_pAudioSystem->Pause(true);
			// Sets m_bPause to true;
			m_bPause = true;
			// Sets m_bPlaying to false;
			m_bPlaying = false;
		}
		else
		{
			// Else it unpauses the audio. 
			m_pAudioSystem->Pause(false);
			// Sets m_bPause to false;
			m_bPause = false;
			// Sets m_bPlaying to true;
			m_bPlaying = true;
		}
	}
	
	// Unindents the next UI add.
	ImGui::Unindent(85);

	// Creates a slider which changes the intensity of the audio.
	ImGui::SliderFloat("Intensity", &m_fIntensity, 0.0f, 5000.0f);
	m_pAudioSystem->SetIntensity(m_fIntensity);

	// Creates a slider which changes the volume of the audio.
	ImGui::SliderFloat("Volume", &m_fVolume, 0.0f, 5.0f);
	m_pAudioSystem->SetVolume(m_fVolume);
	
	// Creates text input box whixh is used to load audio.
	ImGui::InputText("File Directory", m_chBuf, 256);

	// Indents the buttons
	ImGui::Indent(85);

	// Creates a Load Button.
	bool bPressed = ImGui::Button("Load", ImVec2(100, 20));
	if (bPressed)
	{
		// If the load button is pressed then release the Sound.
		m_pAudioSystem->ReleaseSound();
		// Sets FileDir, FileName, to the already created chars or the inputed name.
		std::string FileDir = m_chFileDir;
		std::string FileName = m_chBuf;
		// Then adds them together.
		std::string FullFile = FileDir + FileName;
		// Lastly converts it back to a const char pointer so it can be used in load audio.
		const char* chFullFile = FullFile.c_str();
		m_pAudioSystem->LoadAudio(chFullFile);
		// Sets m_bPlaying to false;
		m_bPlaying = false;
	}
	// Ends ImGui.
	ImGui::End();
}

