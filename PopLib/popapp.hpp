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

	    virtual void InitHook();
	    virtual void InitPropertiesHook();
	    virtual void UpdateHook();
        #if _FEATURE_DISCORD_RPC
        virtual void InitDiscordRPC();
        #endif
    };

extern PopApp* gPopApp;
}

#endif