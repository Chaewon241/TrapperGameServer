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
	ThreadManager();
	~ThreadManager();

	// callback �Լ��� �޾��ܰ� ���ÿ� �����带 ��������ش�.
	void	Launch(function<void(void)> callback);
	// ������ ���������� ��ٷ��ִ� join
	void	Join();

	// TLS ������ �ʱ�ȭ�ϰ� �ı������ִ� ThreadManager�� �ٽɺκ�
	static void InitTLS();
	static void DestroyTLS();

private:
	Mutex			_lock;
	vector<thread>	_threads;
};

