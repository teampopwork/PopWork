#include "httptransfer.hpp"
#include "appbase.hpp"

using namespace PopWork;

static int gCurTransferId = 1;

HTTPTransfer::HTTPTransfer()
{
	mTransferId = gCurTransferId++;
	mResult = RESULT_NOT_STARTED;
	mContentLength = 0;
	mThreadRunning = false;
}

HTTPTransfer::~HTTPTransfer()
{
}

std::string HTTPTransfer::GetAbsURL(const std::string &theBaseURL, const std::string &theRelURL)
{
	return "";
}

void HTTPTransfer::Fail(int theResult)
{
}

bool HTTPTransfer::SocketWait(bool checkRead, bool checkWrite)
{
	// Return true on abort
	return true;
}

void HTTPTransfer::GetThreadProc()
{
}

void HTTPTransfer::GetThreadProcStub(void *theArg)
{
}

void HTTPTransfer::PrepareTransfer(const std::string &theURL)
{
}

void HTTPTransfer::StartTransfer()
{
}

void HTTPTransfer::GetHelper(const std::string &theURL)
{
}

void HTTPTransfer::PostHelper(const std::string &theURL, const std::string &theParams)
{
}

void HTTPTransfer::Get(const std::string &theURL)
{
}

void HTTPTransfer::Post(const std::string &theURL, const std::string &theParams)
{
}

void HTTPTransfer::Get(const std::string &theBaseURL, const std::string &theRelURL)
{
}

void HTTPTransfer::Post(const std::string &theBaseURL, const std::string &theRelURL, const std::string &theParams)
{
}

void HTTPTransfer::SendRequestString(const std::string &theHost, const std::string &theSendString)
{
}

void HTTPTransfer::Abort()
{
}

void HTTPTransfer::Reset()
{
}

static int aLastThreadId = 0;

void HTTPTransfer::UpdateStatus()
{
}

void HTTPTransfer::WaitFor()
{
}

int HTTPTransfer::GetResultCode()
{
	return 0;
}

std::string HTTPTransfer::GetContent()
{
	return "";
}
