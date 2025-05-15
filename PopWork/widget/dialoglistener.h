#ifndef __DIALOGLISTENER_H__
#define __DIALOGLISTENER_H__
#ifdef _WIN32
#pragma once
#endif

namespace PopWork
{

class DialogListener
{
public:
	virtual void			DialogButtonPress(int theDialogId, int theButtonId) {}
	virtual void			DialogButtonDepress(int theDialogId, int theButtonId) {}
};

}

#endif