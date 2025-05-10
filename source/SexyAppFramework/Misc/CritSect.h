#pragma once

#include "../Common.h"
#include <mutex>

//We are using std::recursive_mutex because the old Win32 CRITICAL_SECTION was recursive by default.

class CritSync;
namespace Sexy
{

class CritSect 
{
private:
	std::recursive_mutex mCriticalSection;
	friend class AutoCrit;

public:
	CritSect(void) {};
	~CritSect(void) {};
};

}