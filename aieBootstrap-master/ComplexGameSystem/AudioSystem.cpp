#include "AudioSystem.h"

AudioSystem::AudioSystem()
{
	// Load song
	//enableNormalize = true;
	//sampleSize = 64;

	// Set beat detection parameters
	//beatThresholdVolume = 0.3f;
	//beatThresholdBar = 0;
	//beatSustain = 150;
	//beatPostIgnore = 250;
	//beatTrackCutoff = 10000;
	//
	//beatLastTick = 0;
	//beatIgnoreLastTick = 0;
	//
	//musicStartTick = 0;
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
	result = m_pSystem->createSound(audio, FMOD_DEFAULT, 0, &m_pSound);
}

void AudioSystem::PlayAudio()
{
	result = m_pSystem->createChannelGroup("MyChannelGroup", &m_pChannelGroup);
	result = m_pSystem->playSound(m_pSound, m_pChannelGroup, false, &m_pChannel);
}

void AudioSystem::UpdateAudio()
{
	m_pSystem->update();

	// Frequency analysis
	//float *specLeft, *specRight, *spec;
	//spec = new float[sampleSize];
	//specLeft = new float[sampleSize];
	//specRight = new float[sampleSize];
	// Get average spectrum for left and right stereo channels
	//for (int i = 0; i < sampleSize; i++)
	//	spec[i] = (specLeft[i] + specRight[i]) / 2;
	// Find max volume
	//auto maxIterator = std::max_element(&spec[0], &spec[sampleSize]);
	//float maxVol = *maxIterator;
	// Normalize
	//if (enableNormalize && maxVol != 0)
		//std::transform(&spec[0], &spec[sampleSize], &spec[0], [maxVol](float dB) -> float { return dB / maxVol; });
	// Find frequency range of each array item
	//float hzRange = (44100 / 2) / static_cast<float>(sampleSize);
}

void AudioSystem::OnDestroy()
{
	m_pSound->release();
	m_pSystem->close();
	m_pSystem->release();
}

void AudioSystem::FrequencyAnalysis()
{
	m_pSystem->createDSPByType(FMOD_DSP_TYPE::FMOD_DSP_TYPE_FFT, &m_pDSP);
	m_pChannel->addDSP(FMOD_DSP_TYPE_FFT, m_pDSP);
	m_pFFT = new FMOD_DSP_PARAMETER_FFT();
	m_pDSP->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void **)m_pFFT, 0, 0, 0);
	for (int channel = 0; channel < m_pFFT->numchannels; channel++)
	{
		for (int bin = 0; bin < m_pFFT->length; bin++)
		{
			float freqVal = m_pFFT->spectrum[channel][bin];
			std::cout << freqVal << std::endl;
		}
	}
}

int AudioSystem::ErrorCheck(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		std::cout << "FMOD ERROR " << result << std::endl;
		return 1;
	}
	// cout << "FMOD all good" << endl;
	return 0;
}
