#ifndef __EDITLISTENER_H__
#define __EDITLISTENER_H__
#ifdef _WIN32
#pragma once
#endif

#include "common.h"
#include "misc/keycodes.h"

namespace PopWork
{

class EditListener
{
  public:
	virtual void EditWidgetText(int theId, const PopWorkString &theString){};

	virtual bool AllowKey(int theId, KeyCode theKey)
	{
		return true;
	}
	virtual bool AllowChar(int theId, PopWorkChar theChar)
	{
		return true;
	}
	virtual bool AllowText(int theId, const PopWorkString &theText)
	{
		return true;
	}
};

} // namespace PopWork

#endif