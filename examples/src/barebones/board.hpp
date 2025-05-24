#ifndef __BOARD_HPP__
#define __BOARD_HPP__
#ifdef _WIN32
#pragma once
#endif

#include "PopWork/widget/widget.hpp"

namespace PopWork
{
class Graphics;

class GameApp;

class Board : public Widget
{
  public:
	Board(GameApp *theApp);

	virtual ~Board();

	virtual void Draw(Graphics *g);

	virtual void Update();

  private:
	GameApp *mApp;
};

} // namespace PopWork

#endif // __BOARD_H__