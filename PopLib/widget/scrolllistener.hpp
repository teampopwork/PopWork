#ifndef __SCROLLLISTENER_HPP__
#define __SCROLLLISTENER_HPP__
#ifdef _WIN32
#pragma once
#endif

namespace PopLib
{

class ScrollListener
{
  public:
	virtual void ScrollPosition(int theId, double thePosition){};
};

} // namespace PopLib

#endif // __SCROLLLISTENER_HPP__