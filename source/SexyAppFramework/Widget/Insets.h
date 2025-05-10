#pragma once

namespace Sexy
{

class Insets
{
public:
	int						mLeft;
	int						mTop;
	int						mRight;
	int						mBottom;

public:
	Insets();
	Insets(int theLeft, int theTop, int theRight, int theBottom);
	Insets(const Insets& theInsets);			
};

}
