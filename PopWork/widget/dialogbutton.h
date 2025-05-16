#ifndef __DIALOGBUTTON_H__
#define __DIALOGBUTTON_H__
#ifdef _WIN32
#pragma once
#endif

#include "buttonwidget.h"

namespace PopWork
{

class DialogButton : public ButtonWidget
{
  public:
	Image *mComponentImage;
	int mTranslateX, mTranslateY;
	int mTextOffsetX, mTextOffsetY;

  public:
	DialogButton(Image *theComponentImage, int theId, ButtonListener *theListener);

	virtual void Draw(Graphics *g);
};

} // namespace PopWork

#endif