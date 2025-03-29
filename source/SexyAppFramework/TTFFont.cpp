#include "TTFFont.h"
#include "SexyAppBase.h"
#include "SDLInterface.h"
#include "Graphics.h"

using namespace Sexy;

TTFFont::TTFFont(const std::string& theFace, int thePointSize, bool bold, bool italics, bool underline)
{

}

TTFFont::TTFFont(SexyAppBase* theApp, const std::string& theFace, int thePointSize, int theScript, bool bold, bool italics, bool underline)
{

}

TTFFont::TTFFont(const TTFFont& theTTFFont)
{
}

void TTFFont::Init(SexyAppBase* theApp, const std::string& theFace, int thePointSize, int theScript, bool bold, bool italics, bool underline, bool useDevCaps)
{
	mApp = theApp;

}

void TTFFont::SetText(const std::string& textureText)
{

}


TTFFont::~TTFFont()
{

}

void TTFFont::DrawString(Graphics* g, int theX, int theY, const SexyString& theString, const Color& theColor, const Rect& theClipRect)
{

}

Font* TTFFont::Duplicate()
{
	return new TTFFont(*this);
}
