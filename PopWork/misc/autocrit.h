#ifndef __AUTOCRIT_H__
#define __AUTOCRIT_H__
#ifdef _WIN32
#pragma once
#endif

#include "common.h"
#include "critsect.h"

namespace PopWork
{

class AutoCrit
{
	std::unique_lock<std::recursive_mutex> mLock;

  public:
	AutoCrit(std::recursive_mutex theCritSec) : mLock(theCritSec)
	{
	}

	AutoCrit(CritSect &theCritSect) : mLock(theCritSect.mCriticalSection)
	{
	}

	~AutoCrit()
	{
	}
};

} // namespace PopWork

#endif