#pragma once

#include "SoundInstance.h"
#include "bass.h"

namespace Sexy
{
	class BassSoundInstance : public SoundInstance
	{
		friend class BassSoundManager;

	protected:
		BassSoundManager*		mSoundManagerP;
		HSTREAM 				mSourceSoundBuffer;
		HSTREAM					mSoundBuffer;
		bool					mAutoRelease;
		bool					mHasPlayed;
		bool					mReleased;

		int						mBasePan;
		double					mBaseVolume;

		int						mPan;
		double					mVolume;

		DWORD					mDefaultFrequency;


	protected:
		void					RehupVolume();
		void					RehupPan();

	public:
		BassSoundInstance(BassSoundManager* theSoundManager, HSTREAM  theSourceSound);
		~BassSoundInstance();

		virtual void			Release();

		virtual void			SetBaseVolume(double theBaseVolume);
		virtual void			SetBasePan(int theBasePan);

		virtual void			SetVolume(double theVolume);
		virtual void			SetPan(int thePosition); //-hundredth db to +hundredth db = left to right	
		virtual void			AdjustPitch(double theNumSteps);

		virtual bool			Play(bool looping, bool autoRelease);
		virtual void			Stop();
		virtual bool			IsPlaying();
		virtual bool			IsReleased();
		virtual double			GetVolume();

	private:

	};

}