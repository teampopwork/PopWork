#ifndef __POPAPP_HPP__
#define __POPAPP_HPP__
#ifdef _WIN32
#pragma once
#endif

#include "appbase.hpp"

namespace PopLib
{
    class DiscordRPC;

    class PopApp: public AppBase
    {
    public:
        #if _FEATURE_DISCORD_RPC
        DiscordRPC* mDiscordRPC;

        std::string mRPCAppID;
        #endif

        std::string mBetaSupportSiteOverride;
        std::string mBetaSupportProdNameOverride;
        std::string mReferId;
        std::string mVariation;
        ulong mDownloadId;
        std::string mRegSource;
        ulong mLastVerCheckQueryTime;
        bool mSkipAd;
        bool mDontUpdate;	

        int mBuildNum;
        std::string mBuildDate;

        std::string mUserName;
        std::string mRegUserName;
        std::string mRegCode;
        bool mIsRegistered;	
        bool mBuildUnlocked;

        int mTimesPlayed;
        int mTimesExecuted;
        bool mTimedOut;
    public:
        PopApp();
        virtual ~PopApp();

    	virtual void Init();
	    virtual void InitHook();
	    virtual void InitPropertiesHook();
        virtual bool CheckSignature(const Buffer& theBuffer, const std::string& theFileName);
	    virtual void UpdateHook();
    	virtual void OpenUpdateURL();
	    virtual void PreDisplayHook();
    	virtual void PreTerminate();
        virtual void ReadFromRegistry();

        bool Validate(const std::string& theUserName, const std::string& theRegCode);

        virtual bool OpenRegisterPage(DefinesMap theDefinesMap);
        virtual bool OpenRegisterPage();
        #if _FEATURE_DISCORD_RPC
        virtual void InitDiscordRPC();
        #endif
    };

extern PopApp* gPopApp;
}

#endif