#ifndef __IMAGELIB_H__
#define __IMAGELIB_H__

#include <string>

namespace ImageLib
{

class Image
{
public:
	int						mWidth;
	int						mHeight;
	unsigned long*			mBits;
	int						mNumChannels;

public:
	Image();
	virtual ~Image();

	int						GetWidth();
	int						GetHeight();
	unsigned long*			GetBits();
};

bool WriteImage(const std::string& theFileName, const std::string& theExtension, Image* theImage);
bool WriteImageRaw(const std::string& theFileName, const std::string& theExtension, unsigned char* theData, int theWidth, int theHeight);
extern int gAlphaComposeColor;
extern bool gAutoLoadAlpha;

Image* GetImage(const std::string& theFileName, bool lookForAlphaImage = true);

}

#endif //__IMAGELIB_H__