// xmlwriter.h: interface for the XMLWriter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLWRITER_H__3DB6D22D_A120_4738_B622_06E90FAED4E4__INCLUDED_)
#define AFX_XMLWRITER_H__3DB6D22D_A120_4738_B622_06E90FAED4E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)
#pragma warning(disable : 4503)

#include <stack>
#include "xmlparser.h"
#include "common.h"

#include "debug/perftimer.h"

namespace PopWork
{
class XMLWriter
{
  protected:
	PopWorkString mFileName;
	PopWorkString mErrorText;
	int mLineNum;
	FILE *mFile;
	bool mHasFailed;
	bool mAllowComments;
	bool mOpenAttributes;

	std::stack<PopWorkString> mSectionStack;
	std::stack<PopWorkString> mWarningStack;

  protected:
	bool CheckFileOpen();
	bool ValidateElementNodeName(const PopWorkString &theNodeName);
	void Fail(const PopWorkString &theErrorText);
	void Warn(const PopWorkString &theWarning);
	void Init();

  public:
	XMLWriter();
	virtual ~XMLWriter();

	static bool AddAttribute(XMLElement *theElement, const PopWorkString &aAttributeKey,
							 const PopWorkString &aAttributeValue);
	bool WriteAttribute(const PopWorkString &aAttributeKey, const PopWorkString &aAttributeValue);
	bool WriteAttribute(const PopWorkString &aAttributeKey, const float &aAttributeValue);
	bool WriteAttribute(const PopWorkString &aAttributeKey, const int &aAttributeValue);
	bool WriteAttribute(const PopWorkString &aAttributeKey);
	void Comment(const PopWorkString &theComment);
	bool StartElement(const PopWorkString &theElementName);
	bool StartElement(XMLElement *theElement);
	bool StopElement();
	bool WriteElementText(PopWorkString theText);
	bool OpenFile(const PopWorkString &theFilename);
	bool CloseFile();
	PopWorkString GetErrorText();
	int GetCurrentLineNum();
	PopWorkString GetFileName();

	inline void AllowComments(bool doAllow)
	{
		mAllowComments = doAllow;
	}

	bool HasFailed();
};
}; // namespace PopWork

#endif // !defined(AFX_XMLWRITER_H__3DB6D22D_A120_4738_B622_06E90FAED4E4__INCLUDED_)
