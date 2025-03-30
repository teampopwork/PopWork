#include "BassLoader.h"
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <string>

using namespace Sexy;

BASS_INSTANCE* Sexy::gBass = NULL;
static long gBassLoadCount = 0;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static void CheckBassFunction(unsigned int theFunc, const char *theName)
{
	if (theFunc==0)
	{
		std::string finalMessage = "function not found in BASS library";
		finalMessage = theName + finalMessage;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "BASS Error", finalMessage.c_str() , nullptr);
		exit(EXIT_FAILURE);
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
BASS_INSTANCE::BASS_INSTANCE(const char *dllName)
{
#if defined(_WIN32)
	mModule = LoadLibrary(dllName);
#else
	mModule = dlopen(dllName, RTLD_LAZY);
#endif
	if (!mModule)
		return;

#define GETPROC(_x) CheckBassFunction(*((unsigned int *)&_x) = (unsigned int)GetProcAddress(mModule, #_x),#_x)    

	GETPROC(BASS_Init);
	GETPROC(BASS_Free);
	GETPROC(BASS_Stop);
	GETPROC(BASS_Start);
	
	*((unsigned int*) &BASS_SetGlobalVolumes) = (unsigned int) GetProcAddress(mModule, "BASS_SetGlobalVolumes");
	*((unsigned int*) &BASS_SetVolume) = (unsigned int) GetProcAddress(mModule, "BASS_SetVolume");

	if ((BASS_SetVolume == NULL) && (BASS_SetGlobalVolumes == NULL))
	{
		//MessageBoxA(NULL,"Neither BASS_SetGlobalVolumes or BASS_SetVolume found in bass.dll","Error",MB_OK | MB_ICONERROR);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "BASS Error", "Neither BASS_SetGlobalVolumes or BASS_SetVolume found in bass.dll", nullptr);
		exit(0);
	}	

	*((unsigned int*) &BASS_SetConfig) = (unsigned int) GetProcAddress(mModule, "BASS_SetConfig");
	*((unsigned int*) &BASS_GetConfig) = (unsigned int) GetProcAddress(mModule, "BASS_GetConfig");

	GETPROC(BASS_GetVolume);
	GETPROC(BASS_GetInfo);

	GETPROC(BASS_GetVersion);
	GETPROC(BASS_ChannelStop);
	GETPROC(BASS_ChannelPlay);
	GETPROC(BASS_ChannelPause);
	//GETPROC(BASS_ChannelSetAttributes);
	//GETPROC(BASS_ChannelGetAttributes);
	GETPROC(BASS_ChannelSetPosition);
	GETPROC(BASS_ChannelGetPosition);
	GETPROC(BASS_ChannelIsActive);
	GETPROC(BASS_ChannelUpdate);
	GETPROC(BASS_ChannelGetAttribute);
	GETPROC(BASS_ChannelSetAttribute);
	GETPROC(BASS_ChannelSlideAttribute);
	GETPROC(BASS_ChannelIsSliding);
	GETPROC(BASS_ChannelGetLevel);	
	GETPROC(BASS_ChannelSetSync);
	GETPROC(BASS_ChannelRemoveSync);
	GETPROC(BASS_ChannelGetData);

	//NEW FUNCS
	GETPROC(BASS_SampleCreate);
	GETPROC(BASS_StreamCreate);
	GETPROC(BASS_ChannelGetAttribute);
	GETPROC(BASS_ChannelSetAttribute);
	GETPROC(BASS_ChannelGetInfo);
	GETPROC(BASS_ChannelFlags);

	// supported by BASS 1.1 and higher. Only work if the user has DX8 or higher though.
	GETPROC(BASS_FXSetParameters);
	GETPROC(BASS_FXGetParameters);
	GETPROC(BASS_ChannelSetFX);
	GETPROC(BASS_ChannelRemoveFX);

	GETPROC(BASS_MusicLoad);
	GETPROC(BASS_MusicFree);

	GETPROC(BASS_StreamCreateFile);
	GETPROC(BASS_StreamFree);

	GETPROC(BASS_SampleLoad);
	GETPROC(BASS_SampleFree);
	GETPROC(BASS_SampleSetInfo);
	GETPROC(BASS_SampleGetInfo);
	GETPROC(BASS_SampleGetChannel);
	GETPROC(BASS_SampleStop);

	GETPROC(BASS_ErrorGetCode);

	mVersion2 = BASS_SetConfig != NULL;
	if (mVersion2)
	{
		// Version 2 has different BASS_Init params
		*((unsigned int*) &BASS_Init2) = (unsigned int) BASS_Init;
		BASS_Init = NULL;

		*((unsigned int*) &BASS_MusicLoad2) = (unsigned int) BASS_MusicLoad;
		BASS_MusicLoad = NULL;

		// The following are only supported in 2.2 and higher
		*((unsigned int*) &BASS_PluginLoad) = (unsigned int) GetProcAddress(mModule, "BASS_PluginLoad");
		*((unsigned int*) &BASS_ChannelGetLength) = (unsigned int) GetProcAddress(mModule, "BASS_ChannelGetLength");

		// 2.1 and higher only
		*((unsigned int*) &BASS_ChannelPreBuf) = (unsigned int) GetProcAddress(mModule, "BASS_ChannelPreBuf");
	}
	else
	{
		BASS_PluginLoad = NULL;
		BASS_ChannelPreBuf = NULL;
	}

#undef GETPROC
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
BASS_INSTANCE::~BASS_INSTANCE()
{
	if (mModule)
	{
#if defined(_WIN32)
		FreeLibrary(mModule);
#else
		dlclose(mModule);
#endif
	}
}


BOOL BASS_INSTANCE::BASS_MusicSetAmplify(HMUSIC handle, DWORD amp)
{
	BASS_ChannelSetAttribute(handle, BASS_ATTRIB_MUSIC_AMPLIFY, amp);
	return true;
}


BOOL BASS_INSTANCE::BASS_MusicPlay(HMUSIC handle)
{
	return BASS_ChannelPlay(handle, true);
}


BOOL BASS_INSTANCE::BASS_MusicPlayEx(HMUSIC handle, DWORD pos, int flags, BOOL reset)
{
	BASS_ChannelStop(handle);
	BASS_ChannelSetPosition(handle, MAKELONG(pos, 0), BASS_POS_BYTE);
	BASS_ChannelFlags(handle, flags, -1);

	return BASS_ChannelPlay(handle, reset);
}


BOOL BASS_INSTANCE::BASS_ChannelResume(DWORD handle)
{
	return BASS_ChannelPlay(handle, false);
}

BOOL BASS_INSTANCE::BASS_StreamStop(DWORD handle, DWORD pos, int flags)
{
	//BASS_ChannelSetPosition(handle, MAKELONG(0,0), BASS_POS_BYTE);
	//BASS_ChannelFlags(handle, flags, -1);

	return BASS_ChannelStop(handle);
}

BOOL BASS_INSTANCE::BASS_StreamPlay(HSTREAM handle, BOOL flush, DWORD flags)
{
	BASS_ChannelStop(handle);
	BASS_ChannelSetPosition(handle, 0, BASS_POS_BYTE);
	BASS_ChannelFlags(handle, flags, -1);
	return BASS_ChannelPlay(handle, flush);
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Sexy::LoadBassDLL()
{
	InterlockedIncrement(&gBassLoadCount);
	if (gBass != NULL)
		return;

	gBass = new BASS_INSTANCE("./bass.dll");
	if (gBass->mModule == NULL)
	{
		fprintf(stderr, "Can't find BASS library.\n");
		exit(EXIT_FAILURE);
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Sexy::FreeBassDLL()
{
	if (gBass != NULL)
	{
		if (InterlockedDecrement(&gBassLoadCount) <= 0)
		{
			delete gBass;
			gBass = NULL;
		}
	}
}


