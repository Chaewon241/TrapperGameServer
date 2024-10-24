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
	// ���ôٹ������� ���ٱ�� LockGuard�� �ɾ��ش�.
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
	//// 1���� �����ϴ� ��������
	//static atomic<uint32> SThreadId = 1;
	//// ID �߱ޱ�
	//LThreadId = SThreadId.fetch_add(1);
}

void ThreadManager::DestroyTLS()
{

}