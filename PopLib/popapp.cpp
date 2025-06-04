#include "popapp.hpp"
#include "api/discord.hpp"

using namespace PopLib;

PopApp* PopLib::gPopApp = nullptr;
    
PopApp::PopApp()
{
    gPopApp = this;

    mTimesPlayed = 0;
	mTimesExecuted = 0;
	mTimedOut = false;

    #ifdef _FEATURE_DISCORD_RPC
    mRPCAppID = "1369297870456488057";
    mDiscordRPC = nullptr;
    #endif
}
    
PopApp::~PopApp()
{
    #ifdef _FEATURE_DISCORD_RPC
    if (mDiscordRPC)
        delete mDiscordRPC;
    #endif
}

void PopApp::InitHook()
{
	#if _FEATURE_DISCORD_RPC
    InitDiscordRPC();
    #endif
}

void PopApp::InitPropertiesHook()
{
	// Load properties if we need to
	bool checkSig = !IsScreenSaver();
	LoadProperties("properties\\partner.xml", false, checkSig);

	// Check to see if this build is unlocked.
	if (GetBoolean("NoReg", false))
	{
		mIsRegistered = true;
		mBuildUnlocked = true;
	}

	mProdName = GetString("ProdName", mProdName);
	mIsWindowed = GetBoolean("DefaultWindowed", mIsWindowed);	

	PopString aNewTitle = GetString("Title", "");
	if (aNewTitle.length() > 0)
		mTitle = aNewTitle + " " + mProductVersion;	
		
}

void PopApp::UpdateHook()
{
    #ifdef _FEATURE_DISCORD_RPC
    if (mDiscordRPC && mDiscordRPC->mHasInitialized)
        mDiscordRPC->UpdateRPC();
    #endif
}

#ifdef _FEATURE_DISCORD_RPC
void PopApp::InitDiscordRPC()
{
    if (mDiscordRPC)
        delete mDiscordRPC;

    mDiscordRPC = new DiscordRPC(mRPCAppID.c_str());

}
#endif