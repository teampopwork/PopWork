#include "SDLInterface.h"
#include "SDLImage.h"
#include "../SexyAppBase.h"
#include "../Misc/AutoCrit.h"
#include "Graphics.h"
#include "MemoryImage.h"
#include <SDL3_ttf/SDL_ttf.h>

using namespace Sexy;

SDL_FPoint TransformToPoint(float x, float y, const SexyMatrix3& m, float aTransX = 0, float aTransY = 0) {
	SDL_FPoint result;
	result.x = m.m00 * x + m.m01 * y + m.m02 + aTransX;
	result.y = m.m10 * x + m.m11 * y + m.m12 + aTransY;
	return result;
}

SDLInterface::SDLInterface(SexyAppBase* theApp)
{
    mApp = theApp;
    mWidth = mApp->mWidth;
    mHeight = mApp->mHeight;
    mDisplayWidth = mWidth;
    mDisplayHeight = mHeight;
    mPresentationRect = Rect(0, 0, mWidth, mHeight);
    mScreenImage = NULL;
    mHasInitiated = false;
    mCursorX = 0;
    mCursorY = 0;
    mIs3D = false;
	mVideoOnlyDraw = true;
    mMillisecondsPerFrame = 0;
    mNextCursorX = 0;
    mNextCursorY = 0;
    mRefreshRate = 0;
    mRenderer = nullptr;
    mScreenTexture = nullptr;
    mWindow = nullptr;
}


SDLInterface::~SDLInterface()
{
	Cleanup();
	SDL_Quit();
}

void SDLInterface::Cleanup()
{
	ImageSet::iterator anItr;
	for (anItr = mImageSet.begin(); anItr != mImageSet.end(); ++anItr)
	{
		MemoryImage* anImage = *anItr;
		SDLTextureData*aData = (SDLTextureData*)anImage->mD3DData;
		delete aData;
		anImage->mD3DData = NULL;
	}
	mImageSet.clear();

	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	mHasInitiated = false;
}

void SDLInterface::AddSDLImage(SDLImage* theSDLImage)
{
	AutoCrit anAutoCrit(mCritSect);

	mSDLImageSet.insert(theSDLImage);
}

void SDLInterface::RemoveSDLImage(SDLImage* theSDLImage)
{
	AutoCrit anAutoCrit(mCritSect);

	SDLImageSet::iterator anItr = mSDLImageSet.find(theSDLImage);
	if (anItr != mSDLImageSet.end())
		mSDLImageSet.erase(anItr);
}

void SDLInterface::Remove3DData(MemoryImage* theImage)
{
	if (theImage->mD3DData != NULL)
	{
		delete (SDLTextureData*)theImage->mD3DData;
		theImage->mD3DData = NULL;

		AutoCrit aCrit(mCritSect); // Make images thread safe
		mImageSet.erase(theImage);
	}
}

SDLImage* SDLInterface::GetScreenImage()
{
	return mScreenImage;
}

void SDLInterface::UpdateViewport(){

	int windowWidth, windowHeight;
	SDL_GetWindowSize(mWindow, &windowWidth, &windowHeight);
	SDL_SetRenderLogicalPresentation(mRenderer, windowWidth, windowHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);
	mPresentationRect = Rect(0, 0, windowWidth, windowHeight);
}

int SDLInterface::Init(bool IsWindowed)
{
	int aResult = RESULT_OK;

	if (mHasInitiated)
		Cleanup();

	mRGBBits = 32;

	mRedBits = 8;
	mGreenBits = 8;
	mBlueBits = 8;

	mRedShift = 0;
	mGreenShift = 8;
	mBlueShift = 16;

	mRedMask = (0xFFU << mRedShift);
	mGreenMask = (0xFFU << mGreenShift);
	mBlueMask = (0xFFU << mBlueShift);

	aResult = InitSDLWindow(IsWindowed) ? aResult : RESULT_FAIL;
	mHasInitiated = true;
	return aResult;
}

bool SDLInterface::InitSDLWindow(bool IsWindowed)
{
	int aWindowFlags = IsWindowed ? 0 : SDL_WINDOW_FULLSCREEN;

	mWindow = SDL_CreateWindow(SexyStringToStringFast(mApp->mTitle).c_str(), mWidth, mHeight, aWindowFlags);
	if (mWindow == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Window Creation Failed", SDL_GetError(), nullptr);
		return false;
	}

	SDL_SetWindowFullscreen(mWindow, !IsWindowed);

	SDL_StartTextInput(mWindow);

	return InitSDLRenderer();
}

bool SDLInterface::InitSDLRenderer()
{

	mRenderer = SDL_CreateRenderer(mWindow, mIs3D ? NULL : "software");
	if (mRenderer == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Renderer Creation Failed", SDL_GetError(), nullptr);
		return false;
	}

	mScreenTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, mWidth, mHeight);
	if (mScreenTexture == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Screen Texture-Buffer Creation Failed", SDL_GetError(), nullptr);
		return false;
	}

	const SDL_DisplayMode* aMode = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(mWindow));
	mRefreshRate = aMode->refresh_rate;
	if (!mRefreshRate) mRefreshRate = 60;
	mMillisecondsPerFrame = 1000 / mRefreshRate;

	SetVideoOnlyDraw(mVideoOnlyDraw);

	UpdateViewport();

	return true;
}
bool gSDLInterfacePreDrawError = false;
bool SDLInterface::Redraw(Rect* theClipRect)
{
	SDL_Rect clipRect;
	if (theClipRect != NULL)
		clipRect = { theClipRect->mX, theClipRect->mY, theClipRect->mWidth, theClipRect->mHeight };
	else
		clipRect = { mPresentationRect.mX, mPresentationRect.mY, mPresentationRect.mWidth, mPresentationRect.mHeight };

	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255); // Set clear color
	SDL_RenderClear(mRenderer); // Clear screen

	SDL_SetRenderClipRect(mRenderer, &clipRect); // Set clip rect (affects only render ops)
	gSDLInterfacePreDrawError = !SDL_RenderTexture(mRenderer, mScreenTexture, NULL, NULL); // Render texture
	SDL_SetRenderClipRect(mRenderer, NULL); // Reset clip rect

	SDL_RenderPresent(mRenderer); // Present the frame


	return true;
}

/// <summary>
/// Setup the mScreenImage
/// </summary>
/// <param name="videoOnly"></param>
void SDLInterface::SetVideoOnlyDraw(bool videoOnly)
{
	AutoCrit anAutoCrit(mCritSect);

	mVideoOnlyDraw = videoOnly;

	if (mScreenImage) delete mScreenImage;
	mScreenImage = new SDLImage(this);	
	mScreenImage->mWidth = mWidth;
	mScreenImage->mHeight = mHeight;
	mScreenImage->SetImageMode(false, false);
}

/// <summary>
/// Set the next cursor position
/// </summary>
/// <param name="theCursorX"></param>
/// <param name="theCursorY"></param>
void SDLInterface::SetCursorPos(int theCursorX, int theCursorY)
{
	mNextCursorX = theCursorX;
	mNextCursorY = theCursorY;
}

/// <summary>
/// Set the cursor image to a Image* or NULL to hide the cursor
/// </summary>
/// <param name="theImage"></param>
/// <returns></returns>
bool SDLInterface::SetCursorImage(Image* theImage)
{
	AutoCrit anAutoCrit(mCritSect);

	if (mCursorImage != theImage)
	{
		mCursorImage = theImage;
		if (theImage == NULL)
			return true;
		SDL_Surface* aSurface = SDL_CreateSurfaceFrom(theImage->mWidth, theImage->mHeight, SDL_PIXELFORMAT_ARGB8888, ((MemoryImage*)mCursorImage)->GetBits(), theImage->mWidth * sizeof(ulong));

		SDL_Cursor* aCursor = SDL_CreateColorCursor(aSurface, mCursorImage->mWidth / 2, mCursorImage->mHeight / 2);

		SDL_SetCursor(aCursor);

		SDL_DestroySurface(aSurface);

		return true;
	}

	return false;
}

void SDLInterface::SetCursor(SDL_SystemCursor theCursorType)
{
	SDL_Cursor* aCursor = SDL_CreateSystemCursor(theCursorType);
	SDL_SetCursor(aCursor);
	SDL_DestroyCursor(aCursor);
}

void SDLInterface::MakeSimpleMessageBox(const char* theTitle, const char* theMessage, SDL_MessageBoxFlags flags)
{
	SDL_ShowSimpleMessageBox(flags, theTitle, theMessage, mWindow);
}

int SDLInterface::MakeResultMessageBox(SDL_MessageBoxData data)
{

	int buttonid;
	SDL_ShowMessageBox(&data, &buttonid);

	return buttonid;
}

void SDLInterface::PushTransform(const SexyMatrix3& theTransform, bool concatenate)
{
	if (mTransformStack.empty() || !concatenate)
		mTransformStack.push_back(theTransform);
	else
	{
		SexyMatrix3& aTrans = mTransformStack.back();
		mTransformStack.push_back(theTransform * aTrans);
	}
}

void SDLInterface::PopTransform()
{
	if (!mTransformStack.empty())
		mTransformStack.pop_back();
}

bool SDLInterface::PreDraw()
{
	return true;
}

bool SDLInterface::CreateImageTexture(MemoryImage* theImage)
{
	bool wantPurge = false;

	if (theImage->mD3DData == NULL)
	{
		theImage->mD3DData = new SDLTextureData(mRenderer);

		// The actual purging was deferred
		wantPurge = theImage->mPurgeBits;

		AutoCrit aCrit(mCritSect); // Make images thread safe
		mImageSet.insert(theImage);
	}

	SDLTextureData* aData = (SDLTextureData*)theImage->mD3DData;
	aData->CheckCreateTextures(theImage);

	if (wantPurge)
		theImage->PurgeBits();

	return true;
}

bool SDLInterface::RecoverBits(MemoryImage* theImage)
{
	if (theImage->mD3DData == NULL)
		return false;

	SDLTextureData* aData = (SDLTextureData*)theImage->mD3DData;
	if (aData->mBitsChangedCount != theImage->mBitsChangedCount) // bits have changed since texture was created
		return false;

	// Reverse the process: copy texture data to theImage
	float aWidth;
	float aHeight;
	void* pixels;
	int pitch;

	if (SDL_LockTexture(aData->mTexture, NULL, &pixels, &pitch) && SDL_GetTextureSize(aData->mTexture, &aWidth, &aHeight))
	{
		theImage->SetBits((ulong*)pixels, (int)aWidth, (int)aHeight);
		SDL_UnlockTexture(aData->mTexture);
	}

	return true;
}


SDL_BlendMode SDLInterface::ChooseBlendMode(int theBlendMode)
{
	SDL_BlendMode theSDLBlendMode;
	switch (theBlendMode)
	{
	case Graphics::DRAWMODE_ADDITIVE:
		theSDLBlendMode = SDL_BLENDMODE_ADD;
		break;
	default:
	case Graphics::DRAWMODE_NORMAL:
		theSDLBlendMode = SDL_BLENDMODE_BLEND;
		break;
	}
	return theSDLBlendMode;
}


SDLTextureData::SDLTextureData(SDL_Renderer* theRenderer)
{
	mWidth = 0;
	mHeight = 0;
	mBitsChangedCount = 0;
	mRenderer = theRenderer;
	mTexture = nullptr;
}

SDLTextureData::~SDLTextureData()
{
	ReleaseTextures();
}

void SDLTextureData::ReleaseTextures()
{
	if (mTexture != nullptr)
		SDL_DestroyTexture(mTexture);
}

void SDLTextureData::CreateTextures(MemoryImage* theImage)
{
	theImage->DeleteSWBuffers(); // we don't need the software buffers anymore

	theImage->CommitBits();
	bool createTexture = false;
	if (mWidth != theImage->mWidth || mHeight != theImage->mHeight)
	{
		ReleaseTextures();
		createTexture = true;
	}

	int aHeight = theImage->GetHeight();
	int aWidth = theImage->GetWidth();

	if (createTexture)
	{

		mTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, aWidth, aHeight);

		SDL_SetTextureScaleMode(mTexture, (SDL_GetRendererName(mRenderer) == "software" || theImage->mImageFlags & SDLImageFlag_NearestFiltering) ? SDL_SCALEMODE_NEAREST : SDL_SCALEMODE_LINEAR);
		if (mTexture)
		{
			SDL_UpdateTexture(mTexture, nullptr, theImage->GetBits(), aWidth * sizeof(ulong));
		}
	}

	mWidth = theImage->mWidth;
	mHeight = theImage->mHeight;
	mBitsChangedCount = theImage->mBitsChangedCount;
}

void SDLTextureData::CheckCreateTextures(MemoryImage* theImage)
{
	if (mTexture != nullptr)
	{
		if (mWidth != theImage->mWidth || mHeight != theImage->mHeight || mBitsChangedCount != theImage->mBitsChangedCount)
			CreateTextures(theImage);
		return;
	}
	CreateTextures(theImage);
}

int SDLTextureData::GetMemSize()
{
	int aSize = 0;

	aSize = (SDL_BYTESPERPIXEL(SDL_PIXELFORMAT_ARGB8888) / 8) * mWidth * mHeight;

	return aSize;
}

/////////////////////////////////////////////////////////////////
///				DRAWING/BLITTING FUNCTIONS		    	   //////
/////////////////////////////////////////////////////////////////

void SDLInterface::Blt(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode, bool linearFilter)
{
	MemoryImage* aSrcMemoryImage = (MemoryImage*)theImage;

	if (!CreateImageTexture(aSrcMemoryImage))
		return;

	SDLTextureData* aData = (SDLTextureData*)aSrcMemoryImage->mD3DData;

	SDL_SetRenderTarget(mRenderer, mScreenTexture);

	SDL_Texture* aTexture = aData->mTexture;
	SDL_SetTextureColorMod(aTexture, theColor.GetRed(), theColor.GetGreen(), theColor.GetBlue());
	SDL_SetTextureAlphaMod(aTexture, theColor.GetAlpha());

	SDL_FRect destRect = { theX, theY, theSrcRect.mWidth, theSrcRect.mHeight };
	SDL_FRect srcRect = { theSrcRect.mX, theSrcRect.mY, theSrcRect.mWidth, theSrcRect.mHeight };

	SDL_SetTextureBlendMode(aTexture, ChooseBlendMode(theDrawMode));
	SDL_RenderTexture(mRenderer, aTexture, &srcRect, &destRect);
	SDL_SetRenderTarget(mRenderer, nullptr);
}


void SDLInterface::BltClipF(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect* theClipRect, const Color& theColor, int theDrawMode)
{
	MemoryImage* aSrcMemoryImage = (MemoryImage*)theImage;

	if (!CreateImageTexture(aSrcMemoryImage))
		return;

	SDLTextureData* aData = (SDLTextureData*)aSrcMemoryImage->mD3DData;

	SDL_SetRenderTarget(mRenderer, mScreenTexture);

	SDL_Texture* aTexture = aData->mTexture;
	SDL_SetTextureColorMod(aTexture, theColor.GetRed(), theColor.GetGreen(), theColor.GetBlue());
	SDL_SetTextureAlphaMod(aTexture, theColor.GetAlpha());

	SDL_FRect destRect = { theX, theY, theSrcRect.mWidth, theSrcRect.mHeight };
	SDL_Rect clipRect;
	if (theClipRect == nullptr)
		clipRect = { 0,0,theImage->mWidth, theImage->mHeight };
	else
		clipRect = { theClipRect->mX, theClipRect->mY, theClipRect->mWidth, theClipRect->mHeight };
	SDL_FRect srcRect = { theSrcRect.mX, theSrcRect.mY, theSrcRect.mWidth, theSrcRect.mHeight };

	SDL_SetRenderClipRect(mRenderer, &clipRect);
	SDL_SetTextureBlendMode(aTexture, ChooseBlendMode(theDrawMode));
	SDL_RenderTexture(mRenderer, aTexture, &srcRect, &destRect);
	SDL_SetRenderClipRect(mRenderer, NULL);
	SDL_SetRenderTarget(mRenderer, nullptr);
}

void SDLInterface::BltMirror(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode, bool linearFilter)
{
	MemoryImage* aSrcMemoryImage = (MemoryImage*)theImage;

	if (!CreateImageTexture(aSrcMemoryImage))
		return;

	SDLTextureData* aData = (SDLTextureData*)aSrcMemoryImage->mD3DData;

	SDL_SetRenderTarget(mRenderer, mScreenTexture);

	SDL_Texture* aTexture = aData->mTexture;
	SDL_SetTextureColorMod(aTexture, theColor.GetRed(), theColor.GetGreen(), theColor.GetBlue());
	SDL_SetTextureAlphaMod(aTexture, theColor.GetAlpha());

	SDL_FRect destRect = { theX, theY, theSrcRect.mWidth,theSrcRect.mHeight };
	SDL_FRect srcRect = { theSrcRect.mX, theSrcRect.mY, theSrcRect.mWidth, theSrcRect.mHeight };

	SDL_SetTextureBlendMode(aTexture, ChooseBlendMode(theDrawMode));
	SDL_RenderTextureRotated(mRenderer, aTexture, &srcRect, &destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
	SDL_SetRenderTarget(mRenderer, nullptr);
}

void SDLInterface::StretchBlt(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect* theClipRect, const Color& theColor, int theDrawMode, bool fastStretch, bool mirror)
{
	float xScale = (float)theDestRect.mWidth / theSrcRect.mWidth;
	float yScale = (float)theDestRect.mHeight / theSrcRect.mHeight;

	MemoryImage* aSrcMemoryImage = (MemoryImage*)theImage;

	if (!CreateImageTexture(aSrcMemoryImage))
		return;

	SDLTextureData* aData = (SDLTextureData*)aSrcMemoryImage->mD3DData;

	SDL_SetRenderTarget(mRenderer, mScreenTexture);

	SDL_Texture* aTexture = aData->mTexture;
	SDL_SetTextureColorMod(aTexture, theColor.GetRed(), theColor.GetGreen(), theColor.GetBlue());
	SDL_SetTextureAlphaMod(aTexture, theColor.GetAlpha());

	SDL_FRect destRect = { theDestRect.mX, theDestRect.mY, theDestRect.mWidth * xScale, theDestRect.mHeight * yScale};
	SDL_Rect clipRect;
	if (theClipRect == nullptr)
		clipRect = { 0,0,theImage->mWidth, theImage->mHeight };
	else
		clipRect = { theClipRect->mX, theClipRect->mY, theClipRect->mWidth, theClipRect->mHeight };
	SDL_FRect srcRect = { theSrcRect.mX, theSrcRect.mY, theSrcRect.mWidth, theSrcRect.mHeight};

	SDL_SetRenderClipRect(mRenderer, &clipRect);
	SDL_SetTextureBlendMode(aTexture, ChooseBlendMode(theDrawMode));
	SDL_RenderTextureRotated(mRenderer, aTexture, &srcRect, &destRect, 0, NULL, mirror ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	SDL_SetRenderTarget(mRenderer, nullptr);
	SDL_SetRenderClipRect(mRenderer, NULL);
}


void SDLInterface::BltRotated(Image* theImage, float theX, float theY, const Rect* theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY, const Rect& theSrcRect)
{
	MemoryImage* aSrcMemoryImage = (MemoryImage*)theImage;

	if (!CreateImageTexture(aSrcMemoryImage))
		return;

	SDLTextureData* aData = (SDLTextureData*)aSrcMemoryImage->mD3DData;

	SDL_SetRenderTarget(mRenderer, mScreenTexture);

	SDL_Texture* aTexture = aData->mTexture;
	SDL_SetTextureColorMod(aTexture, theColor.GetRed(), theColor.GetGreen(), theColor.GetBlue());
	SDL_SetTextureAlphaMod(aTexture, theColor.GetAlpha());

	SDL_FRect destRect = { theX, theY, theSrcRect.mWidth, theSrcRect.mHeight };
	SDL_FRect srcRect = { theSrcRect.mX, theSrcRect.mY, theSrcRect.mWidth, theSrcRect.mHeight };
	SDL_Rect clipRect;
	if (theClipRect == nullptr)
		clipRect = { 0,0,theImage->mWidth, theImage->mHeight };
	else
		clipRect = { theClipRect->mX, theClipRect->mY, theClipRect->mWidth, theClipRect->mHeight };
	SDL_FPoint rotationCenter = { theRotCenterX, theRotCenterY };

	SDL_SetRenderClipRect(mRenderer, &clipRect);
	SDL_SetTextureBlendMode(aTexture, ChooseBlendMode(theDrawMode));
	SDL_RenderTextureRotated(mRenderer, aTexture, &srcRect, &destRect, theRot, &rotationCenter, SDL_FLIP_NONE);
	SDL_SetRenderTarget(mRenderer, nullptr);
	SDL_SetRenderClipRect(mRenderer, NULL);
}

void SDLInterface::BltTransformed(Image* theImage, const Rect* theClipRect, const Color& theColor, int theDrawMode, const Rect& theSrcRect, const SexyMatrix3& theTransform, bool linearFilter, float theX, float theY, bool center)
{
	MemoryImage* aSrcMemoryImage = (MemoryImage*)theImage;

	if (!CreateImageTexture(aSrcMemoryImage))
		return;

	SDLTextureData* aData = (SDLTextureData*)aSrcMemoryImage->mD3DData;

	SDL_SetRenderTarget(mRenderer, mScreenTexture);

	SDL_Texture* aTexture = aData->mTexture;
	SDL_SetTextureColorMod(aTexture, theColor.GetRed(), theColor.GetGreen(), theColor.GetBlue());
	SDL_SetTextureAlphaMod(aTexture, theColor.GetAlpha());

	SDL_Rect clipRect;
	if (theClipRect == nullptr)
		clipRect = { 0,0,theImage->mWidth, theImage->mHeight };
	else
		clipRect = { theClipRect->mX, theClipRect->mY, theClipRect->mWidth, theClipRect->mHeight };

	SDL_SetTextureBlendMode(aTexture, ChooseBlendMode(theDrawMode));

	//HERE COMES THE MAGIC!!

	float halfWidth = theSrcRect.mWidth * 0.5f;
	float halfHeight = theSrcRect.mHeight * 0.5f;

	float x1 = center ? -halfWidth : 0;
	float y1 = center ? -halfHeight : 0;
	float x2 = x1 + theSrcRect.mWidth;
	float y2 = y1;
	float x3 = x1;
	float y3 = y1 + theSrcRect.mHeight;
	float x4 = x2;
	float y4 = y3;

	SDL_FColor aColor = { theColor.GetRed() , theColor.GetGreen(), theColor.GetBlue(), theColor.GetAlpha() };

	SDL_Vertex vertices[4] = {
		{ TransformToPoint(x1, y1, theTransform, theX, theY), aColor, {0, 0} },     // Top-left
		{ TransformToPoint(x2, y2, theTransform, theX, theY), aColor, {1, 0} },     // Top-right
		{ TransformToPoint(x3, y3, theTransform, theX, theY), aColor, {0, 1} },     // Bottom-left
		{ TransformToPoint(x4, y4, theTransform, theX, theY), aColor, {1, 1} }      // Bottom-right
	};

	int indices[] = { 0, 1, 2, 1, 3, 2 };

	SDL_SetRenderClipRect(mRenderer, &clipRect);
	SDL_RenderGeometry(mRenderer, aTexture, vertices, 4, indices, 6);
	SDL_SetRenderClipRect(mRenderer, NULL);
	SDL_SetRenderTarget(mRenderer, nullptr);
}

void SDLInterface::DrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode)
{
	SDL_SetRenderTarget(mRenderer, mScreenTexture);


	SDL_SetRenderDrawBlendMode(mRenderer, ChooseBlendMode(theDrawMode));
	SDL_RenderLine(mRenderer, theStartX, theStartY, theEndX, theEndY);
	SDL_SetRenderDrawBlendMode(mRenderer, ChooseBlendMode(Graphics::DRAWMODE_NORMAL)); //RESET cause this aint a texture
	SDL_SetRenderTarget(mRenderer, nullptr);
}


void SDLInterface::FillRect(const Rect& theRect, const Color& theColor, int theDrawMode)
{
	SDL_SetRenderTarget(mRenderer, mScreenTexture);

	SDL_FRect theSDLRect = { theRect.mX, theRect.mY, theRect.mWidth, theRect.mHeight };

	SDL_SetRenderDrawColor(mRenderer, theColor.mRed, theColor.mGreen, theColor.mBlue, theColor.mAlpha);

	SDL_SetRenderDrawBlendMode(mRenderer, ChooseBlendMode(theDrawMode));
	SDL_RenderFillRect(mRenderer, &theSDLRect);
	SDL_SetRenderDrawBlendMode(mRenderer, ChooseBlendMode(Graphics::DRAWMODE_NORMAL)); //RESET cause this aint a texture
	SDL_SetRenderTarget(mRenderer, nullptr);
}

void SDLInterface::DrawTriangle(const TriVertex& p1, const TriVertex& p2, const TriVertex& p3, const Color& theColor, int theDrawMode)
{
	SDL_SetRenderTarget(mRenderer, mScreenTexture);

	SDL_FColor aColor = { theColor.GetRed() , theColor.GetGreen(), theColor.GetBlue(), theColor.GetAlpha() };

	int indices[] = { 0, 1, 2}; 

	SDL_Vertex vertices[3] = {
	{ SDL_FPoint {p1.x, p1.y},aColor, {p1.u, p1.v}},
	{ SDL_FPoint {p2.x, p2.y}, aColor, {p2.u, p2.v} },
	{ SDL_FPoint {p3.x, p3.y}, aColor, {p3.u, p3.v} }
	};

	SDL_RenderGeometry(mRenderer, NULL, vertices, 3, indices, 3);
	SDL_SetRenderTarget(mRenderer, nullptr);
}

void SDLInterface::DrawTriangleTex(const TriVertex& p1, const TriVertex& p2, const TriVertex& p3, const Color& theColor, int theDrawMode, Image* theTexture, bool blend)
{
	MemoryImage* aSrcMemoryImage = (MemoryImage*)theTexture;

	if (!CreateImageTexture(aSrcMemoryImage))
		return;

	SDLTextureData* aData = (SDLTextureData*)aSrcMemoryImage->mD3DData;

	SDL_SetRenderTarget(mRenderer, mScreenTexture);

	SDL_Texture* aTexture = aData->mTexture;
	SDL_SetTextureColorMod(aTexture, theColor.GetRed(), theColor.GetGreen(), theColor.GetBlue());
	SDL_SetTextureAlphaMod(aTexture, theColor.GetAlpha());
	SDL_SetTextureBlendMode(aTexture, ChooseBlendMode(theDrawMode));

	SDL_SetRenderTarget(mRenderer, mScreenTexture);

	SDL_FColor aColor = { theColor.GetRed() , theColor.GetGreen(), theColor.GetBlue(), theColor.GetAlpha() };

	int indices[] = { 0, 1, 2 };

	SDL_Vertex vertices[3] = {
	{ SDL_FPoint {p1.x, p1.y},aColor, {p1.u, p1.v}},
	{ SDL_FPoint {p2.x, p2.y}, aColor, {p2.u, p2.v} },
	{ SDL_FPoint {p3.x, p3.y}, aColor, {p3.u, p3.v} }
	};

	SDL_RenderGeometry(mRenderer, aTexture, vertices, 3, indices, 3);
	SDL_SetRenderTarget(mRenderer, nullptr);
}

void SDLInterface::DrawTrianglesTex(const TriVertex theVertices[][3], int theNumTriangles, const Color& theColor, int theDrawMode, Image* theTexture, float tx, float ty, bool blend)
{
	MemoryImage* aSrcMemoryImage = (MemoryImage*)theTexture;

	if (!CreateImageTexture(aSrcMemoryImage))
		return;

	SDLTextureData* aData = (SDLTextureData*)aSrcMemoryImage->mD3DData;

	SDL_SetRenderTarget(mRenderer, mScreenTexture);

	SDL_Texture* aTexture = aData->mTexture;
	SDL_SetTextureColorMod(aTexture, theColor.GetRed(), theColor.GetGreen(), theColor.GetBlue());
	SDL_SetTextureAlphaMod(aTexture, theColor.GetAlpha());
	SDL_SetTextureBlendMode(aTexture, ChooseBlendMode(theDrawMode));

	SDL_SetRenderTarget(mRenderer, mScreenTexture);

	for (int aTriangleNum = 0; aTriangleNum < theNumTriangles; aTriangleNum++)
	{
		TriVertex theCurrentVertex[3];
		theCurrentVertex[0] = theVertices[aTriangleNum][0];
		theCurrentVertex[1] = theVertices[aTriangleNum][1];
		theCurrentVertex[2] = theVertices[aTriangleNum][2];

		SDL_Vertex vertices[3];

		SDL_FColor aColor[3];
		aColor[0].r = (theCurrentVertex[0].color >> 16) & 0xFF;
		aColor[0].g = (theCurrentVertex[0].color >> 8) & 0xFF;
		aColor[0].b = theCurrentVertex[0].color & 0xFF;
		aColor[1].r = (theCurrentVertex[1].color >> 16) & 0xFF;
		aColor[1].g = (theCurrentVertex[1].color >> 8) & 0xFF;
		aColor[1].b = theCurrentVertex[1].color & 0xFF;
		aColor[2].r = (theCurrentVertex[2].color >> 16) & 0xFF;
		aColor[2].g = (theCurrentVertex[2].color >> 8) & 0xFF;
		aColor[2].b = theCurrentVertex[2].color & 0xFF;

		vertices[0].position.x = theCurrentVertex[0].x + tx;
		vertices[0].position.y = theCurrentVertex[0].y + ty;
		vertices[1].position.x = theCurrentVertex[1].x + tx;
		vertices[1].position.y = theCurrentVertex[1].y + ty;
		vertices[2].position.x = theCurrentVertex[2].x + tx;
		vertices[2].position.y = theCurrentVertex[2].y + ty;
		vertices[0].color = aColor[0];
		vertices[1].color = aColor[1];
		vertices[2].color = aColor[2];

		SDL_RenderGeometry(mRenderer, aTexture, vertices, 3, NULL, 3);
	}

	SDL_SetRenderTarget(mRenderer, nullptr);
}

void SDLInterface::DrawTrianglesTexStrip(const TriVertex theVertices[], int theNumTriangles, const Color& theColor, int theDrawMode, Image* theTexture, float tx, float ty, bool blend)
{
	TriVertex aList[100][3];
	int aTriNum = 0;
	while (aTriNum < theNumTriangles)
	{
		int aMaxTriangles = min(100, theNumTriangles - aTriNum);
		for (int i = 0; i < aMaxTriangles; i++)
		{
			aList[i][0] = theVertices[aTriNum];
			aList[i][1] = theVertices[aTriNum + 1];
			aList[i][2] = theVertices[aTriNum + 2];
			aTriNum++;
		}
		DrawTrianglesTex(aList, aMaxTriangles, theColor, theDrawMode, theTexture, tx, ty, blend);
	}
}

void SDLInterface::FillPoly(const Point theVertices[], int theNumVertices, const Rect* theClipRect, const Color& theColor, int theDrawMode, int tx, int ty)
{
	if (theNumVertices < 3)
		return;

	for (int i = 0; i < theNumVertices; i++)
	{
		DrawLine(theVertices[i].mX, theVertices[i].mY, theVertices[i+1].mX, theVertices[i + 1].mY, theColor, theDrawMode);
	}
}

void SDLInterface::BltTexture(SDL_Texture* theTexture,const SDL_FRect& theSrcRect, const SDL_FRect& theDestRect, const Color& theColor, int theDrawMode)
{
	SDL_SetRenderTarget(mRenderer, mScreenTexture);

	SDL_SetTextureColorMod(theTexture, theColor.GetRed(), theColor.GetGreen(), theColor.GetBlue());
	SDL_SetTextureAlphaMod(theTexture, theColor.GetAlpha());

	SDL_SetTextureBlendMode(theTexture, ChooseBlendMode(theDrawMode));
	SDL_RenderTexture(mRenderer, theTexture, &theSrcRect, &theDestRect);
	SDL_SetRenderTarget(mRenderer, nullptr);
}
