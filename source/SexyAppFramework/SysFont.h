#pragma once

#include "Font.h"
#include <SDL3_ttf/SDL_ttf.h>

namespace Sexy
{

class ImageFont;
class SexyAppBase;

class SysFont : public Font
{
public:	
	TTF_Font*				mTTFFont;
	SexyAppBase*			mApp;
	bool					mDrawShadow;
	bool					mSimulateBold;
	
	void Init(SexyAppBase* theApp, const std::string& theFace, int thePointSize, int theScript, bool bold, bool italics, bool underline, bool useDevCaps);

public:
	SysFont(const std::string& theFace, int thePointSize, bool bold = false, bool italics = false, bool underline = false);
	SysFont(SexyAppBase* theApp, const std::string& theFace, int thePointSize, int theScript = ANSI_CHARSET, bool bold = false, bool italics = false, bool underline = false);
	SysFont(SexyAppBase* theApp, const unsigned char aData[], size_t aDataSize, int thePointSize, int theScript = ANSI_CHARSET, bool bold = false, bool italics = false, bool underline = false);
	SysFont(const SysFont& theSysFont);

	virtual ~SysFont();

	ImageFont*				CreateImageFont();
	virtual int				StringWidth(const SexyString& theString);
	virtual void			DrawString(Graphics* g, int theX, int theY, const SexyString& theString, const Color& theColor, const Rect& theClipRect);

	virtual Font*			Duplicate();
};

}
