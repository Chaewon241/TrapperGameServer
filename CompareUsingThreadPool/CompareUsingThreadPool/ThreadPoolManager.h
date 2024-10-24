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

	// �����带 �����ϱ� ���� ��� �۾��� ��ٸ����� �����.
	void WorkerThread();

private:
	// �� Worker �������� ����.
	size_t num_threads_;
	// Worker �����带 �����ϴ� ����.
	std::vector<std::thread> worker_threads_;
	// ���ϵ��� �����ϴ� job ť.
	std::queue<std::function<void()>> jobs_;
	// ���� job ť�� ���� cv �� m.
	std::condition_variable cv_job_q_;
	std::mutex m_job_q_;

	// ��� ������ ����
	bool stop_all;
};
