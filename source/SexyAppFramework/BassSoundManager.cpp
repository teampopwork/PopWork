#include "BassSoundManager.h"
#include "BassSoundInstance.h"
#include "BassLoader.h"
#include "../PakLib/PakInterface.h"
#include "Common.h"
#include <SDL3/SDL.h>

using namespace Sexy;

#define USE_OGG_LIB


#ifdef USE_OGG_LIB
#include "ogg/ivorbiscodec.h"
#include "ogg/ivorbisfile.h"
#endif

#define SOUND_FLAGS (DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME |  DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLFREQUENCY)

BassSoundManager::BassSoundManager()
{
	if (gBass == NULL)
		LoadBassDLL();

	int i;

	for (i = 0; i < MAX_SOURCE_SOUNDS; i++)
	{
		mSourceSounds[i] = NULL;
		mBaseVolumes[i] = 1;
		mBasePans[i] = 0;
	}

	for (i = 0; i < MAX_CHANNELS; i++)
		mPlayingSounds[i] = NULL;

	mMasterVolume = 1.0;
}

BassSoundManager::~BassSoundManager()
{
	ReleaseSounds();
}

bool BassSoundManager::Initialized()
{
	return gBass != NULL;
}

int BassSoundManager::FindFreeChannel()
{
	DWORD aTick = SDL_GetTicks();
	if (aTick - mLastReleaseTick > 1000)
	{
		ReleaseFreeChannels();
		mLastReleaseTick = aTick;
	}

	for (int i = 0; i < MAX_CHANNELS; i++)
	{
		if (mPlayingSounds[i] == NULL)
			return i;

		if (mPlayingSounds[i]->IsReleased())
		{
			delete mPlayingSounds[i];
			mPlayingSounds[i] = NULL;
			return i;
		}
	}

	return -1;
}

int BassSoundManager::VolumeToDB(double theVolume)
{
	int aVol = (int)((log10(1 + theVolume * 9) - 1.0) * 2333);
	if (aVol < -2000)
		aVol = -10000;

	return aVol;
}

void BassSoundManager::ReleaseFreeChannels()
{
	for (int i = 0; i < MAX_CHANNELS; i++)
		if (mPlayingSounds[i] != NULL && mPlayingSounds[i]->IsReleased())
		{
			delete mPlayingSounds[i];
			mPlayingSounds[i] = NULL;
		}
}

bool BassSoundManager::LoadSound(unsigned int theSfxID, const std::string& theFilename)
{
	if ((theSfxID < 0) || (theSfxID >= MAX_SOURCE_SOUNDS))
		return false;

	ReleaseSound(theSfxID);

	mSourceFileNames[theSfxID] = theFilename;

	std::string aFilename = theFilename;

	std::string aPossibleStrings[3] = { ".wav" , ".ogg" ,".mp3" };
	
	HSTREAM aStream = gBass->BASS_StreamCreateFile(FALSE, theFilename.c_str(), 0, 0, 0);
	if (aStream) {
		mSourceSounds[theSfxID] = aStream;
		mSourceFileNames[theSfxID] = theFilename;
		return true;
	}

	std::vector<std::string> extensions = { ".wav", ".ogg", ".mp3" };
	PFILE* aFP = nullptr;
	std::string fullPath;

	for (const auto& ext : extensions) {
		fullPath = theFilename + ext;
		aFP = p_fopen(fullPath.c_str(), "rb");
		if (aFP) break;
	}


	p_fseek(aFP, 0, SEEK_END);
	int aSize = p_ftell(aFP);
	p_fseek(aFP, 0, SEEK_SET);

	uchar* aData = new uchar[aSize];
	p_fread(aData, 1, aSize, aFP);
	p_fclose(aFP);

	aStream = gBass->BASS_StreamCreateFile(TRUE, (void*)aData, 0, aSize, 0);
	if (!aStream) {
		printf("Error: BASS failed to load %s from memory\n", fullPath.c_str());
		return false;
	}

	mSourceSounds[theSfxID] = aStream;
	mSourceFileNames[theSfxID] = theFilename;
	mSourceDataSizes[theSfxID] = aSize;

	return true;
}

int BassSoundManager::LoadSound(const std::string& theFilename)
{
	int i;
	for (i = 0; i < MAX_SOURCE_SOUNDS; i++)
		if (mSourceFileNames[i] == theFilename)
			return i;

	for (i = MAX_SOURCE_SOUNDS - 1; i >= 0; i--)
	{
		if (mSourceSounds[i] == NULL)
		{
			if (!LoadSound(i, theFilename))
				return -1;
			else
				return i;
		}
	}

	return -1;
}

void BassSoundManager::ReleaseSound(unsigned int theSfxID)
{
	if (mSourceSounds[theSfxID] != NULL)
	{
		mSourceSounds[theSfxID] = NULL;
		mSourceFileNames[theSfxID] = "";
	}
}

void BassSoundManager::StopAllSounds()
{
	for (int i = 0; i < MAX_CHANNELS; i++)
		if (mPlayingSounds[i] != NULL)
		{
			bool isAutoRelease = mPlayingSounds[i]->mAutoRelease;
			mPlayingSounds[i]->Stop();
			mPlayingSounds[i]->mAutoRelease = isAutoRelease;
		}
}

int BassSoundManager::GetFreeSoundId()
{
	for (int i = 0; i < MAX_SOURCE_SOUNDS; i++)
	{
		if (mSourceSounds[i] == NULL)
			return i;
	}

	return -1;
}

int BassSoundManager::GetNumSounds()
{
	int aCount = 0;
	for (int i = 0; i < MAX_SOURCE_SOUNDS; i++)
	{
		if (mSourceSounds[i] != NULL)
			aCount++;
	}

	return aCount;
}

void BassSoundManager::SetVolume(double theVolume)
{
	mMasterVolume = theVolume;

	for (int i = 0; i < MAX_CHANNELS; i++)
		if (mPlayingSounds[i] != NULL)
			mPlayingSounds[i]->RehupVolume();
}

bool BassSoundManager::SetBaseVolume(unsigned int theSfxID, double theBaseVolume)
{
	if ((theSfxID < 0) || (theSfxID >= MAX_SOURCE_SOUNDS))
		return false;

	mBaseVolumes[theSfxID] = theBaseVolume;
	return true;
}

bool BassSoundManager::SetBasePan(unsigned int theSfxID, int theBasePan)
{
	if ((theSfxID < 0) || (theSfxID >= MAX_SOURCE_SOUNDS))
		return false;

	mBasePans[theSfxID] = theBasePan;
	return true;
}

SoundInstance* BassSoundManager::GetSoundInstance(unsigned int theSfxID)
{
	if (theSfxID > MAX_SOURCE_SOUNDS)
		return NULL;

	int aFreeChannel = FindFreeChannel();
	if (aFreeChannel < 0)
		return NULL;

	if (mSourceSounds[theSfxID] == NULL)
		return NULL;

	mPlayingSounds[aFreeChannel] = new BassSoundInstance(this, mSourceSounds[theSfxID]);

	mPlayingSounds[aFreeChannel]->SetBasePan(mBasePans[theSfxID]);
	mPlayingSounds[aFreeChannel]->SetBaseVolume(mBaseVolumes[theSfxID]);

	return mPlayingSounds[aFreeChannel];
}

void BassSoundManager::ReleaseSounds()
{
	for (int i = 0; i < MAX_SOURCE_SOUNDS; i++)
		if (mSourceSounds[i] != NULL)
		{
			gBass->BASS_StreamFree(mSourceSounds[i]);
			mSourceSounds[i] = NULL;
		}
}

void BassSoundManager::ReleaseChannels()
{
	for (int i = 0; i < MAX_CHANNELS; i++)
		if (mPlayingSounds[i] != NULL)
		{
			delete mPlayingSounds[i];
			mPlayingSounds[i] = NULL;
		}
}

double BassSoundManager::GetMasterVolume()
{
	return mMasterVolume;
}

void BassSoundManager::SetMasterVolume(double theVolume)
{
	mMasterVolume = theVolume;
}

void BassSoundManager::Flush()
{
}

void BassSoundManager::SetCooperativeWindow(HWND theHWnd, bool isWindowed)
{
}
#undef SOUND_FLAGS
