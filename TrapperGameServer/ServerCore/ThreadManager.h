#pragma once

#include <thread>
// std::function�� ����ϱ� ����.
#include <functional>

/// <summary>
/// 
/// </summary>

class ThreadManager
{
public:
	ThreadManager(size_t poolSize);
	~ThreadManager();

	// callback �Լ��� �޾��ܰ� ���ÿ� �����带 ��������ش�.
	void	Launch(function<void(void)> callback);
	// ������ ���������� ��ٷ��ִ� join
	void	Join();
	// �����带 �����ϱ� ���� ��� �۾��� ��ٸ����� �����.
	void WorkerThread();

	// TLS ������ �ʱ�ȭ�ϰ� �ı������ִ� ThreadManager�� �ٽɺκ�
	static void InitTLS();
	static void DestroyTLS();

private:
	Mutex			_lock;
	CondVar			_condition;
	std::queue<std::function<void(void)>> _tasks; // �۾� ť

	vector<thread>	_threads;
	bool _stop;  // ������ Ǯ ���� �÷���
};

