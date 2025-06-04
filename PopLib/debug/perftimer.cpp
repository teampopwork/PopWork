#include "perftimer.hpp"
#include <map>
#include <SDL3/SDL.h>

using namespace PopLib;

static int64_t gCPUSpeed = 0;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
PerfTimer::PerfTimer()
{
	mDuration = 0;
	mStart = 0;
	mRunning = false;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void PerfTimer::CalcDuration()
{
	int64_t anEnd = SDL_GetPerformanceCounter();
	int64_t aFreq = SDL_GetPerformanceFrequency();
	mDuration = ((anEnd - mStart) * 1000) / (double)aFreq;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void PerfTimer::Start()
{
	mRunning = true;
	mStart = SDL_GetPerformanceCounter();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void PerfTimer::Stop()
{
	if (mRunning)
	{
		CalcDuration();
		mRunning = false;
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
double PerfTimer::GetDuration()
{
	if (mRunning)
		CalcDuration();

	return mDuration;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int64_t PerfTimer::GetCPUSpeed()
{

	if (gCPUSpeed <= 0)
	{
		// gCPUSpeed = CalcCPUSpeed();
		//	if (gCPUSpeed<=0)
		gCPUSpeed = 1;
	}

	return gCPUSpeed;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int PerfTimer::GetCPUSpeedMHz()
{
	return (int)(gCPUSpeed / 1000000);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
struct PerfInfo
{
	const char *mPerfName;
	mutable int64_t mStartTime;
	mutable int64_t mDuration;
	mutable double mMillisecondDuration;
	mutable double mLongestCall;
	mutable int mStartCount;
	mutable int mCallCount;

	PerfInfo(const char *theName)
		: mPerfName(theName), mStartTime(0), mDuration(0), mStartCount(0), mCallCount(0), mLongestCall(0)
	{
	}

	bool operator<(const PerfInfo &theInfo) const
	{
#ifdef _WIN32
		return stricmp(mPerfName, theInfo.mPerfName) < 0;
#else
		return strcasecmp(mPerfName, theInfo.mPerfName) < 0;
#endif
	}
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
typedef std::set<PerfInfo> PerfInfoSet;
static PerfInfoSet gPerfInfoSet;
static bool gPerfOn = false;
static int64_t gStartTime;
static int64_t gCollateTime;
double gDuration = 0;
int gStartCount = 0;
int gPerfRecordTop = 0;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
struct PerfRecord
{
	const char *mName;
	int64_t mTime;
	bool mStart;

	PerfRecord()
	{
	}
	PerfRecord(const char *theName, bool start) : mName(theName), mStart(start), mTime(SDL_GetPerformanceFrequency()){};
};
typedef std::vector<PerfRecord> PerfRecordVector;
PerfRecordVector gPerfRecordVector;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static inline void InsertPerfRecord(PerfRecord &theRecord)
{
	if (theRecord.mStart)
	{
		PerfInfoSet::iterator anItr = gPerfInfoSet.insert(PerfInfo(theRecord.mName)).first;
		anItr->mCallCount++;

		if (++anItr->mStartCount == 1)
			anItr->mStartTime = theRecord.mTime;
	}
	else
	{
		PerfInfoSet::iterator anItr = gPerfInfoSet.find(theRecord.mName);
		if (anItr != gPerfInfoSet.end())
		{
			if (--anItr->mStartCount == 0)
			{
				int64_t aDuration = theRecord.mTime - anItr->mStartTime;
				anItr->mDuration += aDuration;

				if (aDuration > anItr->mLongestCall)
					anItr->mLongestCall = (double)aDuration;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static inline void CollatePerfRecords()
{
	int64_t aTime1, aTime2;
	aTime1 = SDL_GetPerformanceCounter();

	for (int i = 0; i < gPerfRecordTop; i++)
		InsertPerfRecord(gPerfRecordVector[i]);

	gPerfRecordTop = 0;
	aTime2 = SDL_GetPerformanceCounter();
	gCollateTime += aTime2 - aTime1;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static inline void PushPerfRecord(PerfRecord &theRecord)
{
	if (gPerfRecordTop >= (int)gPerfRecordVector.size())
		gPerfRecordVector.push_back(theRecord);
	else
		gPerfRecordVector[gPerfRecordTop] = theRecord;

	++gPerfRecordTop;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool Perf::IsPerfOn()
{
	return gPerfOn;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Perf::BeginPerf(bool measurePerfOverhead)
{
	gPerfInfoSet.clear();
	gPerfRecordTop = 0;
	gStartCount = 0;
	gCollateTime = 0;

	if (!measurePerfOverhead)
		gPerfOn = true;

	gStartTime = SDL_GetPerformanceCounter();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Perf::EndPerf()
{
	int64_t anEndTime = SDL_GetPerformanceCounter();

	CollatePerfRecords();

	gPerfOn = false;

	int64_t aFreq = SDL_GetPerformanceFrequency();

	gDuration = ((double)(anEndTime - gStartTime - gCollateTime)) * 1000 / aFreq;

	for (PerfInfoSet::iterator anItr = gPerfInfoSet.begin(); anItr != gPerfInfoSet.end(); ++anItr)
	{
		const PerfInfo &anInfo = *anItr;
		anInfo.mMillisecondDuration = (double)anInfo.mDuration * 1000 / aFreq;
		anInfo.mLongestCall = anInfo.mLongestCall * 1000 / aFreq;
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Perf::StartTiming(const char *theName)
{
	if (gPerfOn)
	{
		++gStartCount;
		PerfRecord rec(theName, true);
		PushPerfRecord(rec);
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Perf::StopTiming(const char *theName)
{
	if (gPerfOn)
	{
		PerfRecord rec(theName, false);
		PushPerfRecord(rec);
		if (--gStartCount == 0)
			CollatePerfRecords();
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
std::string Perf::GetResults()
{
	std::string aResult;
	char aBuf[512];

	sprintf(aBuf, "Total Time: %.2f\n", gDuration);
	aResult += aBuf;
	for (PerfInfoSet::iterator anItr = gPerfInfoSet.begin(); anItr != gPerfInfoSet.end(); ++anItr)
	{
		const PerfInfo &anInfo = *anItr;
		sprintf(aBuf, "%s (%d calls, %%%.2f time): %.2f (%.2f avg, %.2f longest)\n", anInfo.mPerfName,
				anInfo.mCallCount, anInfo.mMillisecondDuration / gDuration * 100, anInfo.mMillisecondDuration,
				anInfo.mMillisecondDuration / anInfo.mCallCount, anInfo.mLongestCall);
		aResult += aBuf;
	}

	return aResult;
}
