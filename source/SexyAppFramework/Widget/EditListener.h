#pragma once

#include "../Common.h"
#include "../Misc/KeyCodes.h"

namespace Sexy
{

class EditListener
{
public:
	virtual void			EditWidgetText(int theId, const SexyString& theString) {};

	virtual bool			AllowKey(int theId, KeyCode theKey) { return true; }
	virtual bool			AllowChar(int theId, SexyChar theChar) { return true; }
	virtual bool			AllowText(int theId, const SexyString& theText) { return true; }
};

}
