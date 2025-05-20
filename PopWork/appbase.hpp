#ifndef __APPBASE_HPP__
#define __APPBASE_HPP__
#ifdef _WIN32
#pragma once
#endif

#include "common.hpp"
#include "math/rect.hpp"
#include "graphics/color.hpp"
#include "widget/buttonlistener.hpp"
#include "widget/dialoglistener.hpp"
#include "misc/buffer.hpp"
#include "misc/critsect.hpp"
#include "graphics/sharedimage.hpp"
#include "math/ratio.hpp"
#include <mutex>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

// H522
enum JSON_RTYPE
{
	JSON_NONE = 0,
	JSON_STRING,
	JSON_INTEGER,
	JSON_BOOLEAN,
	JSON_DATA,
	JSON_LAST
};

namespace ImageLib
{
class Image;
};

namespace PopWork
{

class WidgetManager;
class SDLInterface;
class Image;
class SDLImage;
class Widget;
class SoundManager;
class MusicInterface;
class MemoryImage;
class HTTPTransfer;
class Dialog;

class ResourceManager;

class WidgetSafeDeleteInfo
{
  public:
	int mUpdateAppDepth;
	Widget *mWidget;
};

typedef std::list<WidgetSafeDeleteInfo> WidgetSafeDeleteList;
typedef std::set<MemoryImage *> MemoryImageSet;
typedef std::map<int, Dialog *> DialogMap;
typedef std::list<Dialog *> DialogList;
typedef std::vector<std::string> StringVector;
// typedef std::basic_string<TCHAR> tstring; // string of TCHARs

typedef std::map<std::string, PopString> StringPopStringMap;
typedef std::map<std::string, std::string> StringStringMap;
typedef std::map<std::string, std::wstring> StringWStringMap;
typedef std::map<std::string, bool> StringBoolMap;
typedef std::map<std::string, int> StringIntMap;
typedef std::map<std::string, double> StringDoubleMap;
typedef std::map<std::string, StringVector> StringStringVectorMap;

enum
{
	CURSOR_POINTER,
	CURSOR_HAND,
	CURSOR_DRAGGING,
	CURSOR_TEXT,
	CURSOR_CIRCLE_SLASH,
	CURSOR_SIZEALL,
	CURSOR_SIZENESW,
	CURSOR_SIZENS,
	CURSOR_SIZENWSE,
	CURSOR_SIZEWE,
	CURSOR_WAIT,
	CURSOR_NONE,
	CURSOR_CUSTOM,
	NUM_CURSORS
};

enum
{
	FPS_ShowFPS,
	FPS_ShowCoords,
	Num_FPS_Types
};

enum
{
	UPDATESTATE_MESSAGES,
	UPDATESTATE_PROCESS_1,
	UPDATESTATE_PROCESS_2,
	UPDATESTATE_PROCESS_DONE
};

enum MsgBoxFlags
{
	MsgBox_OK = 0,
	MsgBox_OKCANCEL = 1,
	MsgBox_ABORTRETRYIGNORE = 2,
	MsgBox_YESNOCANCEL = 3,
	MsgBox_YESNO = 4,
	MsgBox_RETRYCANCEL = 5,
};

class AppBase : public ButtonListener, public DialogListener
{
  public:
	ulong mRandSeed;

	std::string mCompanyName;
	std::string mFullCompanyName;
	std::string mProdName;
	PopString mTitle;
	std::string mRegKey;
	std::string mChangeDirTo;

	int mRelaxUpdateBacklogCount; // app doesn't try to catch up for this many frames
	int mPreferredX;
	int mPreferredY;
	int mWidth;
	int mHeight;
	int mFullscreenBits;
	double mMusicVolume;
	double mSfxVolume;
	bool mNoSoundNeeded;
	bool mCmdLineParsed;
	bool mSkipSignatureChecks;
	bool mStandardWordWrap;
	bool mbAllowExtendedChars;

	std::mutex *mMutex;
	bool mOnlyAllowOneCopyToRun;
	CritSect mCritSect;
	bool mBetaValidate;
	uchar mAdd8BitMaxTable[512];
	WidgetManager *mWidgetManager;
	DialogMap mDialogMap;
	DialogList mDialogList;
	SDL_ThreadID mPrimaryThreadId;
	bool mSEHOccured;
	bool mShutdown;
	bool mExitToTop;
	bool mIsWindowed;
	bool mIsPhysWindowed;
	bool mFullScreenWindow; // uses ChangeDisplaySettings to run fullscreen with mIsWindowed true
	bool mForceFullscreen;
	bool mForceWindowed;
	bool mInitialized;
	bool mProcessInTimer;
	uint32_t mTimeLoaded;
	bool mIsScreenSaver;
	bool mAllowMonitorPowersave;
	bool mNoDefer;
	bool mFullScreenPageFlip;
	bool mTabletPC;
	SDLInterface *mSDLInterface;
	bool mAlphaDisabled;
	MusicInterface *mMusicInterface;
	bool mReadFromRegistry;
	std::string mRegisterLink;
	std::string mProductVersion;
	Image *mCursorImages[NUM_CURSORS];
	Image *mTitleBarIcon;
	SDL_Cursor *mOverrideCursor;
	bool mIsOpeningURL;
	bool mShutdownOnURLOpen;
	std::string mOpeningURL;
	uint32_t mOpeningURLTime;
	uint32_t mLastTimerTime;
	uint32_t mLastBigDelayTime;
	double mUnmutedMusicVolume;
	double mUnmutedSfxVolume;
	int mMuteCount;
	int mAutoMuteCount;
	bool mMuteOnLostFocus;
	MemoryImageSet mMemoryImageSet;
	SharedImageMap mSharedImageMap;
	bool mCleanupSharedImages;

	int mNonDrawCount;
	int mFrameTime;

	bool mIsDrawing;
	bool mLastDrawWasEmpty;
	bool mHasPendingDraw;
	double mPendingUpdatesAcc;
	double mUpdateFTimeAcc;
	uint64_t mLastTimeCheck;
	uint64_t mLastTime;
	uint64_t mLastUserInputTick;

	int mSleepCount;
	int mDrawCount;
	int mUpdateCount;
	int mUpdateAppState;
	int mUpdateAppDepth;
	double mUpdateMultiplier;
	bool mPaused;
	int mFastForwardToUpdateNum;
	bool mFastForwardToMarker;
	bool mFastForwardStep;
	uint64_t mLastDrawTick;
	uint64_t mNextDrawTick;
	int mStepMode; // 0 = off, 1 = step, 2 = waiting for step

	int mCursorNum;
	SoundManager *mSoundManager;
	SDL_Cursor *mHandCursor;
	SDL_Cursor *mDraggingCursor;
	WidgetSafeDeleteList mSafeDeleteList;
	bool mMouseIn;
	bool mRunning;
	bool mActive;
	bool mMinimized;
	bool mPhysMinimized;
	bool mIsDisabled;
	bool mHasFocus;
	int mDrawTime;
	uint64_t mFPSStartTick;
	int mFPSFlipCount;
	int mFPSDirtyCount;
	int mFPSTime;
	int mFPSCount;
	bool mShowFPS;
	int mShowFPSMode;
	int mScreenBltTime;
	bool mAutoStartLoadingThread;
	bool mLoadingThreadStarted;
	bool mLoadingThreadCompleted;
	bool mLoaded;
	bool mYieldMainThread;
	bool mLoadingFailed;
	bool mCursorThreadRunning;
	bool mSysCursor;
	bool mCustomCursorsEnabled;
	bool mCustomCursorDirty;
	bool mLastShutdownWasGraceful;
	bool mIsWideWindow;

	int mNumLoadingThreadTasks;
	int mCompletedLoadingThreadTasks;

	bool mDebugKeysEnabled;
	bool mEnableMaximizeButton;
	bool mCtrlDown;
	bool mAltDown;

	int mSyncRefreshRate;
	bool mVSyncUpdates;
	bool mVSyncBroken;
	int mVSyncBrokenCount;
	uint32_t mVSyncBrokenTestStartTick;
	uint32_t mVSyncBrokenTestUpdates;
	bool mWaitForVSync;
	bool mSoftVSyncWait;
	bool mUserChanged3DSetting;
	bool mAutoEnable3D;
	bool mTest3D;
	uint32_t mMinVidMemory3D;
	uint32_t mRecommendedVidMemory3D;

	bool mWidescreenAware;
	Rect mScreenBounds;
	bool mEnableWindowAspect;
	Ratio mWindowAspect;

	StringWStringMap mStringProperties;
	StringBoolMap mBoolProperties;
	StringIntMap mIntProperties;
	StringDoubleMap mDoubleProperties;
	StringStringVectorMap mStringVectorProperties;
	ResourceManager *mResourceManager;

#ifdef ZYLOM
	uint mZylomGameId;
#endif

  protected:
	void RehupFocus();
	void ClearKeysDown();
	bool ProcessDeferredMessages(bool singleMessage);
	void UpdateFTimeAcc();
	virtual bool Process(bool allowSleep = true);
	virtual void UpdateFrames();
	virtual bool DoUpdateFrames();
	virtual void DoUpdateFramesF(float theFrac);
	virtual void MakeWindow();
	virtual void EnforceCursor();
	virtual void ReInitImages();
	virtual void DeleteNativeImageData();
	virtual void DeleteExtraImageData();

	// Loading thread methods
	virtual void LoadingThreadCompleted();
	static int LoadingThreadProcStub(void *theArg);

	// Cursor thread methods
	void CursorThreadProc();
	static int CursorThreadProcStub(void *theArg);
	void StartCursorThread();

	void WaitForLoadingThread();
	void ProcessSafeDeleteList();
	void RestoreScreenResolution();
	void DoExit(int theCode);

	void TakeScreenshot();
	void DumpProgramInfo();
	void ShowMemoryUsage();

	// Registry helpers
	bool RegistryRead(const std::string &theValueName, JSON_RTYPE *theType, uchar *theValue, ulong *theLength);
	bool RegistryReadKey(const std::string &theValueName, JSON_RTYPE *theType, uchar *theValue, ulong *theLength,
						 ulong theMainKey = 0);
	bool RegistryWrite(const std::string &theValueName, JSON_RTYPE theType, const uchar *theValue, ulong theLength);

  public:
	AppBase();
	virtual ~AppBase();

	// Common overrides:
	virtual MusicInterface *CreateMusicInterface();
	virtual void InitHook();
	virtual void ShutdownHook();
	virtual void PreTerminate();
	virtual void LoadingThreadProc();
	virtual void WriteToRegistry();
	virtual void ReadFromRegistry();
	virtual Dialog *NewDialog(int theDialogId, bool isModal, const PopString &theDialogHeader,
							  const PopString &theDialogLines, const PopString &theDialogFooter,
							  int theButtonMode);
	virtual void PreDisplayHook();

	// Public methods
	virtual void BeginPopup();
	virtual void EndPopup();
	virtual int MsgBox(const std::string &theText, const std::string &theTitle = "Message", int theFlags = 0);
	virtual int MsgBox(const std::wstring &theText, const std::wstring &theTitle = L"Message", int theFlags = 0);
	virtual void Popup(const std::string &theString);
	virtual void Popup(const std::wstring &theString);
	virtual void LogScreenSaverError(const std::string &theError);
	virtual void SafeDeleteWidget(Widget *theWidget);

	virtual void URLOpenFailed(const std::string &theURL);
	virtual void URLOpenSucceeded(const std::string &theURL);
	virtual bool OpenURL(const std::string &theURL, bool shutdownOnOpen = false);
	virtual std::string GetProductVersion(const std::string &thePath);

	virtual void SEHOccured();
	virtual std::string GetGameSEHInfo();
	virtual void GetSEHWebParams(DefinesMap *theDefinesMap);
	virtual void Shutdown();

	virtual void DoParseCmdLine();
	virtual void ParseCmdLine(const std::string &theCmdLine);
	virtual void HandleCmdLineParam(const std::string &theParamName, const std::string &theParamValue);
	virtual void HandleNotifyGameMessage(
		int theType,
		int theParam); // for HWND_BROADCAST of mNotifyGameMessage (0-1000 are reserved for AppBase for theType)
	virtual void HandleGameAlreadyRunning();

	virtual void Start();
	virtual void Init();
	virtual void PreSDLInterfaceInitHook();
	virtual void PostSDLInterfaceInitHook();
	virtual bool ChangeDirHook(const char *theIntendedPath);
	virtual void PlaySample(int theSoundNum);
	virtual void PlaySample(int theSoundNum, int thePan);

	virtual double GetMasterVolume();
	virtual double GetMusicVolume();
	virtual double GetSfxVolume();
	virtual bool IsMuted();

	virtual void SetMasterVolume(double theVolume);
	virtual void SetMusicVolume(double theVolume);
	virtual void SetSfxVolume(double theVolume);
	virtual void Mute(bool autoMute = false);
	virtual void Unmute(bool autoMute = false);

	void StartLoadingThread();
	virtual double GetLoadingThreadProgress();

	void CopyToClipboard(const std::string &theString);
	std::string GetClipboard();

	void SetCursor(int theCursorNum);
	int GetCursor();
	void EnableCustomCursors(bool enabled);
	virtual SDLImage *GetImage(const std::string &theFileName, bool commitBits = true);
	virtual SharedImageRef GetSharedImage(const std::string &theFileName, const std::string &theVariant = "",
										  bool *isNew = NULL);

	void SetTaskBarIcon(const std::string &theFileName);

	void CleanSharedImages();
	void PrecacheAdditive(MemoryImage *theImage);
	void PrecacheAlpha(MemoryImage *theImage);
	void PrecacheNative(MemoryImage *theImage);
	void SetCursorImage(int theCursorNum, Image *theImage);

	SDLImage *CreateCrossfadeImage(Image *theImage1, const Rect &theRect1, Image *theImage2, const Rect &theRect2,
								   double theFadeFactor);
	void ColorizeImage(Image *theImage, const Color &theColor);
	SDLImage *CreateColorizedImage(Image *theImage, const Color &theColor);
	SDLImage *CopyImage(Image *theImage, const Rect &theRect);
	SDLImage *CopyImage(Image *theImage);
	void MirrorImage(Image *theImage);
	void FlipImage(Image *theImage);
	void RotateImageHue(PopWork::MemoryImage *theImage, int theDelta);
	ulong HSLToRGB(int h, int s, int l);
	ulong RGBToHSL(int r, int g, int b);
	void HSLToRGB(const ulong *theSource, ulong *theDest, int theSize);
	void RGBToHSL(const ulong *theSource, ulong *theDest, int theSize);

	void AddMemoryImage(MemoryImage *theMemoryImage);
	void RemoveMemoryImage(MemoryImage *theMemoryImage);
	void Remove3DData(MemoryImage *theMemoryImage);
	virtual void SwitchScreenMode();
	virtual void SwitchScreenMode(bool wantWindowed);
	virtual void SwitchScreenMode(bool wantWindowed, bool is3d, bool force = false);
	virtual void SetAlphaDisabled(bool isDisabled);

	virtual Dialog *DoDialog(int theDialogId, bool isModal, const PopString &theDialogHeader,
							 const PopString &theDialogLines, const PopString &theDialogFooter,
							 int theButtonMode);
	virtual Dialog *GetDialog(int theDialogId);
	virtual void AddDialog(int theDialogId, Dialog *theDialog);
	virtual void AddDialog(Dialog *theDialog);
	virtual bool KillDialog(int theDialogId, bool removeWidget, bool deleteWidget);
	virtual bool KillDialog(int theDialogId);
	virtual bool KillDialog(Dialog *theDialog);
	virtual int GetDialogCount();
	virtual void ModalOpen();
	virtual void ModalClose();
	virtual void DialogButtonPress(int theDialogId, int theButtonId);
	virtual void DialogButtonDepress(int theDialogId, int theButtonId);

	virtual void GotFocus();
	virtual void LostFocus();
	virtual bool IsAltKeyUsed(long wParam);
	virtual bool DebugKeyDown(int theKey);
	virtual bool DebugKeyDownAsync(int theKey, bool ctrlDown, bool altDown);
	virtual void CloseRequestAsync();
	bool Is3DAccelerated();
	bool Is3DAccelerationSupported();
	bool Is3DAccelerationRecommended();
	void Set3DAcclerated(bool is3D, bool reinit = true);
	virtual void Done3dTesting();
	virtual std::string NotifyCrashHook(); // return file name that you want to upload

	virtual bool CheckSignature(const Buffer &theBuffer, const std::string &theFileName);
	virtual bool DrawDirtyStuff();
	virtual void Redraw(Rect *theClipRect);

	// Properties access methods
	bool LoadProperties(const std::string &theFileName, bool required, bool checkSig);
	bool LoadProperties();
	virtual void InitPropertiesHook();

	// Resource access methods
	void LoadResourceManifest();
	void ShowResourceError(bool doExit = false);

	bool GetBoolean(const std::string &theId);
	bool GetBoolean(const std::string &theId, bool theDefault);
	int GetInteger(const std::string &theId);
	int GetInteger(const std::string &theId, int theDefault);
	double GetDouble(const std::string &theId);
	double GetDouble(const std::string &theId, double theDefault);
	PopString GetString(const std::string &theId);
	PopString GetString(const std::string &theId, const PopString &theDefault);

	StringVector GetStringVector(const std::string &theId);

	void SetBoolean(const std::string &theId, bool theValue);
	void SetInteger(const std::string &theId, int theValue);
	void SetDouble(const std::string &theId, double theValue);
	void SetString(const std::string &theId, const std::wstring &theValue);

	// Registry access methods
	bool RegistryGetSubKeys(const std::string &theKeyName, StringVector *theSubKeys);
	bool RegistryReadString(const std::string &theValueName, std::string *theString);
	bool RegistryReadInteger(const std::string &theValueName, int *theValue);
	bool RegistryReadBoolean(const std::string &theValueName, bool *theValue);
	bool RegistryReadData(const std::string &theValueName, uchar *theValue, ulong *theLength);
	bool RegistryWriteString(const std::string &theValueName, const std::string &theString);
	bool RegistryWriteInteger(const std::string &theValueName, int theValue);
	bool RegistryWriteBoolean(const std::string &theValueName, bool theValue);
	bool RegistryWriteData(const std::string &theValueName, const uchar *theValue, ulong theLength);
	bool RegistryEraseKey(const PopString &theKeyName);
	void RegistryEraseValue(const PopString &theValueName);

	// File access methods
	bool WriteBufferToFile(const std::string &theFileName, const Buffer *theBuffer);
	bool ReadBufferFromFile(const std::string &theFileName, Buffer *theBuffer); // UNICODE
	bool WriteBytesToFile(const std::string &theFileName, const void *theData, unsigned long theDataLen);
	bool FileExists(const std::string &theFileName);
	bool EraseFile(const std::string &theFileName);

	// Misc methods
	virtual void DoMainLoop();
	virtual bool UpdateAppStep(bool *updated);
	virtual bool UpdateApp();
	int InitSDLInterface();
	void ClearUpdateBacklog(bool relaxForASecond = false);
	bool IsScreenSaver();
	virtual bool AppCanRestore();
};

extern AppBase *gAppBase;

}; // namespace PopWork

#endif