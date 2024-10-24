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

	// 지정된 크기의 스레드 풀 생성
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

	// 모든 스레드에 작업 종료 신호를 보낸다.
	_condition.notify_all();

	Join();
}

void ThreadManager::Launch(function<void(void)> callback)
{
	// 동시다발적으로 해줄까봐 LockGuard를 걸어준다.
	{
		UniqueLock guard(_lock);
		_tasks.push(callback);
	}

	// 작업이 추가됐음을 알린다.
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
			// 작업이 들어오거나 종료 신호가 올 때까지 대기한다.
			std::unique_lock<std::mutex> lock(_lock);
			_condition.wait(lock, [this] { return !_tasks.empty() || _stop; });

			// 종료 플래그가 설정되어 있고 작업이 없는 경우 스레드를 종료한다.
			if (_stop && _tasks.empty())
				break;

			// 작업을 큐에서 꺼낸다.
			task = std::move(_tasks.front());
			_tasks.pop();
		}

		// 작업을 실행한다.
		task();
		DestroyTLS();
	}
}

void ThreadManager::InitTLS()
{
	// 1부터 시작하는 전역변수
	static Atomic<uint32> SThreadId = 1;
	// ID 발급기
	LThreadId = SThreadId.fetch_add(1);
}

void ThreadManager::DestroyTLS()
{

}