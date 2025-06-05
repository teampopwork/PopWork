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

namespace PopLib
{

class Math
{
  public:
	template<typename T>
	inline static T min(T a, T b) {
		return (a < b) ? a : b;
	}

	template<typename T>
	inline static T max(T a, T b) {
		return (a > b) ? a : b;
	}

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

	template<typename T>
	inline static T Clamp(T value, T minVal, T maxVal) {
		return max(minVal, min(value, maxVal));
	}

	inline static float Lerp(float a, float b, float t)
	{
		return a + t * (b - a);
	}

	inline static float SmoothStep(float edge0, float edge1, float x)
	{
		x = Clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
		return x * x * (3 - 2 * x);
	}

	inline static bool NearlyEqual(float a, float b, float epsilon = 1e-5f)
	{
		return std::fabs(a - b) <= epsilon;
	}

	inline static float Sin(float angleRadians) { return std::sinf(angleRadians); }
	inline static float Cos(float angleRadians) { return std::cosf(angleRadians); }
	inline static float Tan(float angleRadians) { return std::tanf(angleRadians); }
	inline static float Asin(float x) { return std::asinf(x); }
	inline static float Acos(float x) { return std::acosf(x); }
	inline static float Atan2(float y, float x) { return std::atan2f(y, x); }

	template <typename T> int Sign(T val) {
    return (T(0) < val) - (val < T(0));
	}
};

};

#endif