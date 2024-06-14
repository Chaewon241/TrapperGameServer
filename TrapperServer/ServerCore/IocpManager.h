#pragma once
#include <functional>

/// <summary>
/// Iocp를 생성하고 Iocp를 등록하고 Iocp를 통해 overlapped를 반환 받는 클래스
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

