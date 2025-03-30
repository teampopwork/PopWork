#pragma once

#include "SoundManager.h"
#include "bass.h"

namespace Sexy
{
	class BassSoundInstance;

	class BassSoundManager : public SoundManager
	{
		friend class BassSoundInstance;
		friend class BassMusicInterface;

	protected:
		HSTREAM  mSourceSounds[MAX_SOURCE_SOUNDS];
		std::string mSourceFileNames[MAX_SOURCE_SOUNDS];
		ulong mSourceDataSizes[MAX_SOURCE_SOUNDS];
		double mBaseVolumes[MAX_SOURCE_SOUNDS];
		int mBasePans[MAX_SOURCE_SOUNDS];
		BassSoundInstance* mPlayingSounds[MAX_CHANNELS];
		double mMasterVolume;
		DWORD mLastReleaseTick;

	protected:
		int						FindFreeChannel();
		int						VolumeToDB(double theVolume);
		void					ReleaseFreeChannels();

	public:

		BassSoundManager();
		virtual ~BassSoundManager();

		virtual bool			Initialized();

		virtual bool			LoadSound(unsigned int theSfxID, const std::string& theFilename);
		virtual int				LoadSound(const std::string& theFilename);
		virtual void			ReleaseSound(unsigned int theSfxID);

		virtual void			SetVolume(double theVolume);
		virtual bool			SetBaseVolume(unsigned int theSfxID, double theBaseVolume);
		virtual bool			SetBasePan(unsigned int theSfxID, int theBasePan);

		virtual SoundInstance* GetSoundInstance(unsigned int theSfxID);

		virtual void			ReleaseSounds();
		virtual void			ReleaseChannels();

		virtual double			GetMasterVolume();
		virtual void			SetMasterVolume(double theVolume);

		virtual void			Flush();

		virtual void			SetCooperativeWindow(HWND theHWnd, bool isWindowed);
		virtual void			StopAllSounds();
		virtual int				GetFreeSoundId();
		virtual int				GetNumSounds();
	};

}