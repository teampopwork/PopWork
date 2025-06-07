#include "xmlparser.hpp"
#include "debug/debug.hpp"
#include "paklib/pakinterface.hpp"

using namespace PopLib;

XMLParser::XMLParser()
{
	mFile = NULL;
	mLineNum = 0;
	mCurrentNode = nullptr;
	mFirstStart = true;
}

XMLParser::~XMLParser()
{
	if (mFile != NULL)
		p_fclose(mFile);
}

void XMLParser::Fail(const PopString &theErrorText)
{
	mHasFailed = true;
	mErrorText = theErrorText;
}

void XMLParser::Init()
{
    mLineNum = 1;
    mHasFailed  = false;
    mCurrentNode = nullptr;
    mSectionStack.clear();
}

bool XMLParser::AddAttribute(XMLElement *theElement, const PopString &theAttributeKey, const PopString &theAttributeValue)
{
	std::pair<XMLParamMap::iterator, bool> aRet;

	aRet = theElement->mAttributes.insert(XMLParamMap::value_type(theAttributeKey, theAttributeValue));
	if (!aRet.second)
		aRet.first->second = theAttributeValue;

	if (theAttributeKey != "/")
		theElement->mAttributeIteratorList.push_back(aRet.first);

	return aRet.second;
}

bool XMLParser::OpenBuffer(const std::string &theBuffer)
{
	mCurrentNode = nullptr;
	mSectionStack.clear();
	mEndPending.clear();
	mHasFailed = false;

	const char* data = theBuffer.c_str();
	size_t size   = theBuffer.size();
	if (size >= 3 && (unsigned char)data[0]==0xEF && (unsigned char)data[1]==0xBB && (unsigned char)data[2]==0xBF)
	{
		data += 3; size -= 3;
	}

	XMLError err = mDocument.Parse(data, size);
	if (err != XML_SUCCESS) { 
		std::string anError = mDocument.ErrorStr();
		Fail("Parse error: " + anError); 
		return false;
	}
	return true;
}

bool XMLParser::OpenFile(const std::string &theFileName)
{
	mFile = p_fopen(theFileName.c_str(), "r");

	if (mFile == NULL)
	{
		mLineNum = 0;
		Fail("Unable to open file " + theFileName);
		return false;
	}

	p_fseek(mFile, 0, SEEK_END);
	long size = p_ftell(mFile);
	p_fseek(mFile, 0, SEEK_SET);

	if (size <= 0)
	{
		p_fclose(mFile);
		Fail("Empty or unreadable file: " + theFileName);
		return false;
	}

	std::string content(size, '\0');
	p_fread(content.data(), size, 1, mFile);

	XMLError result = mDocument.Parse(content.c_str(), content.size());
    if (result != tinyxml2::XML_SUCCESS)
    {
        Fail("Failed to parse XML file " + theFileName + ": " + mDocument.ErrorStr());
        return false;
    }

	mFileName = theFileName;
	Init();
	return true;
}

bool XMLParser::NextElement(XMLElement *theElement)
{

    if (!mEndPending.empty())
    {
        theElement->mType = XMLElement::TYPE_END;
        theElement->mValue = mEndPending.back();
        theElement->mSection = mSectionStack.back();
        mEndPending.pop_back();
        mSectionStack.pop_back();
        return true;
    }

	while (!mNodeStack.empty() && mCurrentNode == nullptr)
    {
        XMLNode* parent = mNodeStack.back();
        mNodeStack.pop_back();

        theElement->mType = XMLElement::TYPE_END;
        theElement->mValue = parent->ToElement()->Name();
        theElement->mSection = mSectionStack.back();
        mSectionStack.pop_back();

        mCurrentNode = parent->NextSibling();
		if (mCurrentNode)
			mLineNum = mCurrentNode->GetLineNum();
        return true;
    }

	if (!mCurrentNode && mFirstStart)
    {
        mCurrentNode = mDocument.FirstChild();
        mFirstStart = false;
    }
    else if (!mCurrentNode && !mFirstStart)
    {
        // No more nodes to process, end of document reached
        return false;
    }

    while (mCurrentNode &&
           !mCurrentNode->ToElement() &&
           !mCurrentNode->ToComment() &&
           !mCurrentNode->ToDeclaration())
    {
        mCurrentNode = mCurrentNode->NextSibling();
    }

  	if (!mCurrentNode)
        return false;

    theElement->mAttributes.clear();
    theElement->mInstruction.clear();
    theElement->mValue.clear();
    theElement->mSection.clear();

    if (auto com = mCurrentNode->ToComment()) // Comments
    {
		mLineNum = mCurrentNode->GetLineNum();
        theElement->mType = XMLElement::TYPE_COMMENT;
        theElement->mInstruction = com->Value();
        mCurrentNode = mCurrentNode->NextSibling();
        return true;
    }
    else if (auto decl = mCurrentNode->ToDeclaration()) // XML declaration / PI
    {
		mLineNum = mCurrentNode->GetLineNum();
        theElement->mType        = XMLElement::TYPE_INSTRUCTION;
        theElement->mInstruction = decl->Value();
		mCurrentNode = mCurrentNode->NextSibling();
        return true;
    }
    else if (auto elem = mCurrentNode->ToElement()) // Element start
    {
		mLineNum = mCurrentNode->GetLineNum();
        theElement->mType   = XMLElement::TYPE_START;
        theElement->mValue  = elem->Name();

        if (mSectionStack.empty())
            mSectionStack.push_back(elem->Name());
        else
            mSectionStack.push_back(mSectionStack.back() + "/" + elem->Name());
        theElement->mSection = mSectionStack.back();

        for (auto attr = elem->FirstAttribute(); attr; attr = attr->Next())
            AddAttribute(theElement, attr->Name(), attr->Value());

		if (elem->FirstChild())
        {
            mCurrentNode = elem->FirstChild();
			mNodeStack.push_back(elem);
        }
		else
		{
			mEndPending.push_back(elem->Name());
            mCurrentNode = elem->NextSibling();
		}

        return true;
    }

	return false;
}

bool XMLParser::HasFailed()
{
	return mHasFailed;
}

PopString XMLParser::GetErrorText()
{
	return mErrorText;
}

int XMLParser::GetCurrentLineNum()
{
	return mLineNum;
}

std::string XMLParser::GetFileName()
{
	return mFileName;
}