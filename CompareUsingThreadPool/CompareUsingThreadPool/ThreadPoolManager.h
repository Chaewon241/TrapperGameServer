#pragma once
#include <thread>
#include <functional>
#include <mutex>
#include <vector>
#include <queue>
#include <atomic>

using namespace std;

class ThreadPoolManager
{
public:
	ThreadPoolManager(size_t poolSize);
	~ThreadPoolManager();

	void EnqueueJob(std::function<void()> job);

	// 스레드를 재사용하기 위해 계속 작업을 기다리도록 만든다.
	void WorkerThread();

private:
	// 총 Worker 쓰레드의 개수.
	size_t num_threads_;
	// Worker 쓰레드를 보관하는 벡터.
	std::vector<std::thread> worker_threads_;
	// 할일들을 보관하는 job 큐.
	std::queue<std::function<void()>> jobs_;
	// 위의 job 큐를 위한 cv 와 m.
	std::condition_variable cv_job_q_;
	std::mutex m_job_q_;

	// 모든 쓰레드 종료
	bool stop_all;
};
