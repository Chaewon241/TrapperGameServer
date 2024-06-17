#include "pch.h"
#include "ThreadManager.h"

thread_local uint32_t LThreadId = 0;

ThreadManager::ThreadManager()
{
	// Main Thread
	InitTLS();
}

ThreadManager::~ThreadManager()
{
	Join();
}

void ThreadManager::Launch(function<void(void)> callback)
{
	LockGuard guard(m_Lock);

	m_Threads.push_back(thread([=]()
		{
			InitTLS();
			callback();
			DestroyTLS();
		}));
}

void ThreadManager::Join()
{
	for (thread& t : m_Threads)
	{
		if (t.joinable())
			t.join();
	}
	m_Threads.clear();
}

void ThreadManager::InitTLS()
{
	static atomic<uint32> SThreadId = 1;
	LThreadId = SThreadId.fetch_add(1);
}

void ThreadManager::DestroyTLS()
{
}