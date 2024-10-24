#include "pch.h"
#include "ThreadManager.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"

/*------------------
	ThreadManager
-------------------*/

ThreadManager::ThreadManager(size_t poolSize)
{
	// Main Thread
	InitTLS();

	// ������ ũ���� ������ Ǯ ����
	for (size_t i = 0; i < poolSize; ++i)
	{
		_threads.emplace_back(&ThreadManager::WorkerThread, this);
	}
}

ThreadManager::~ThreadManager()
{
	{
		UniqueLock guard(_lock);
		_stop = true;
	}

	// ��� �����忡 �۾� ���� ��ȣ�� ������.
	_condition.notify_all();

	Join();
}

void ThreadManager::Launch(function<void(void)> callback)
{
	// ���ôٹ������� ���ٱ�� LockGuard�� �ɾ��ش�.
	{
		UniqueLock guard(_lock);
		_tasks.push(callback);
	}

	// �۾��� �߰������� �˸���.
	_condition.notify_one();
}

void ThreadManager::Join()
{
	for (thread& t : _threads)
	{
		if (t.joinable())
			t.join();
	}
	_threads.clear();
}

void ThreadManager::WorkerThread()
{
	InitTLS();
	while (true)
	{
		std::function<void(void)> task;

		{
			// �۾��� �����ų� ���� ��ȣ�� �� ������ ����Ѵ�.
			std::unique_lock<std::mutex> lock(_lock);
			_condition.wait(lock, [this] { return !_tasks.empty() || _stop; });

			// ���� �÷��װ� �����Ǿ� �ְ� �۾��� ���� ��� �����带 �����Ѵ�.
			if (_stop && _tasks.empty())
				break;

			// �۾��� ť���� ������.
			task = std::move(_tasks.front());
			_tasks.pop();
		}

		// �۾��� �����Ѵ�.
		task();
		DestroyTLS();
	}
}

void ThreadManager::InitTLS()
{
	// 1���� �����ϴ� ��������
	static Atomic<uint32> SThreadId = 1;
	// ID �߱ޱ�
	LThreadId = SThreadId.fetch_add(1);
}

void ThreadManager::DestroyTLS()
{

}