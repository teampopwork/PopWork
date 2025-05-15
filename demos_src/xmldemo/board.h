#ifndef __BOARD_H__
#define __BOARD_H__
#ifdef _WIN32
#pragma once
#endif

#include "PopWork/widget/widget.h"

namespace PopWork
{

class XMLDemoApp;

class Board : public Widget
{

public:

	XMLDemoApp* mApp;

public:

	Board(XMLDemoApp* theApp);
	virtual ~Board();

	void		Update();
	void		Draw(Graphics* g);
};

}

#endif //__BOARD_H__
