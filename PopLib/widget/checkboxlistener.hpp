#ifndef __CHECKBOXLISTENER_HPP__
#define __CHECKBOXLISTENER_HPP__
#ifdef _WIN32
#pragma once
#endif

namespace PopLib
{

class CheckboxListener
{
  public:
	virtual void CheckboxChecked(int theId, bool checked)
	{
	}
};

} // namespace PopLib

#endif