#include "errorhandler.hpp"
#include "appbase.hpp"

using namespace PopWork;

ErrorHandler *PopWork::gErrorHandler = nullptr; // global error handler!!! :P

ErrorHandler::ErrorHandler(AppBase *theApp)
{
	gErrorHandler = this;

	mApp = theApp;
}

ErrorHandler::~ErrorHandler()
{
}