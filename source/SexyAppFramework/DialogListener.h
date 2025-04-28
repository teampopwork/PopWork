#pragma once

namespace Sexy
{

class DialogListener
{
public:
	virtual void			DialogButtonPress(int theDialogId, int theButtonId) {}
	virtual void			DialogButtonDepress(int theDialogId, int theButtonId) {}
};

}
