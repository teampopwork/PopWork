#ifndef __OPENALSOUNDINTERFACE_H__
#define __OPENALSOUNDINTERFACE_H__
#ifdef _WIN32
#pragma once
#endif

#include "soundinstance.h"

#define AL_LIBTYPE_STATIC
#include <AL/al.h>
#include <AL/alc.h>

namespace PopWork
{
class OpenALSoundManager;

class OpenALSoundInstance : public SoundInstance
{
	friend class OpenALSoundManager;

  protected:
	OpenALSoundManager *mSoundManagerP;
	ALuint mSourceSoundBuffer;
	ALuint mSoundSource;
	bool mAutoRelease;
	bool mHasPlayed;
	bool mReleased;

	int mBasePan;
	double mBaseVolume;

	int mPan;
	double mVolume;

	double mDefaultFrequency;

  protected:
	void RehupVolume();
	void RehupPan();

  public:
	OpenALSoundInstance(OpenALSoundManager *theSoundManager, ALuint theSourceSound);
	~OpenALSoundInstance();

	virtual void Release();

	virtual void SetBaseVolume(double theBaseVolume);
	virtual void SetBasePan(int theBasePan);

	virtual void SetVolume(double theVolume);
	virtual void SetPan(int thePosition);
	virtual void AdjustPitch(double theNumSteps);

	virtual bool Play(bool looping, bool autoRelease);
	virtual void Stop();
	virtual bool IsPlaying();
	virtual bool IsReleased();
	virtual double GetVolume();
};

} // namespace PopWork

#endif