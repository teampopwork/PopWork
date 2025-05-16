#ifndef __QUANTIZE_H__
#define __QUANTIZE_H__
#ifdef _WIN32
#pragma once
#endif

#include "common.h"

namespace PopWork
{

bool Quantize8Bit(const ulong *theSrcBits, int theWidth, int theHeight, uchar *theDestColorIndices,
				  ulong *theDestColorTable);

}

#endif // __QUANTIZE_H__