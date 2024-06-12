#pragma once

#include <functional>

class IocpManager
{
public:
	using Callback = std::function<void(OVERLAPPED_STRUCT*)>;

public:
	IocpManager();
	~IocpManager();

	HANDLE GetHandle() { return m_IocpHandle; }

	bool Register(SOCKET_STRUCT& socket);
	bool Dispatch(uint32 timeoutMs = INFINITE);

	void RegisterHandler(Callback callback) { m_Callback = callback; }

private:
	HANDLE m_IocpHandle;
	Callback m_Callback;
};

