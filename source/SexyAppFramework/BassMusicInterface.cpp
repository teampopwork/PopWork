#include "BassMusicInterface.h"
#include "BassLoader.h"
#include "..\PakLib\PakInterface.h"

using namespace Sexy;

#define BASS_CONFIG_BUFFER			0

BassMusicInfo::BassMusicInfo()
{	
	mVolume = 0.0;
	mVolumeAdd = 0.0;
	mVolumeCap = 1.0;
	mStopOnFade = false;
	mHMusic = NULL;
	mHStream = NULL;
}

BassMusicInterface::BassMusicInterface()
{
	LoadBassDLL();

	bool success = false;

	success = gBass->BASS_Init(1, 44100, 0, 0, NULL);
	gBass->BASS_SetConfig(BASS_CONFIG_BUFFER, 2000);

	mMaxMusicVolume = 40;
	mMusicLoadFlags = BASS_MUSIC_LOOP | BASS_MUSIC_RAMP;
}

BassMusicInterface::~BassMusicInterface()
{

}

bool BassMusicInterface::LoadMusic(int theSongId, const std::string& theFileName)
{
	HMUSIC aHMusic = NULL;
	HSTREAM aStream = NULL;
	
	std::string anExt;
	int aDotPos = theFileName.find_last_of('.');
	if (aDotPos!=std::string::npos)
		anExt = StringToLower(theFileName.substr(aDotPos+1));

	if (anExt=="wav" || anExt=="ogg" || anExt=="mp3")
		aStream = gBass->BASS_StreamCreateFile(FALSE, (void*) theFileName.c_str(), 0, 0, 0);
	else
	{
		PFILE* aFP = p_fopen(theFileName.c_str(), "rb");
		if (aFP == NULL)
			return false;

		p_fseek(aFP, 0, SEEK_END);
		int aSize = p_ftell(aFP);
		p_fseek(aFP, 0, SEEK_SET);

		uchar* aData = new uchar[aSize];
		p_fread(aData, 1, aSize, aFP);
		p_fclose(aFP);

		aHMusic = gBass->BASS_MusicLoad(FALSE, (void*)theFileName.c_str(), 0, 0, BASS_MUSIC_LOOP | BASS_MUSIC_RAMP, 0);

		delete aData;
	}

	if (aHMusic==NULL && aStream==NULL)
		return false;
	
	BassMusicInfo aMusicInfo;	
	aMusicInfo.mHMusic = aHMusic;
	aMusicInfo.mHStream = aStream;
	mMusicMap.insert(BassMusicMap::value_type(theSongId, aMusicInfo));

	return true;	
}

void BassMusicInterface::PlayMusic(int theSongId, int theOffset, bool noLoop)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
		aMusicInfo->mVolume = aMusicInfo->mVolumeCap;
		aMusicInfo->mVolumeAdd = 0.0;
		aMusicInfo->mStopOnFade = noLoop;   
		gBass->BASS_ChannelSetAttribute(aMusicInfo->GetHandle(), BASS_ATTRIB_MUSIC_VOL_GLOBAL, (int) (aMusicInfo->mVolume*100));			   

		gBass->BASS_ChannelStop(aMusicInfo->GetHandle());
		if (aMusicInfo->mHMusic)
		{
			gBass->BASS_MusicPlayEx(aMusicInfo->mHMusic, theOffset, BASS_MUSIC_POSRESET | BASS_MUSIC_RAMP | (noLoop ? 0 : BASS_MUSIC_LOOP), TRUE);
		}
		else
		{
			BOOL flush = theOffset == -1 ? FALSE : TRUE;
			gBass->BASS_StreamPlay(aMusicInfo->mHStream, flush, noLoop ? 0 : BASS_MUSIC_LOOP);
			if (theOffset > 0)
				gBass->BASS_ChannelSetPosition(aMusicInfo->mHStream, theOffset, BASS_POS_BYTE);
		}
	}
}

void BassMusicInterface::StopMusic(int theSongId)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
		aMusicInfo->mVolume = 0.0;
		gBass->BASS_ChannelStop(aMusicInfo->GetHandle());
	}
}

void BassMusicInterface::StopAllMusic()
{
	BassMusicMap::iterator anItr = mMusicMap.begin();
	while (anItr != mMusicMap.end())
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
		aMusicInfo->mVolume = 0.0;
		gBass->BASS_ChannelStop(aMusicInfo->GetHandle());
		++anItr;
	}
}

void BassMusicInterface::UnloadMusic(int theSongId)
{
	StopMusic(theSongId);
	
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
		if (aMusicInfo->mHStream)
			gBass->BASS_StreamFree(aMusicInfo->mHStream);
		else if (aMusicInfo->mHMusic)
			gBass->BASS_MusicFree(aMusicInfo->mHMusic);

		mMusicMap.erase(anItr);
	}
}

void BassMusicInterface::UnloadAllMusic()
{
	StopAllMusic();
	for (BassMusicMap::iterator anItr = mMusicMap.begin(); anItr != mMusicMap.end(); ++anItr)
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
		if (aMusicInfo->mHStream)
			gBass->BASS_StreamFree(aMusicInfo->mHStream);
		else if (aMusicInfo->mHMusic)
			gBass->BASS_MusicFree(aMusicInfo->mHMusic);
	}
	mMusicMap.clear();
}

void BassMusicInterface::PauseMusic(int theSongId)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
		gBass->BASS_ChannelPause(aMusicInfo->GetHandle());
	}
}

void BassMusicInterface::PauseAllMusic()
{
	for (BassMusicMap::iterator anItr = mMusicMap.begin(); anItr != mMusicMap.end(); ++anItr)
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
		if (gBass->BASS_ChannelIsActive(aMusicInfo->GetHandle()) == BASS_ACTIVE_PLAYING)
			gBass->BASS_ChannelPause(aMusicInfo->GetHandle());
	}
}

void BassMusicInterface::ResumeAllMusic()
{
	for (BassMusicMap::iterator anItr = mMusicMap.begin(); anItr != mMusicMap.end(); ++anItr)
	{
		BassMusicInfo* aMusicInfo = &anItr->second;

		if (gBass->BASS_ChannelIsActive(aMusicInfo->GetHandle()) == BASS_ACTIVE_PAUSED)
			gBass->BASS_ChannelResume(aMusicInfo->GetHandle());
	}
}

void BassMusicInterface::ResumeMusic(int theSongId)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
		gBass->BASS_ChannelResume(aMusicInfo->GetHandle());
	}
}

void BassMusicInterface::FadeIn(int theSongId, int theOffset, double theSpeed, bool noLoop)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
				
		aMusicInfo->mVolumeAdd = theSpeed;
		aMusicInfo->mStopOnFade = noLoop;

		gBass->BASS_ChannelStop(aMusicInfo->GetHandle());
		gBass->BASS_ChannelSetAttribute(aMusicInfo->GetHandle(), BASS_ATTRIB_MUSIC_VOL_GLOBAL, (int)(aMusicInfo->mVolume * 100));
		if (aMusicInfo->mHMusic)
		{
			if (theOffset == -1)
				gBass->BASS_MusicPlay(aMusicInfo->mHMusic);
			else
			{
				gBass->BASS_MusicPlayEx(aMusicInfo->mHMusic, theOffset, BASS_MUSIC_RAMP | (noLoop ? 0 : BASS_MUSIC_LOOP), TRUE);
			}
		}
		else
		{
			BOOL flush = theOffset == -1 ? FALSE : TRUE;
			gBass->BASS_StreamPlay(aMusicInfo->mHStream, flush, noLoop ? 0 : BASS_MUSIC_LOOP);
			if (theOffset > 0)
				gBass->BASS_ChannelSetPosition(aMusicInfo->mHStream, theOffset, BASS_POS_BYTE);
		}

	}
}

void BassMusicInterface::FadeOut(int theSongId, bool stopSong, double theSpeed)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{		
		BassMusicInfo* aMusicInfo = &anItr->second;
		
		if (aMusicInfo->mVolume != 0.0)
		{
			aMusicInfo->mVolumeAdd = -theSpeed;			
		}

		aMusicInfo->mStopOnFade = stopSong;
	}
}

void BassMusicInterface::FadeOutAll(bool stopSong, double theSpeed)
{
	BassMusicMap::iterator anItr = mMusicMap.begin();
	while (anItr != mMusicMap.end())
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
				
		aMusicInfo->mVolumeAdd = -theSpeed;
		aMusicInfo->mStopOnFade = stopSong;

		++anItr;
	}
}

void BassMusicInterface::SetVolume(double theVolume)
{
	int aVolume = (int)(theVolume * 1000);
	
	gBass->BASS_SetConfig(/*BASS_CONFIG_GVOL_MUSIC*/6, (int)aVolume);
	gBass->BASS_SetConfig(/*BASS_CONFIG_GVOL_STREAM*/5, (int)aVolume);
}

void BassMusicInterface::SetSongVolume(int theSongId, double theVolume)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{		
		BassMusicInfo* aMusicInfo = &anItr->second;

		aMusicInfo->mVolume = theVolume;
		gBass->BASS_ChannelSetAttribute(aMusicInfo->GetHandle(), BASS_ATTRIB_MUSIC_VOL_GLOBAL, (int)(aMusicInfo->mVolume * 100));
	}
}

void BassMusicInterface::SetSongMaxVolume(int theSongId, double theMaxVolume)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{		
		BassMusicInfo* aMusicInfo = &anItr->second;

		aMusicInfo->mVolumeCap = theMaxVolume;
		aMusicInfo->mVolume = min(aMusicInfo->mVolume, theMaxVolume);
		gBass->BASS_ChannelSetAttribute(aMusicInfo->GetHandle(), BASS_ATTRIB_MUSIC_VOL_GLOBAL, (int)(aMusicInfo->mVolume * 100));
	}
}

bool BassMusicInterface::IsPlaying(int theSongId)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{		
		BassMusicInfo* aMusicInfo = &anItr->second;
		return gBass->BASS_ChannelIsActive(aMusicInfo->GetHandle()) == BASS_ACTIVE_PLAYING;
	}

	return false;
}

void BassMusicInterface::SetMusicAmplify(int theSongId, double theAmp)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{		
		BassMusicInfo* aMusicInfo = &anItr->second;		
		gBass->BASS_MusicSetAmplify(aMusicInfo->GetHandle(), (int) (theAmp * 100));
	}
}

void BassMusicInterface::Update()
{
	BassMusicMap::iterator anItr = mMusicMap.begin();
	while (anItr != mMusicMap.end())
	{
		BassMusicInfo* aMusicInfo = &anItr->second;

		if (aMusicInfo->mVolumeAdd != 0.0)
		{
			aMusicInfo->mVolume += aMusicInfo->mVolumeAdd;
			
			if (aMusicInfo->mVolume > aMusicInfo->mVolumeCap)
			{
				aMusicInfo->mVolume = aMusicInfo->mVolumeCap;
				aMusicInfo->mVolumeAdd = 0.0;
			}
			else if (aMusicInfo->mVolume < 0.0)
			{
				aMusicInfo->mVolume = 0.0;
				aMusicInfo->mVolumeAdd = 0.0;

				if (aMusicInfo->mStopOnFade)
					gBass->BASS_ChannelStop(aMusicInfo->GetHandle());
			}

			gBass->BASS_ChannelSetAttribute(aMusicInfo->GetHandle(), BASS_ATTRIB_MUSIC_VOL_GLOBAL, (int)(aMusicInfo->mVolume * 100));
		}

		++anItr;
	}	
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
// MODs are broken up into several orders or patterns. This returns the current order a song is on.
int BassMusicInterface::GetMusicOrder(int theSongId)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{		
		BassMusicInfo* aMusicInfo = &anItr->second;
		int aPosition = gBass->BASS_ChannelGetLength(aMusicInfo->GetHandle(), BASS_POS_BYTE);
		return aPosition;
	}
	return -1;
}