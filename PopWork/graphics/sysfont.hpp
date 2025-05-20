#ifndef __SYSFONT_HPP__
#define __SYSFONT_HPP__
#ifdef _WIN32
#pragma once
#endif

#include "font.hpp"
#include "common.hpp"

#include <SDL3_ttf/SDL_ttf.h>

namespace PopWork
{

class ImageFont;
class AppBase;

class SysFont : public Font
{
  public:
	TTF_Font *mTTFFont;
	AppBase *mApp;
	bool mDrawShadow;
	bool mSimulateBold;

	void Init(AppBase *theApp, const std::string &theFace, int thePointSize, int theScript, bool bold, bool italics,
			  bool underline, bool useDevCaps);

  public:
	SysFont(const std::string &theFace, int thePointSize, bool bold = false, bool italics = false,
			bool underline = false);
	SysFont(AppBase *theApp, const std::string &theFace, int thePointSize, int theScript = 0,
			bool bold = false, bool italics = false, bool underline = false);
	SysFont(AppBase *theApp, const unsigned char aData[], size_t aDataSize, int thePointSize,
			int theScript = 0, bool bold = false, bool italics = false, bool underline = false);
	SysFont(const SysFont &theSysFont);

	virtual ~SysFont();

	ImageFont *CreateImageFont();
	virtual int StringWidth(const PopString &theString);
	virtual void DrawString(Graphics *g, int theX, int theY, const PopString &theString, const Color &theColor,
							const Rect &theClipRect);

	virtual Font *Duplicate();
};

} // namespace PopWork

#endif // __SYSFONT_HPP__