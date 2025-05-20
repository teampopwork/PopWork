#ifndef __DIALOGBUTTON_HPP__
#define __DIALOGBUTTON_HPP__
#ifdef _WIN32
#pragma once
#endif

#include "buttonwidget.hpp"

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