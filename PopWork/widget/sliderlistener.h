#ifndef __SLIDERLISTENER_H__
#define __SLIDERLISTENER_H__
#ifdef _WIN32
#pragma once
#endif

namespace PopWork
{

class SliderListener
{
public:
	virtual void			SliderVal(int theId, double theVal) {};
};

}

#endif
