#include "errorhandler.hpp"
#include "appbase.hpp"

using namespace PopLib;

ErrorHandler *PopLib::gErrorHandler = nullptr; // global error handler!!! :P

ErrorHandler::ErrorHandler(AppBase *theApp)
{
	gErrorHandler = this;

	mApp = theApp;
}

ErrorHandler::~ErrorHandler()
{
}