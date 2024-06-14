#pragma once
#include <functional>

/// <summary>
/// Iocp�� �����ϰ� Iocp�� ����ϰ� Iocp�� ���� overlapped�� ��ȯ �޴� Ŭ����
/// </summary>

class IocpManager
{
public:
	IocpManager();
	~IocpManager();

	HANDLE GetHandle() { return m_IocpHandle; }

	bool Register(SOCKET& socket);
	bool Dispatch(uint32 timeoutMs = INFINITE);

private:
	HANDLE m_IocpHandle;

};

