#ifndef __XMLDEMOAPP_H__
#define __XMLDEMOAPP_H__
#ifdef _WIN32
#pragma once
#endif

#include "PopWork/appbase.h"

namespace PopWork
{

class Board;

// This is the new class we're going to be learning about.
// It'll handle the loading and manipulation of XML files.
class XMLParser;

// These structs just represent the values from our properties/demo.xml
// file. In a real game, you'd have your own made up config file format.
// The names correspond to the attributes/sections from the XML file.
struct s_Section1
{
	PopWorkString mItem1Text;

	PopWorkString mBoolParamText;
	bool mBoolParamElement;
};

struct s_Section2
{
	PopWorkString mSectionAttribText;

	PopWorkString mIntParamText;
	int mIntParamElement;

	PopWorkString mMultiAttrib1;
	PopWorkString mMultiAttrib2;
	PopWorkString mMultiAttrib3;

	PopWorkString mSubsectionItem2;
};

class XMLDemoApp : public AppBase
{

  public:
	Board *mBoard;
	s_Section1 mSection1;
	s_Section2 mSection2;
	PopWorkString mInstructionTag;
	PopWorkString mInstruction;

  private:
	// With this class, we'll read in our sample XML file, properties/demo.xml
	XMLParser *mParser;

  private:
	//////////////////////////////////////////////////////////////////////////
	// Function:	ExtractXMLData
	// Parameters:	none
	// Returns:		false on error, otherwise true
	//
	// Purpose: After opening an XML file via the XMLParser::OpenFile() method,
	// this function then extracts out the data it needs from the sample XML file.
	// When complete, mSection1 and mSection2 will have their values initialized.
	//////////////////////////////////////////////////////////////////////////
	bool ExtractXMLData();

  public:
	XMLDemoApp();

	virtual ~XMLDemoApp();

	virtual void ShutdownHook();
	virtual void InitHook();
};

} // namespace PopWork
#endif //__XMLDEMOAPP_H__
