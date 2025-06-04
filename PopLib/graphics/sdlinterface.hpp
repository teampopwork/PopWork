#ifndef __SDLINTERFACE_HPP__
#define __SDLINTERFACE_HPP__
#ifdef _WIN32
#pragma once
#endif

#include "common.hpp"
#include "memoryimage.hpp"
#include "misc/critsect.hpp"
#include "nativedisplay.hpp"
#include "math/rect.hpp"
#include "math/ratio.hpp"
#include "math/matrix.hpp"

#include <SDL3/SDL.h>

namespace PopLib
{

class AppBase;
class SDLImage;
class Matrix3;
class TriVertex;

typedef std::set<SDLImage *> SDLImageSet;
typedef std::set<MemoryImage *> ImageSet;
typedef std::list<Matrix3> TransformStack;

enum SDLImageFlags
{
	SDLImageFlag_NearestFiltering = 0x0001, // Uses nearest filtering for the texture
											// 0x0002
											// 0x0004
											// 0x0008
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
struct SDLTextureData
{
  public:
	SDL_Texture *mTexture;
	int mWidth;
	int mHeight;
	int mBitsChangedCount;
	SDL_Renderer *mRenderer;

	SDLTextureData(SDL_Renderer *theRenderer);
	~SDLTextureData();

	void ReleaseTextures();

	void CreateTextures(MemoryImage *theImage);
	void CheckCreateTextures(MemoryImage *theImage);

	int GetMemSize();
};

class SDLInterface : public NativeDisplay
{
  public:
	enum
	{
		RESULT_OK = 0,
		RESULT_FAIL = 1,
		RESULT_DD_CREATE_FAIL = 2,
		RESULT_SURFACE_FAIL = 3,
		RESULT_EXCLUSIVE_FAIL = 4,
		RESULT_DISPCHANGE_FAIL = 5,
		RESULT_INVALID_COLORDEPTH = 6,
		RESULT_3D_FAIL = 7
	};

	AppBase *mApp;
	CritSect mCritSect;
	int mWidth;
	int mHeight;
	int mDisplayWidth;
	int mDisplayHeight;
	int mVideoOnlyDraw;

	bool mIs3D;
	bool mHasInitiated;

	Rect mPresentationRect;
	int mRefreshRate;
	int mMillisecondsPerFrame;

	Image *mCursorImage;
	SDLImage *mScreenImage;

	int mNextCursorX;
	int mNextCursorY;
	int mCursorX;
	int mCursorY;

	ImageSet mImageSet;
	SDLImageSet mSDLImageSet;
	TransformStack mTransformStack;

  public:
	SDL_Renderer *mRenderer;
	SDL_Window *mWindow;
	SDL_Texture *mScreenTexture;

  public:
	void AddSDLImage(SDLImage *theSDLImage);
	void RemoveSDLImage(SDLImage *theSDLImage);
	void Remove3DData(MemoryImage *theImage); // for 3d texture cleanup

  public:
	SDLInterface(AppBase *theApp);
	virtual ~SDLInterface();
	void Cleanup();

	SDLImage *GetScreenImage();
	void UpdateViewport();
	int Init(bool IsWindowed);

	bool InitSDLWindow(bool IsWindowed);
	bool InitSDLRenderer();

	bool Redraw(Rect *theClipRect);
	void SetVideoOnlyDraw(bool videoOnly);

	void SetCursorPos(int theCursorX, int theCursorY);

	bool SetCursorImage(Image *theImage);
	bool UpdateWindowIcon(Image *theImage);

	void SetCursor(SDL_SystemCursor theCursorType);

	void MakeSimpleMessageBox(const char *theTitle, const char *theMessage, SDL_MessageBoxFlags flags);
	int MakeResultMessageBox(SDL_MessageBoxData data);

  public:
	void PushTransform(const Matrix3 &theTransform, bool concatenate = true);
	void PopTransform();

	bool PreDraw();

	bool CreateImageTexture(MemoryImage *theImage);
	bool RecoverBits(MemoryImage *theImage);

	SDL_BlendMode ChooseBlendMode(int theBlendMode);

	// Draw Funcs
	void Blt(Image *theImage, int theX, int theY, const Rect &theSrcRect, const Color &theColor, int theDrawMode,
			 bool linearFilter = false);
	void BltClipF(Image *theImage, float theX, float theY, const Rect &theSrcRect, const Rect *theClipRect,
				  const Color &theColor, int theDrawMode);
	void BltMirror(Image *theImage, float theX, float theY, const Rect &theSrcRect, const Color &theColor,
				   int theDrawMode, bool linearFilter = false);
	void StretchBlt(Image *theImage, const Rect &theDestRect, const Rect &theSrcRect, const Rect *theClipRect,
					const Color &theColor, int theDrawMode, bool fastStretch, bool mirror = false);
	void BltRotated(Image *theImage, float theX, float theY, const Rect *theClipRect, const Color &theColor,
					int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY, const Rect &theSrcRect);
	void BltTransformed(Image *theImage, const Rect *theClipRect, const Color &theColor, int theDrawMode,
						const Rect &theSrcRect, const Matrix3 &theTransform, bool linearFilter, float theX = 0,
						float theY = 0, bool center = false);
	void DrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color &theColor,
				  int theDrawMode);
	void FillRect(const Rect &theRect, const Color &theColor, int theDrawMode);
	void DrawTriangle(const TriVertex &p1, const TriVertex &p2, const TriVertex &p3, const Color &theColor,
					  int theDrawMode);
	void DrawTriangleTex(const TriVertex &p1, const TriVertex &p2, const TriVertex &p3, const Color &theColor,
						 int theDrawMode, Image *theTexture, bool blend = true);
	void DrawTrianglesTex(const TriVertex theVertices[][3], int theNumTriangles, const Color &theColor, int theDrawMode,
						  Image *theTexture, float tx = 0, float ty = 0, bool blend = true);
	void DrawTrianglesTexStrip(const TriVertex theVertices[], int theNumTriangles, const Color &theColor,
							   int theDrawMode, Image *theTexture, float tx = 0, float ty = 0, bool blend = true);
	void FillPoly(const Point theVertices[], int theNumVertices, const Rect *theClipRect, const Color &theColor,
				  int theDrawMode, int tx, int ty);

	void BltTexture(SDL_Texture *theTexture, const SDL_FRect &theSrcRect, const SDL_FRect &theDestRect,
					const Color &theColor, int theDrawMode);
};
} // namespace PopLib

#endif // __SDLINTERFACE_HPP__