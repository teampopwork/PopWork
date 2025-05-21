#ifndef __MATH_HPP__
#define __MATH_HPP__
#ifdef _WIN32
#pragma once
#endif

#include "common.hpp"
#include <cmath>

// VC6 workaround
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace PopWork
{

class /*Pop*/Math
{
  public:
	inline static double Fabs(double x)
	{
		return std::fabs(x);
	}

	inline static float Fabs(float x)
	{
		return std::fabsf(x);
	}

	inline static float DegToRad(float degrees)
	{
		return degrees * static_cast<float>(M_PI / 180.0);
	}

	inline static float RadToDeg(float radians)
	{
		return radians * static_cast<float>(180.0 / M_PI);
	}

	inline static bool IsPowerOfTwo(uint32_t x)
	{
		return x != 0 && (x & (x - 1)) == 0;
	}
};

};

#endif