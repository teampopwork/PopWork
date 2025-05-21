#ifndef __DEMO_WIDGET_HPP__
#define __DEMO_WIDGET_HPP__
#ifdef _WIN32
#pragma once
#endif

#include "PopWork/widget/widget.hpp"
#include "PopWork/widget/buttonlistener.hpp"

namespace PopWork
{

class ButtonWidget;

//////////////////////////////////////////////////////////////////////////
//	Noting new in this header. Check the previous demos if this makes
//	no sense to you, as it's all covered there. CHECK OUT THE .CPP FILE
//	THOUGH, there's new stuff there.
//////////////////////////////////////////////////////////////////////////

class DemoWidget : public Widget, public ButtonListener
{

  private:
	ButtonWidget *mMoveButton;
	ButtonWidget *mCloseButton;

  public:
	DemoWidget();
	virtual ~DemoWidget();

	void Draw(Graphics *g);
	void ButtonDepress(int id);
};

} // namespace PopWork

#endif //__DEMO_WIDGET_HPP__
