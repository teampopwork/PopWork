#pragma once

#include "../Common.h"
#include "CritSect.h"

namespace Sexy
{

class AutoCrit
{
	std::unique_lock<std::recursive_mutex> mLock;
public:
	AutoCrit(std::recursive_mutex theCritSec) :
		mLock(theCritSec)
	{ 
	}

	AutoCrit(CritSect& theCritSect) :
		mLock(theCritSect.mCriticalSection)
	{ 
	}

	~AutoCrit()
	{ 
	}
};

}
