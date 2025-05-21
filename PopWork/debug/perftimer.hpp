#ifndef __PERFTIMER_HPP__
#define __PERFTIMER_HPP__
#ifdef _WIN32
#pragma once
#endif

#include "common.hpp"

#ifdef _WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif

namespace PopWork
{

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class PerfTimer
{
  protected:
	int64_t mStart;
	double mDuration;
	bool mRunning;

	void CalcDuration();

  public:
	PerfTimer();
	void Start();
	void Stop();

	double GetDuration();

	static int64_t GetCPUSpeed(); // in Hz
	static int GetCPUSpeedMHz();
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class PopWorkPerf
{
  public:
	static void BeginPerf(bool measurePerfOverhead = false);
	static void EndPerf();
	static bool IsPerfOn();

	static void StartTiming(const char *theName);
	static void StopTiming(const char *theName);

	static std::string GetResults();
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class PopWorkAutoPerf
{
  public:
	const char *mName;
	bool mIsStarted;

	PopWorkAutoPerf(const char *theName) : mName(theName), mIsStarted(true)
	{
		PopWorkPerf::StartTiming(theName);
	}
	PopWorkAutoPerf(const char *theName, bool doStart) : mIsStarted(doStart), mName(theName)
	{
		if (doStart)
			PopWorkPerf::StartTiming(theName);
	}

	~PopWorkAutoPerf()
	{
		Stop();
	}

	void Start()
	{
		if (!mIsStarted)
		{
			mIsStarted = true;
			PopWorkPerf::StartTiming(mName);
		}
	}

	void Stop()
	{
		if (mIsStarted)
		{
			PopWorkPerf::StopTiming(mName);
			mIsStarted = false;
		}
	}
};

} // namespace PopWork

#pragma warning(push)
#pragma warning(disable : 4005)

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// #define POPWORK_PERF_ENABLED
#if defined(POPWORK_PERF_ENABLED) && !defined(RELEASEFINAL)

#define POPWORK_PERF_BEGIN(theName) PopWorkPerf::StartTiming(theName)
#define POPWORK_PERF_END(theName) PopWorkPerf::StopTiming(theName)
#define POPWORK_AUTO_PERF_MULTI(theName, theSuffix) PopWorkAutoPerf anAutoPerf##theSuffix(theName)
#define POPWORK_AUTO_PERF_2(theName, theSuffix) POPWORK_AUTO_PERF_MULTI(theName, theSuffix)
#define POPWORK_AUTO_PERFL(theName)                                                                                    \
	POPWORK_AUTO_PERF_2(theName, __LINE__) // __LINE__ doesn't work correctly if Edit-and-Continue (/ZI) is enabled
#define POPWORK_AUTO_PERF(theName) POPWORK_AUTO_PERF_2(theName, UNIQUE)

#define POPWORK_PERF_BEGIN_COND(theName, theCond)                                                                      \
	if (theCond)                                                                                                       \
	PopWorkPerf::StartTiming(theName)
#define POPWORK_PERF_END_COND(theName, theCond)                                                                        \
	if (theCond)                                                                                                       \
	PopWorkPerf::StopTiming(theName)
#define POPWORK_AUTO_PERF_MULTI_COND(theName, theSuffix, theCond)                                                      \
	PopWorkAutoPerf anAutoPerf##theSuffix(theName, theCond);
#define POPWORK_AUTO_PERF_COND_2(theName, theSuffix, theCond) POPWORK_AUTO_PERF_MULTI_COND(theName, theSuffix, theCond);
#define POPWORK_AUTO_PERF_CONDL(theName) POPWORK_AUTO_PERF_COND_2(theName, __LINE__, theCond)
#define POPWORK_AUTO_PERF_COND(theName) POPWORK_AUTO_PERF_COND_2(theName, UNIQUE, theCond)

#else

#define POPWORK_PERF_BEGIN(theName)
#define POPWORK_PERF_END(theName)
#define POPWORK_AUTO_PERF_MULTI(theName, theSuffix)
#define POPWORK_AUTO_PERF(theName)

#define POPWORK_PERF_BEGIN_COND(theName, theCond)
#define POPWORK_PERF_END_COND(theName, theCond)
#define POPWORK_AUTO_PERF_MULTI_COND(theName, theSuffix, theCond)
#define POPWORK_AUTO_PERF_COND(theName)

#endif

#pragma warning(pop)

#endif