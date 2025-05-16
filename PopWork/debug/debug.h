#ifndef __DEBUG_H__
#define __DEBUG_H__
#ifdef _WIN32
#pragma once
#endif

#include "common.h"
#include <cassert>

extern bool gInAssert;

#ifdef POPWORK_TRACING_ENABLED
void PopWorkTrace(const char *theStr);
#define POPWORK_TRACE(theStr) PopWorkTrace(theStr)
#else
#define POPWORK_TRACE(theStr)
#endif

extern void PopWorkTraceFmt(const PopWorkChar *fmt...);
extern void OutputDebug(const PopWorkChar *fmt...);

#ifdef NDEBUG

#define DBG_ASSERTE(exp) ((void)0)
#define DBG_ASSERT(exp) ((void)0)

#else

#define DBG_ASSERTE(exp)                                                                                               \
	{                                                                                                                  \
		gInAssert = true;                                                                                              \
		assert(exp);                                                                                                   \
		gInAssert = false;                                                                                             \
	}
#define DBG_ASSERT(exp)                                                                                                \
	{                                                                                                                  \
		gInAssert = true;                                                                                              \
		assert(exp);                                                                                                   \
		gInAssert = false;                                                                                             \
	}

#endif // NDEBUG

#endif