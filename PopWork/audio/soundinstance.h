#ifndef __SOUNDINSTANCE_H__
#define __SOUNDINSTANCE_H__
#ifdef _WIN32
#pragma once
#endif

#include "../Common.h"

namespace PopWork
{

class SoundInstance
{
public:
	SoundInstance() {}
	virtual ~SoundInstance() {}
	virtual void			Release() = NULL;
		
	virtual void			SetBaseVolume(double theBaseVolume) = NULL; 
	virtual void			SetBasePan(int theBasePan) = NULL;

	virtual void			AdjustPitch(double theNumSteps) = NULL;

	virtual void			SetVolume(double theVolume) = NULL; 
	virtual void			SetPan(int thePosition) = NULL; //-hundredth db to +hundredth db = left to right

	virtual bool			Play(bool looping, bool autoRelease) = NULL;	
	virtual void			Stop() = NULL;
	virtual bool			IsPlaying() = NULL;
	virtual bool			IsReleased() = NULL;
	virtual double			GetVolume() = NULL;
};

}

#endif