#include "jsonparser.hpp"
#include "paklib/pakinterface.hpp"

using namespace PopWork;

    
JsonParser::JsonParser()
{
}
    
JsonParser::~JsonParser()
{
}

bool JsonParser::OpenFile(const std::string &theFileName)
{
	return false;
}

int JsonParser::GetValueInt(const std::string &theName)
{
	return INT_MIN;
}
    
PopString JsonParser::GetValueStr(const std::string &theName)
{
	return StringToPopStringFast("");
}

void JsonParser::Fail(const PopString &theErrorText)
{
	mHasFailed = true;
	mErrorText = theErrorText;
}
