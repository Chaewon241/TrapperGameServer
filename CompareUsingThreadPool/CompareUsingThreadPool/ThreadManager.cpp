#include "ThreadManager.h"


ThreadManager::ThreadManager()
{
	// Main Thread
	InitTLS();
}

ThreadManager::~ThreadManager()
{
	Join();
}

void ThreadManager::Launch(std::function<void(void)> callback)
{
	// 동시다발적으로 해줄까봐 LockGuard를 걸어준다.
	std::lock_guard<std::mutex> guard(m_job_q_);

	worker_threads_.push_back(std::thread([=]()
		{
			InitTLS();
			callback();
			DestroyTLS();
		}));
}

void ThreadManager::Join()
{
	for (std::thread& t : worker_threads_)
	{
		if (t.joinable())
			t.join();
	}
	worker_threads_.clear();
}

void ThreadManager::InitTLS()
{
	//// 1부터 시작하는 전역변수
	//static atomic<uint32> SThreadId = 1;
	//// ID 발급기
	//LThreadId = SThreadId.fetch_add(1);
}

void ThreadManager::DestroyTLS()
{

}