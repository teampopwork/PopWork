#ifndef __HYPERLINKWIDGET_H__
#define __HYPERLINKWIDGET_H__
#ifdef _WIN32
#pragma once
#endif

#include "ButtonWidget.h"

namespace Sexy
{

class HyperlinkWidget : public ButtonWidget
{
public:
	Color					mColor;
	Color					mOverColor;
	int						mUnderlineSize;
	int						mUnderlineOffset;

public:
	HyperlinkWidget(int theId, ButtonListener* theButtonListener);
	virtual ~HyperlinkWidget() {};

	void					Draw(Graphics* g);
	void					MouseEnter();
	void					MouseLeave();	
};

}

#endif