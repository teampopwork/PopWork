#include "gameapp.hpp"
#ifndef _CONSOLE_ON
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#endif

// The PopWork resides in the "PopWork" namespace. As a convenience,
// you'll see in all the .cpp files "using namespace PopWork" to avoid
// having to prefix everything with PopWork::
using namespace PopWork;

int main(int argc, char *argv[])
{
#ifndef _CONSOLE_ON
#ifdef _WIN32
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
#endif

	// Create and initialize our game application.
	GameApp *anApp = new GameApp();
	anApp->Init();

	// Starts the entire application: sets up the resource loading thread and
	// custom cursor thread, and enters the game loop where the application
	// will remain until it is shut down. You will most likely not need to
	// override this function.
	anApp->Start();

	delete anApp;

	return 0;
}
