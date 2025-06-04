#ifndef __NATIVE_DISPLAY_HPP__
#define __NATIVE_DISPLAY_HPP__
#ifdef _WIN32
#pragma once
#endif

#include "common.hpp"

namespace PopLib
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

}; // namespace PopLib

#endif
