#ifndef __HYPERLINKWIDGET_HPP__
#define __HYPERLINKWIDGET_HPP__
#ifdef _WIN32
#pragma once
#endif

#include "buttonwidget.hpp"

namespace PopWork
{

class HyperlinkWidget : public ButtonWidget
{
  public:
	Color mColor;
	Color mOverColor;
	int mUnderlineSize;
	int mUnderlineOffset;

  public:
	HyperlinkWidget(int theId, ButtonListener *theButtonListener);
	virtual ~HyperlinkWidget(){};

	void Draw(Graphics *g);
	void MouseEnter();
	void MouseLeave();
};

} // namespace PopWork

#endif