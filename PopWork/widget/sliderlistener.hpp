#ifndef __SLIDERLISTENER_HPP__
#define __SLIDERLISTENER_HPP__
#ifdef _WIN32
#pragma once
#endif

namespace PopWork
{

class SliderListener
{
  public:
	virtual void SliderVal(int theId, double theVal){};
};

} // namespace PopWork

#endif
