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

	// callback �Լ��� �޾��ܰ� ���ÿ� �����带 ��������ش�.
	void	Launch(std::function<void(void)> callback);
	// ������ ���������� ��ٷ��ִ� join
	void	Join();

	// TLS ������ �ʱ�ȭ�ϰ� �ı������ִ� ThreadManager�� �ٽɺκ�
	static void InitTLS();
	static void DestroyTLS();

private:
	// �� Worker �������� ����.
	size_t num_threads_;
	// Worker �����带 �����ϴ� ����.
	std::vector<std::thread> worker_threads_;
	std::mutex m_job_q_;
};
