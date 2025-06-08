#ifndef __XMLPARSER_HPP__
#define __XMLPARSER_HPP__
#ifdef _WIN32
#pragma once
#endif

#include "common.hpp"
#include "debug/perftimer.hpp"
#include <tinyxml2.h>

using namespace tinyxml2;
struct PFILE;

namespace PopLib
{

class XMLParam
{
  public:
	std::string mKey;
	std::string mValue;
};

typedef std::map<PopString, PopString> XMLParamMap;
typedef std::list<XMLParamMap::iterator> XMLParamMapIteratorList;

typedef std::vector<uchar> XMLParserBuffer;

class XMLElement
{
  public:
	enum
	{
		TYPE_NONE,
		TYPE_START,
		TYPE_END,
		TYPE_ELEMENT,
		TYPE_INSTRUCTION,
		TYPE_COMMENT
	};

  public:
	int mType;
	PopString mSection;
	PopString mValue;
	PopString mInstruction;
	XMLParamMap mAttributes;
	XMLParamMapIteratorList mAttributeIteratorList; // stores attribute iterators in their original order
};

class XMLParser
{
  protected:
	std::string mFileName;
	PopString mErrorText;
	int mLineNum;
	PFILE *mFile;
	bool mHasFailed;
	bool mFirstChar;
	bool mByteSwap;
    XMLDocument* mDocument;
    XMLNode* mCurrentNode;
	/// @brief current elements
	std::vector<PopString> mSectionStack;
	/// @brief names of elements that await TYPE_END
	std::vector<PopString> mEndPending;
	
	/// @brief the processed children
	std::vector<PopString> mProcessedChildren;
	/// @brief stack of parent elements
	std::vector<XMLNode*> mNodeStack;
	bool mFirstStart;

  protected:
	void Fail(const PopString &theErrorText);
	void Init();

	bool AddAttribute(XMLElement *theElement, const PopString &aAttributeKey, const PopString &aAttributeValue);

  public:
	XMLParser();
	virtual ~XMLParser();

	bool OpenFile(const std::string &theFilename, const std::string &custom_root = "");
	bool OpenBuffer(const std::string &theBuffer, const std::string &custom_root = "");
	bool NextElement(XMLElement *theElement);
	PopString GetErrorText();
	int GetCurrentLineNum();
	std::string GetFileName();

	bool HasFailed();
};

}; // namespace PopLib

#endif
