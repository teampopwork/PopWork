#ifndef __BOARD_HPP__
#define __BOARD_HPP__
#ifdef _WIN32
#pragma once
#endif

#include "PopWork/widget/widget.hpp"

namespace PopWork
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

} // namespace PopWork

#endif //__BOARD_HPP__
