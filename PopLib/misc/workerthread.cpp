#include "workerthread.hpp"

using namespace PopLib;

WorkerThread::WorkerThread(const std::string &name)
	: mThread(nullptr), mMutex(nullptr), mCond(nullptr), mTask(nullptr), mTaskArg(nullptr), mStopped(false),
	  mTaskPending(false), mName(name)
{
	mMutex = SDL_CreateMutex();
	mCond = SDL_CreateCondition();
	mThread = SDL_CreateThread(StaticThreadProc, mName.c_str(), this);
}

WorkerThread::~WorkerThread()
{
	SDL_LockMutex(mMutex);
	mStopped = true;
	SDL_SignalCondition(mCond);
	SDL_UnlockMutex(mMutex);

	SDL_WaitThread(mThread, nullptr);
	SDL_DestroyCondition(mCond);
	SDL_DestroyMutex(mMutex);
}

void WorkerThread::DoTask(void (*task)(void *), void *arg)
{
	SDL_LockMutex(mMutex);
	mTask = task;
	mTaskArg = arg;
	mTaskPending = true;
	SDL_SignalCondition(mCond);
	SDL_UnlockMutex(mMutex);
}

void WorkerThread::WaitForTask()
{
	SDL_LockMutex(mMutex);
	while (mTaskPending)
	{
		SDL_WaitCondition(mCond, mMutex);
	}
	SDL_UnlockMutex(mMutex);
}

bool WorkerThread::IsProcessingTask()
{
	SDL_LockMutex(mMutex);
	bool processing = mTaskPending;
	SDL_UnlockMutex(mMutex);
	return processing;
}

int WorkerThread::StaticThreadProc(void *data)
{
	WorkerThread *self = static_cast<WorkerThread *>(data);
	self->ThreadProc();
	return 0;
}

void WorkerThread::ThreadProc()
{
	while (true)
	{
		SDL_LockMutex(mMutex);
		while (!mTaskPending && !mStopped)
		{
			SDL_WaitCondition(mCond, mMutex);
		}

		if (mStopped)
		{
			SDL_UnlockMutex(mMutex);
			break;
		}

		void (*task)(void *) = mTask;
		void *arg = mTaskArg;
		mTaskPending = false;
		SDL_UnlockMutex(mMutex);

		if (task)
		{
			task(arg);
		}

		SDL_LockMutex(mMutex);
		SDL_SignalCondition(mCond);
		SDL_UnlockMutex(mMutex);
	}
}