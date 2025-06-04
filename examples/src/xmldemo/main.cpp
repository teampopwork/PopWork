//////////////////////////////////////////////////////////////////////////
//						main.cpp
//
//	This is the starting point for all new projects. This file's purpose is
//	pretty small, but important. In here we create our application, initialize
//	it, and begin processing all the game code.
//
//	NOTE: You should have read and understood demos 1 and 2 before
//	this, as topics that are already covered will be either not commented
//	or minimally so. In addition, this demo uses just a couple features from the v.1.2
//	release of the framework, so it is beneficial to have read and understood
//	V12Demo as well. Though, if you fully understand demos 1 and 2, you'll probably
//	be fine enough.
//
//	This demo will teach you:
//	* How to read in XML files from disk
//  * How to sift through the XML data and extract the information you need
//////////////////////////////////////////////////////////////////////////

#include "xmldemoapp.hpp"
#ifndef _CONSOLE_ON
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#endif

using namespace PopLib;

int main(int argc, char *argv[])
{
#ifndef _CONSOLE_ON
#ifdef _WIN32
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
#endif
	XMLDemoApp *anApp = new XMLDemoApp();
	anApp->Init();
	anApp->Start();
	delete anApp;

	return 0;
}
