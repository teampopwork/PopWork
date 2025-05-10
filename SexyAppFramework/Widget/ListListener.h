#pragma once

namespace Sexy 
{

class ListListener 
{
public:
	virtual void ListClicked(int theId, int theIdx, int theClickCount) {}
	virtual void ListClosed(int theId) {}
	virtual void ListHiliteChanged(int theId, int theOldIdx, int theNewIdx) {}
};

}

