#ifndef __POPWORKMATRIX_H__
#define __POPWORKMATRIX_H__
#ifdef _WIN32
#pragma once
#endif

#include "popvector.h"

namespace PopWork
{

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class PopWorkMatrix3
{
public:
	union
    {
        float m[3][3];
        struct
        {
            float m00, m01, m02;
            float m10, m11, m12;
            float m20, m21, m22;
        };
    };

public:
	PopWorkMatrix3();
	void ZeroMatrix();
	void LoadIdentity();

	PopWorkVector2 operator*(const PopWorkVector2 &theVec) const;
	PopWorkVector3 operator*(const PopWorkVector3 &theVec) const;
	PopWorkMatrix3 operator*(const PopWorkMatrix3 &theMat) const;
	const PopWorkMatrix3& operator*=(const PopWorkMatrix3 &theMat);
};


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class PopWorkTransform2D : public PopWorkMatrix3
{
	// only useful internally
protected:
	double determinantOfMinor(int theRowHeightY, int theColumnWidthX) const;


public:
	PopWorkTransform2D();
	PopWorkTransform2D(bool loadIdentity);
	PopWorkTransform2D(const PopWorkMatrix3& theMatrix);

	const PopWorkTransform2D& operator=(const PopWorkMatrix3 &theMat);

	double GetDeterminant() const;
	PopWorkTransform2D Inverse() const;

	void Translate(float tx, float ty);

	// Rotate has been replaced by RotateRad.  
	// NOTE:  If you had Rotate(angle) you should now use RotateRad(-angle).  
	// This is to make positive rotations go counter-clockwise when using screen coordinates.
	void RotateRad(float rot); 
	void RotateDeg(float rot);
	void Scale(float sx, float sy);
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Transform
{
protected:
	mutable PopWorkTransform2D mMatrix;
	mutable bool mNeedCalcMatrix;
	void MakeComplex();
	void CalcMatrix() const;

public:
	bool mComplex, mHaveRot, mHaveScale;
	float mTransX1, mTransY1, mTransX2, mTransY2;
	float mScaleX, mScaleY;
	float mRot;

public:
	Transform();

	void Reset();

	void Translate(float tx, float ty);
	void RotateRad(float rot); 
	void RotateDeg(float rot);
	void Scale(float sx, float sy);

	const PopWorkTransform2D& GetMatrix() const;
};


} // namespace PopWork

#endif