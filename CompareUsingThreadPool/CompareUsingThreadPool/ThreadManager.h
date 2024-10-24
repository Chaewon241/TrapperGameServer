#pragma once
#include <thread>
#include <functional>
#include <mutex>
#include <vector>
#include <queue>
#include <atomic>

using namespace std;

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();

	// callback 함수를 받아줌과 동시에 쓰레드를 실행시켜준다.
	void	Launch(std::function<void(void)> callback);
	// 쓰레드 끝날때까지 기다려주는 join
	void	Join();

	// TLS 영역을 초기화하고 파괴시켜주는 ThreadManager의 핵심부분
	static void InitTLS();
	static void DestroyTLS();

private:
	// 총 Worker 쓰레드의 개수.
	size_t num_threads_;
	// Worker 쓰레드를 보관하는 벡터.
	std::vector<std::thread> worker_threads_;
	std::mutex m_job_q_;
};
