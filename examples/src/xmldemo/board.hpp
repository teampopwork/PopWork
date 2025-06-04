#ifndef __BOARD_HPP__
#define __BOARD_HPP__
#ifdef _WIN32
#pragma once
#endif

#include "PopLib/widget/widget.hpp"

namespace PopLib
{

class XMLDemoApp;

class Board : public Widget
{

  public:
	XMLDemoApp *mApp;

  public:
	Board(XMLDemoApp *theApp);
	virtual ~Board();

	void Update();
	void Draw(Graphics *g);
};

} // namespace PopLib

#endif //__BOARD_HPP__
