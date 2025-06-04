#ifndef __DIALOGLISTENER_HPP__
#define __DIALOGLISTENER_HPP__
#ifdef _WIN32
#pragma once
#endif

namespace PopLib
{

class DialogListener
{
  public:
	virtual void DialogButtonPress(int theDialogId, int theButtonId)
	{
	}
	virtual void DialogButtonDepress(int theDialogId, int theButtonId)
	{
	}
};

} // namespace PopLib

#endif