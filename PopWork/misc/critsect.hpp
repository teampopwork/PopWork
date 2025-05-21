#ifndef __CRITSECT_HPP__
#define __CRITSECT_HPP__
#ifdef _WIN32
#pragma once
#endif

#include "common.hpp"
#include <mutex>

// We are using std::recursive_mutex because the old Win32 CRITICAL_SECTION was recursive by default.

class CritSync;
namespace PopWork
{

class CritSect
{
  private:
	std::recursive_mutex mCriticalSection;
	friend class AutoCrit;

  public:
	CritSect(void){};
	~CritSect(void){};
};

} // namespace PopWork

#endif