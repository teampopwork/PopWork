#ifndef __TEXTWIDGET_H__
#define __TEXTWIDGET_H__
#ifdef _WIN32
#pragma once
#endif

#include "widget.h"
#include "scrolllistener.h"

namespace PopWork
{

class ScrollbarWidget;
class Font;

typedef std::vector<PopWorkString> PopWorkStringVector;
typedef std::vector<int> IntVector;

class TextWidget : public Widget, public ScrollListener
{
public:
	Font*				mFont;
	ScrollbarWidget*	mScrollbar;		
	
	PopWorkStringVector	mLogicalLines;
	PopWorkStringVector	mPhysicalLines;	
	IntVector			mLineMap;
	double				mPosition;
	double				mPageSize;	
	bool				mStickToBottom;	
	int					mHiliteArea[2][2];
	int					mMaxLines;
	
public:
	TextWidget();

	virtual PopWorkStringVector GetLines();
	virtual void SetLines(PopWorkStringVector theNewLines);	
	virtual void Clear();		
	virtual void DrawColorString(Graphics* g, const PopWorkString& theString, int x, int y, bool useColors);			
	virtual void DrawColorStringHilited(Graphics* g, const PopWorkString& theString, int x, int y, int theStartPos, int theEndPos);		
	virtual int GetStringIndex(const PopWorkString& theString, int thePixel);
	
	virtual int GetColorStringWidth(const PopWorkString& theString);
	virtual void Resize(int theX, int theY, int theWidth, int theHeight);		
	virtual Color GetLastColor(const PopWorkString& theString);		
	virtual void AddToPhysicalLines(int theIdx, const PopWorkString& theLine);
	
	virtual void AddLine(const PopWorkString& theString);
	virtual bool SelectionReversed();		
	virtual void GetSelectedIndices(int theLineIdx, int* theIndices);		
	virtual void Draw(Graphics* g);
	virtual void ScrollPosition(int theId, double thePosition);		
	virtual void GetTextIndexAt(int x, int y, int* thePosArray);
	virtual PopWorkString GetSelection();		

	virtual void MouseDown(int x, int y, int theClickCount);		
	virtual void MouseDrag(int x, int y);	
	
	virtual void KeyDown(KeyCode theKey);
};

}

#endif