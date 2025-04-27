#pragma once

#include "Font.h"
//#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>

namespace Sexy
{
	class SexyAppBase;

	class TTFFont : public Font //TODO: Implement
	{
	public:
		TTFFont(const std::string& theFace, int thePointSize, bool bold = false, bool italics = false, bool underline = false);
		TTFFont(SexyAppBase* theApp, const std::string& theFace, int thePointSize, int theScript = ANSI_CHARSET, bool bold = false, bool italics = false, bool underline = false);
		TTFFont(const TTFFont& theTTFFont);
		virtual ~TTFFont();

		virtual int				GetAscent();
		virtual int				GetAscentPadding();
		virtual int				GetDescent();
		virtual int				GetHeight();
		virtual int				GetLineSpacingOffset();
		virtual int				GetLineSpacing();
		virtual int				StringWidth(const SexyString& theString);
		virtual int				CharWidth(SexyChar theChar);
		virtual int				CharWidthKern(SexyChar theChar, SexyChar thePrevChar);

		virtual void			DrawString(Graphics* g, int theX, int theY, const SexyString& theString, const Color& theColor, const Rect& theClipRect);

		virtual Font* Duplicate();

	public:
		SexyAppBase* mApp;

		std::string mText;
		bool mDrawShadow;
		bool mSimulateBold;
		//TTF_Font* mFont;
		Color mColor;
		SDL_Texture* mTexture;
		//TTF_Text mTTFText;
		int mWidth;
		int mHeight;

		void Init(SexyAppBase* theApp, const std::string& theFace, int thePointSize, int theScript, bool bold, bool italics, bool underline, bool useDevCaps);
		void SetText(const std::string& textureText);

	private:


	};

}
