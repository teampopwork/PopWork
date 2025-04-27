#include "OpenALSoundInstance.h"
#include "OpenALSoundManager.h"
#include "BassLoader.h"
#include <iostream>

using namespace Sexy;


OpenALSoundInstance::OpenALSoundInstance(OpenALSoundManager* theSoundManager, ALuint theSourceSound)
{
	mSoundManagerP = theSoundManager;
	mReleased = false;
	mAutoRelease = false;
	mHasPlayed = false;
	mSourceSoundBuffer = theSourceSound;
	mSoundBuffer = NULL;

	mBaseVolume = 1.0;
	mBasePan = 0;

	mVolume = 1.0;
	mPan = 0;

	mDefaultFrequency = 44100;

	BASS_CHANNELINFO  aInfo{};

	//start duplicating the sound buffer
	if (mSourceSoundBuffer != NULL)
	{
		alGenSources(1, &mSoundBuffer);
		alSourcei(mSoundBuffer, AL_BUFFER, mSourceSoundBuffer);
	}

	RehupVolume();
}

OpenALSoundInstance::~OpenALSoundInstance()
{
	alDeleteSources(1, &mSoundBuffer);
}

void OpenALSoundInstance::RehupVolume()
{
	if (mSoundBuffer != NULL)
	{
		alSourcef(mSoundBuffer, AL_GAIN, mVolume * mBaseVolume * mSoundManagerP->mMasterVolume);
	}
}

void OpenALSoundInstance::RehupPan()
{
	if (mSoundBuffer != NULL)
	{
		float normalizedPan = mBasePan * mPan / 10000.0f;
		alSource3f(mSoundBuffer, AL_POSITION, normalizedPan, 0.0f, 0.0f);
	}
}

void OpenALSoundInstance::Release()
{
	Stop();
	mReleased = true;
}

void OpenALSoundInstance::SetBaseVolume(double theBaseVolume)
{
	mBaseVolume = theBaseVolume;
	RehupVolume();
}

void OpenALSoundInstance::SetBasePan(int theBasePan)
{
	mBasePan = theBasePan;
	RehupPan();
}

void OpenALSoundInstance::SetVolume(double theVolume)
{
	mVolume = theVolume;
	RehupVolume();
}

void OpenALSoundInstance::SetPan(int thePosition)
{
	mPan = thePosition;
	RehupPan();
}


bool OpenALSoundInstance::Play(bool looping, bool autoRelease)
{
	Stop();

	mHasPlayed = true;
	mAutoRelease = autoRelease;

	if (mSoundBuffer == NULL)
	{
		return false;
	}
	if (looping)
		alSourcei(mSoundBuffer, AL_LOOPING, true);
	alSourcePlay(mSoundBuffer);
	return true;
}

void OpenALSoundInstance::Stop()
{
	if (mSoundBuffer != NULL)
	{
		alSourceStop(mSoundBuffer);
		mAutoRelease = false;
	}

}

void OpenALSoundInstance::AdjustPitch(double theNumSteps)
{
	if (mSoundBuffer != NULL)
	{
		double aFrequencyMult = pow(1.0594630943592952645618252949463, theNumSteps);
		double aNewFrequency = mDefaultFrequency * aFrequencyMult;
		if (aNewFrequency < 100)
			aNewFrequency = 100;
		if (aNewFrequency > 100000)
			aNewFrequency = 100000;

		alSourcef(mSoundBuffer, AL_PITCH, aFrequencyMult);
	}
}

bool OpenALSoundInstance::IsPlaying()
{
	if (!mHasPlayed)
		return false;

	if (mSoundBuffer == NULL)
		return false;

	ALint aStatus;
	alGetSourcei(mSoundBuffer, AL_SOURCE_STATE, &aStatus);
	if (aStatus == AL_PLAYING)
		return true;
	else
		return false;
}

bool OpenALSoundInstance::IsReleased()
{
	if ((!mReleased) && (mAutoRelease) && (mHasPlayed) && (!IsPlaying()))
		Release();

	return mReleased;
}

double OpenALSoundInstance::GetVolume()
{
	return mVolume;
}
