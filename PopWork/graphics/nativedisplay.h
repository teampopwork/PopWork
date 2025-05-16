#ifndef __NATIVE_DISPLAY_H__
#define __NATIVE_DISPLAY_H__
#ifdef _WIN32
#pragma once
#endif

#include "common.h"

namespace PopWork
{

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class NativeDisplay
{
  public:
	int mRGBBits;
	ulong mRedMask;
	ulong mGreenMask;
	ulong mBlueMask;
	int mRedBits;
	int mGreenBits;
	int mBlueBits;
	int mRedShift;
	int mGreenShift;
	int mBlueShift;

  public:
	NativeDisplay();
	virtual ~NativeDisplay();
};

}; // namespace PopWork

#endif
