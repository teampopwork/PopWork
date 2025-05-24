#include "jsonparser.hpp"
#include "paklib/pakinterface.hpp"

using namespace PopWork;

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
		Fail(_S("Failed to open file: ") + StringToPopStringFast(theFilename));
		return false;
	}

	// determine file size
	p_fseek(pf, 0, SEEK_END);
	long size = p_ftell(pf);
	p_fseek(pf, 0, SEEK_SET);

	if (size <= 0)
	{
		p_fclose(pf);
		Fail(_S("Empty or unreadable file: ") + StringToPopStringFast(theFilename));
		return false;
	}

	std::string jsonText(size, '\0');
	std::size_t readCount = p_fread(&jsonText[0], 1, size, pf);
	p_fclose(pf);

	if (readCount != static_cast<std::size_t>(size))
	{
		Fail(_S("Failed to read complete file: ") + StringToPopStringFast(theFilename));
		return false;
	}

	try
	{
		mJson = nlohmann::json::parse(jsonText);
	}
	catch (const nlohmann::json::parse_error &e)
	{
		Fail(_S("JSON parse error: ") + StringToPopStringFast(e.what()));
		return false;
	}

	return true;
}

int JsonParser::GetValueInt(const std::string &theName)
{
	if (mHasFailed || !mJson.contains(theName) || !mJson[theName].is_number_integer())
	{
		Fail(_S("Missing or invalid integer value for key: ") + StringToPopStringFast(theName));
		return 0;
	}

	return mJson[theName].get<int>();
}

PopString JsonParser::GetValueStr(const std::string &theName)
{
	if (mHasFailed || !mJson.contains(theName) || !mJson[theName].is_string())
	{
		Fail(_S("Missing or invalid string value for key: ") + StringToPopStringFast(theName));
		return _S("");
	}

	return StringToPopStringFast(mJson[theName].get<std::string>());
}