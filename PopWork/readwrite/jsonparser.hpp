#ifndef __JSONPARSER_HPP__
#define __JSONPARSER_HPP__
#ifdef _WIN32
#pragma once
#endif

#include "common.hpp"
#include <any>
#include <json.hpp>

struct PFILE;

namespace PopWork
{
    class JsonParser
    {
    protected:
        std::string mFileName;
	    PopString mErrorText;
	    int mLineNum;
	    bool mHasFailed;
        nlohmann::json mJson;

        void Fail(const PopString &theErrorText);
    public:
        JsonParser();
        ~JsonParser();

	    bool OpenFile(const std::string &theFilename);


        int GetValueInt(const std::string &theName);
        PopString GetValueStr(const std::string &theName);
    };

};

#endif //__JSONPARSER_HPP__