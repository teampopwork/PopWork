#ifndef __CURSORWIDGET_H__
#define __CURSORWIDGET_H__
#ifdef _WIN32
#pragma once
#endif

#include "widget.h"
#include "point.h"

namespace Sexy
{

class Image;

class CursorWidget : public Widget
{
public:
	Image*					mImage;

public:
	CursorWidget();

	virtual void			Draw(Graphics* g);
	void					SetImage(Image* theImage);
	Point					GetHotspot();
	
};

}

#endif // __CURSORWIDGET_H__
