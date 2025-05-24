#ifndef __ERRORHANDLER_HPP__
#define __ERRORHANDLER_HPP__
#ifdef _WIN32
#pragma once
#endif

namespace PopWork
{
    class AppBase;

    class ErrorHandler
    {
    private:
        /* data */

    public:
        AppBase *mApp;

    public:
        ErrorHandler(AppBase *theApp);
        ~ErrorHandler();
    };

    extern ErrorHandler *gErrorHandler;
    
}

#endif