#ifndef __PROPERTIES_PARSER_H__
#define __PROPERTIES_PARSER_H__
#ifdef _WIN32
#pragma once
#endif

#include "appbase.h"

namespace PopWork
{

class XMLParser;

class PropertiesParser
{
public:
	AppBase*			mApp;
	XMLParser*				mXMLParser;
	PopWorkString				mError;
	bool					mHasFailed;

protected:
	void					Fail(const PopWorkString& theErrorText);

	bool					ParseSingleElement(PopWorkString* theString);
	bool					ParseStringArray(StringVector* theStringVector);
	bool					ParseProperties();
	bool					DoParseProperties();

public:
	PropertiesParser(AppBase* theApp);
	virtual ~PropertiesParser();

	bool					ParsePropertiesFile(const std::string& theFilename);
	bool					ParsePropertiesBuffer(const Buffer& theBuffer);
	PopWorkString				GetErrorText();
};

}

#endif