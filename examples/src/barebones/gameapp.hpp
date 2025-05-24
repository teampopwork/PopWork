#ifndef __GAMEAPP_HPP__
#define __GAMEAPP_HPP__
#ifdef _WIN32
#pragma once
#endif

#include "PopWork/appbase.hpp"

namespace PopWork
{
class Board;

class GameApp : public AppBase
{
  public:
	GameApp();
	virtual ~GameApp();

	virtual void Init();

	virtual void LoadingThreadProc();

	virtual void LoadingThreadCompleted();

  private:
	Board *mBoard;
};

} // namespace PopWork

#endif // __GAMEAPP_H__