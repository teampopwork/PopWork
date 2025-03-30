#include "BassSoundInstance.h"
#include "BassSoundManager.h"
#include "BassLoader.h"
#include <iostream>

using namespace Sexy;

struct StreamCloneData {
	std::vector<char> data;
	size_t position = 0;
};

// Custom callback to feed the new stream
DWORD CALLBACK StreamProc(HSTREAM handle, void* buffer, DWORD length, void* user)
{
	StreamCloneData* cloneData = (StreamCloneData*)user;

	// Check if we have remaining data
	if (cloneData->position >= cloneData->data.size())
		return 0; // End of stream

	// Copy the data to the buffer
	DWORD bytesToCopy = min(length, (DWORD)(cloneData->data.size() - cloneData->position));
	memcpy(buffer, cloneData->data.data() + cloneData->position, bytesToCopy);
	cloneData->position += bytesToCopy;

	return bytesToCopy;
}

BassSoundInstance::BassSoundInstance(BassSoundManager* theSoundManager, HSTREAM theSourceSound)
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
	if (mSourceSoundBuffer != NULL && gBass != NULL)
	{

		float volume = 0.0f;
		float pan = 0.0f;
		float freq = 0.0f;
		float length = 0.0f;
		gBass->BASS_ChannelGetAttribute(mSourceSoundBuffer, BASS_ATTRIB_VOL, volume);
		gBass->BASS_ChannelGetAttribute(mSourceSoundBuffer, BASS_ATTRIB_PAN, pan);
		gBass->BASS_ChannelGetAttribute(mSourceSoundBuffer, BASS_ATTRIB_FREQ, freq);
		length = gBass->BASS_ChannelGetLength(mSourceSoundBuffer, BASS_POS_BYTE);
		gBass->BASS_ChannelGetInfo(mSourceSoundBuffer, &aInfo);
		mDefaultFrequency = aInfo.freq;

		std::vector<char> buffer(length);
		if (gBass->BASS_ChannelGetData(mSourceSoundBuffer, buffer.data(), length) == -1) {
			//return;
		}

		StreamCloneData* cloneData = new StreamCloneData{ buffer, 0 };

		// Create a new stream from memory with a custom callback
		HSTREAM newStream = gBass->BASS_StreamCreate(aInfo.freq, aInfo.chans, aInfo.flags & ~BASS_STREAM_DECODE, StreamProc, cloneData);

		gBass->BASS_ChannelSetAttribute(newStream, BASS_ATTRIB_VOL, volume);
		gBass->BASS_ChannelSetAttribute(newStream, BASS_ATTRIB_PAN, pan);
		gBass->BASS_ChannelSetAttribute(newStream, BASS_ATTRIB_FREQ, freq);

		mSoundBuffer = newStream;
	}

	RehupVolume();
}

BassSoundInstance::~BassSoundInstance()
{
	gBass->BASS_StreamFree(mSoundBuffer);
}

void BassSoundInstance::RehupVolume()
{
	if (mSoundBuffer != NULL)
	{
		gBass->BASS_ChannelSetAttribute(mSoundBuffer, BASS_ATTRIB_VOL, mVolume * mBaseVolume * mSoundManagerP->mMasterVolume);
	}
}

void BassSoundInstance::RehupPan()
{
	if (mSoundBuffer != NULL)
		gBass->BASS_ChannelSetAttribute(mSoundBuffer, BASS_ATTRIB_PAN, mBasePan + mPan);
}

void BassSoundInstance::Release()
{
	Stop();
	mReleased = true;
}

void BassSoundInstance::SetBaseVolume(double theBaseVolume)
{
	mBaseVolume = theBaseVolume;
	RehupVolume();
}

void BassSoundInstance::SetBasePan(int theBasePan)
{
	mBasePan = theBasePan;
	RehupPan();
}

void BassSoundInstance::SetVolume(double theVolume)
{
	mVolume = theVolume;
	RehupVolume();
}

void BassSoundInstance::SetPan(int thePosition)
{
	mPan = thePosition;
	RehupPan();
}


bool BassSoundInstance::Play(bool looping, bool autoRelease)
{
	Stop();

	mHasPlayed = true;
	mAutoRelease = autoRelease;

	if (mSoundBuffer == NULL)
	{
		return false;
	}

	if (gBass->BASS_StreamPlay(mSourceSoundBuffer, true, looping ? BASS_SAMPLE_LOOP : 0))
	{

	}
	else
	{
		std::string aTest = std::to_string(gBass->BASS_ErrorGetCode());
	}
	return true;
}

void BassSoundInstance::Stop()
{
	if (mSoundBuffer != NULL)
	{
		if (gBass->BASS_ChannelStop(mSoundBuffer))
		{
			gBass->BASS_ChannelSetPosition(mSoundBuffer, 0, BASS_POS_BYTE);
		}
		gBass->BASS_ChannelPause(mSoundBuffer);
		mAutoRelease = false;
	}

}

void BassSoundInstance::AdjustPitch(double theNumSteps)
{
	if (mSoundBuffer != NULL)
	{
		double aFrequencyMult = pow(1.0594630943592952645618252949463, theNumSteps);
		double aNewFrequency = mDefaultFrequency * aFrequencyMult;
		if (aNewFrequency < 100)
			aNewFrequency = 100;
		if (aNewFrequency > 100000)
			aNewFrequency = 100000;

		gBass->BASS_ChannelSetAttribute(mSoundBuffer, BASS_ATTRIB_FREQ, aNewFrequency);
	}
}

bool BassSoundInstance::IsPlaying()
{
	if (!mHasPlayed)
		return false;

	if (mSoundBuffer == NULL)
		return false;

	DWORD aStatus;
	if (gBass->BASS_ChannelIsActive(mSoundBuffer) == BASS_ACTIVE_PLAYING)
		return true;
	else
		return false;
}

bool BassSoundInstance::IsReleased()
{
	if ((!mReleased) && (mAutoRelease) && (mHasPlayed) && (!IsPlaying()))
		Release();

	return mReleased;
}

double BassSoundInstance::GetVolume()
{
	return mVolume;
}
