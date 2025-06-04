#include "jsonparser.hpp"
#include "paklib/pakinterface.hpp"

using namespace PopLib;

JsonParser::JsonParser() : mLineNum(0), mHasFailed(false)
{
}

JsonParser::~JsonParser() = default;

void JsonParser::Fail(const PopString &theErrorText)
{
	mHasFailed = true;
	mErrorText = theErrorText;
}

bool JsonParser::OpenFile(const std::string &theFilename)
{
	mFileName = theFilename;
	mHasFailed = false;
	mErrorText.clear();

	PFILE *pf = p_fopen(theFilename.c_str(), "rb");
	if (!pf)
	{
		Fail("Failed to open file: " + theFilename);
		return false;
	}

	// determine file size
	p_fseek(pf, 0, SEEK_END);
	long size = p_ftell(pf);
	p_fseek(pf, 0, SEEK_SET);

	if (size <= 0)
	{
		p_fclose(pf);
		Fail("Empty or unreadable file: " + theFilename);
		return false;
	}

	std::string jsonText(size, '\0');
	std::size_t readCount = p_fread(&jsonText[0], 1, size, pf);
	p_fclose(pf);

	if (readCount != static_cast<std::size_t>(size))
	{
		Fail("Failed to read complete file: " + theFilename);
		return false;
	}

	try
	{
		mJson = nlohmann::json::parse(jsonText);
	}
	catch (const nlohmann::json::parse_error &e)
	{
		Fail(std::string("JSON parse error: ") + e.what());
		return false;
	}

	return true;
}

int JsonParser::GetValueInt(const std::string &theName)
{
	if (mHasFailed || !mJson.contains(theName) || !mJson[theName].is_number_integer())
	{
		Fail("Missing or invalid integer value for key: " + theName);
		return 0;
	}

	return mJson[theName].get<int>();
}

PopString JsonParser::GetValueStr(const std::string &theName)
{
	if (mHasFailed || !mJson.contains(theName) || !mJson[theName].is_string())
	{
		Fail("Missing or invalid string value for key: " + theName);
		return "";
	}

	return mJson[theName].get<std::string>();
}