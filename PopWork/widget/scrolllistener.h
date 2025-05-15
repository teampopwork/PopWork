#ifndef __SCROLLLISTENER_H__
#define __SCROLLLISTENER_H__
#ifdef _WIN32
#pragma once
#endif

namespace PopWork 
{

class ScrollListener 
{
public:
	virtual void ScrollPosition(int theId, double thePosition) {};
};

}

#endif // __SCROLLLISTENER_H__