#include "gameapp.hpp"
#include "board.hpp"
#include "PopWork/widget/widgetmanager.hpp"
#include "PopWork/common.hpp"

using namespace PopWork;

GameApp::GameApp()
{
	mProdName = "BareBones";

	mProductVersion = "1.0";

	mTitle = StringToPopStringFast("PopWork: " + mProdName + " - " + mProductVersion);

	mRegKey = "PopCap\\PopWork\\BareBones";

	mWidth = 640;
	mHeight = 480;

	mBoard = NULL;
	mNoSoundNeeded = true;
}

GameApp::~GameApp()
{
	mWidgetManager->RemoveWidget(mBoard);
	delete mBoard;
}

void GameApp::Init()
{
	AppBase::Init();
}

void GameApp::LoadingThreadProc()
{
}

void GameApp::LoadingThreadCompleted()
{
	AppBase::LoadingThreadCompleted();

	// load your stuff in here

	if (mLoadingFailed)
		return;

	mBoard = new Board(this);

	mBoard->Resize(0, 0, mWidth, mHeight);

	mWidgetManager->AddWidget(mBoard);
}