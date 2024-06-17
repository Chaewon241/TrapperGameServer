#pragma once

#include <thread>

extern thread_local uint32 LThreadId;

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();

	void Launch(function<void(void)> callback);
	void Join();

	static void InitTLS();
	static void DestroyTLS();

private:
	std::mutex m_Lock;
	vector<thread> m_Threads;
};

