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
	//m_pFFT = new FMOD_DSP_PARAMETER_FFT();
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
	result = m_pSystem->init(32, FMOD_INIT_NORMAL, NULL);
	if (result != FMOD_OK) 
{ 
		ErrorCheck(result);
		return false;
	}
	return true;
}

void AudioSystem::LoadAudio(const char* audio)
{
	result = m_pSystem->createSound(audio, FMOD_LOOP_NORMAL, 0, &m_pSound);
}

void AudioSystem::PlayAudio()
{
	result = m_pChannel->setVolume(1.0f);
	
	result = m_pSystem->playSound(m_pSound, 0, false, &m_pChannel);

	const uint32_t windowSize = 1024;
	result = m_pSystem->getMasterChannelGroup(&m_pChannelGroup);

	// Create a DSP by type and add to master channel group
	result = m_pSystem->createDSPByType(FMOD_DSP_TYPE_FFT, &m_pDSP);
	result = m_pDSP->setParameterInt(FMOD_DSP_FFT_WINDOWTYPE, FMOD_DSP_FFT_WINDOW_HANNING);
	result = m_pDSP->setParameterInt(FMOD_DSP_FFT_WINDOWSIZE, windowSize * 2);
	result = m_pChannelGroup->addDSP(FMOD_CHANNELCONTROL_DSP_HEAD, m_pDSP);
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

void AudioSystem::Pause(bool paused)
{
	m_pChannel->setPaused(paused);
}

void AudioSystem::OnDestroy()
{
	m_pSound->release();
	m_pSystem->close();
	m_pSystem->release();
}

float AudioSystem::FrequencyAnalysis()
{
	FMOD_DSP_PARAMETER_FFT *m_pFFT;

	//void* spectrumData;
	result = m_pDSP->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void **)&m_pFFT, 0, 0, 0);
	//FMOD_DSP_PARAMETER_FFT* fft = (FMOD_DSP_PARAMETER_FFT*)m_pSound;
	if (m_pFFT)
	{

		for (int channel = 0; channel<1; ++channel)
		{
			// Only read / display half of the buffer typically for analysis 
			// as the 2nd half is usually the same data reversed due to the nature of the way FFT works.
			//unsigned int len = m_pFFT->length / 2;
			for ( int bin = 0; bin<m_pFFT->length; ++bin)
			{
				// Do something with fft->spectrum[i]
				//float* freqVal = m_pFFT->spectrum[i];
				//std::cout << *freqVal << std::endl;
				
				float freqVal = m_pFFT->spectrum[channel][bin];
				//std::cout << freqVal << std::endl;
				f[bin] = freqVal * 1000;
				
				if (bin >= 32)
				{
					return 0;
				}
			}
		}
	}
	return 0;
	//m_pChannel->addDSP(FMOD_DSP_TYPE_FFT, m_pDSP);
	////int window = 512;
	////m_pDSP->setParameterInt(FMOD_DSP_FFT_WINDOWSIZE, window);
	//m_pDSP->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void **)m_pFFT, 0, 0, 0);
	//for (int channel = 0; channel < m_pFFT->numchannels; channel++)
	//{
	//	for (int bin = 0; bin < m_pFFT->length; bin++)
	//	{
	//		float freqVal = m_pFFT->spectrum[channel][bin];
	//		std::cout << freqVal << std::endl;
	//	}
	//}
}

int AudioSystem::ErrorCheck(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		std::cout << "FMOD ERROR " << result << std::endl;
		return 1;
	}
	// cout << "FMOD all good" << endl;
	return 0;
}
