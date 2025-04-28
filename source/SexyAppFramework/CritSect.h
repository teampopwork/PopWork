#pragma once

#include "Common.h"

class CritSync;

namespace Sexy
{

class CritSect 
{
private:
	CRITICAL_SECTION mCriticalSection;
	friend class AutoCrit;

public:
	CritSect(void);
	~CritSect(void);
};

}

