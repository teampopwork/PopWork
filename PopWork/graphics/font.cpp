#include "font.h"
#include "image.h"

using namespace PopWork;

Font::Font()
{
	mAscent = 0;
	mHeight = 0;
	mAscentPadding = 0;
	mLineSpacingOffset = 0;
}

Font::Font(const Font &theFont)
	: mAscent(theFont.mAscent), mHeight(theFont.mHeight), mAscentPadding(theFont.mAscentPadding),
	  mLineSpacingOffset(theFont.mLineSpacingOffset)
{
}

Font::~Font()
{
}

int Font::GetAscent()
{
	return mAscent;
}

int Font::GetAscentPadding()
{
	return mAscentPadding;
}

int Font::GetDescent()
{
	return mHeight - mAscent;
}

int Font::GetHeight()
{
	return mHeight;
}

int Font::GetLineSpacingOffset()
{
	return mLineSpacingOffset;
}

int Font::GetLineSpacing()
{
	return mHeight + mLineSpacingOffset;
}

int Font::StringWidth(const PopWorkString &theString)
{
	return 0;
}

int Font::CharWidth(PopWorkChar theChar)
{
	PopWorkString aString(1, theChar);
	return StringWidth(aString);
}

int Font::CharWidthKern(PopWorkChar theChar, PopWorkChar thePrevChar)
{
	return CharWidth(theChar);
}

void Font::DrawString(Graphics *g, int theX, int theY, const PopWorkString &theString, const Color &theColor,
					  const Rect &theClipRect)
{
}
