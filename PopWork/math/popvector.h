#ifndef __POPWORKVECTOR_H__
#define __POPWORKVECTOR_H__
#ifdef _WIN32
#pragma once
#endif

#include <math.h>

namespace PopWork
{

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class PopWorkVector2
{
  public:
	float x, y;

  public:
	PopWorkVector2() : x(0), y(0)
	{
	}
	PopWorkVector2(float theX, float theY) : x(theX), y(theY)
	{
	}

	float Dot(const PopWorkVector2 &v) const
	{
		return x * v.x + y * v.y;
	}
	PopWorkVector2 operator+(const PopWorkVector2 &v) const
	{
		return PopWorkVector2(x + v.x, y + v.y);
	}
	PopWorkVector2 operator-(const PopWorkVector2 &v) const
	{
		return PopWorkVector2(x - v.x, y - v.y);
	}
	PopWorkVector2 operator-() const
	{
		return PopWorkVector2(-x, -y);
	}
	PopWorkVector2 operator*(float t) const
	{
		return PopWorkVector2(t * x, t * y);
	}
	PopWorkVector2 operator/(float t) const
	{
		return PopWorkVector2(x / t, y / t);
	}
	void operator+=(const PopWorkVector2 &v)
	{
		x += v.x;
		y += v.y;
	}
	void operator-=(const PopWorkVector2 &v)
	{
		x -= v.x;
		y -= v.y;
	}
	void operator*=(float t)
	{
		x *= t;
		y *= t;
	}
	void operator/=(float t)
	{
		x /= t;
		y /= t;
	}

	bool operator==(const PopWorkVector2 &v)
	{
		return x == v.x && y == v.y;
	}
	bool operator!=(const PopWorkVector2 &v)
	{
		return x != v.x || y != v.y;
	}

	float Magnitude() const
	{
		return sqrtf(x * x + y * y);
	}
	float MagnitudeSquared() const
	{
		return x * x + y * y;
	}

	PopWorkVector2 Normalize() const
	{
		float aMag = Magnitude();
		return aMag != 0 ? (*this) / aMag : *this;
	}

	PopWorkVector2 Perp() const
	{
		return PopWorkVector2(-y, x);
	}
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class PopWorkVector3
{
  public:
	float x, y, z;

  public:
	PopWorkVector3() : x(0), y(0), z(0)
	{
	}
	PopWorkVector3(float theX, float theY, float theZ) : x(theX), y(theY), z(theZ)
	{
	}

	float Dot(const PopWorkVector3 &v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}
	PopWorkVector3 Cross(const PopWorkVector3 &v) const
	{
		return PopWorkVector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
	PopWorkVector3 operator+(const PopWorkVector3 &v) const
	{
		return PopWorkVector3(x + v.x, y + v.y, z + v.z);
	}
	PopWorkVector3 operator-(const PopWorkVector3 &v) const
	{
		return PopWorkVector3(x - v.x, y - v.y, z - v.z);
	}
	PopWorkVector3 operator*(float t) const
	{
		return PopWorkVector3(t * x, t * y, t * z);
	}
	PopWorkVector3 operator/(float t) const
	{
		return PopWorkVector3(x / t, y / t, z / t);
	}
	float Magnitude() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	PopWorkVector3 Normalize() const
	{
		float aMag = Magnitude();
		return aMag != 0 ? (*this) / aMag : *this;
	}
};

}; // namespace PopWork

#endif