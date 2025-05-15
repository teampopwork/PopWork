#ifndef __CHECKBOXLISTENER_H__
#define __CHECKBOXLISTENER_H__
#ifdef _WIN32
#pragma once
#endif

namespace PopWork
{

class CheckboxListener
{
public:
	virtual void			CheckboxChecked(int theId, bool checked) {}
};

}

#endif