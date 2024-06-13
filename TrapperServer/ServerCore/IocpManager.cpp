#include "pch.h"
#include "IocpManager.h"

IocpManager::IocpManager()
{
	m_IocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	ASSERT_CRASH(m_IocpHandle != INVALID_HANDLE_VALUE);
}

IocpManager::~IocpManager()
{
	::CloseHandle(m_IocpHandle);
}

bool IocpManager::Register(SOCKET& socket)
{
	return ::CreateIoCompletionPort(reinterpret_cast<HANDLE>(socket), m_IocpHandle, 0, 0);
}


bool IocpManager::Dispatch(uint32 timeoutMs)
{
	DWORD numOfBytes = 0;
	ULONG_PTR key = 0;
	OVERLAPPED_STRUCT* overlapped = nullptr;

	if (::GetQueuedCompletionStatus(m_IocpHandle, &numOfBytes, &key, reinterpret_cast<LPOVERLAPPED*>(&overlapped), INFINITE))
	{
		if (overlapped->m_IocpObjectType == IocpObjectType::Listener)
		{
			cout << "accept" << endl;
		}
		else
		{
			cout << "connect" << endl;
		}
	}

	int error = GetLastError();
	if (error == WAIT_TIMEOUT)
	{
		cout << "Timeout occurred, no I/O operation was completed." << endl;
	}
	else
	{
		cout << "GetQueuedCompletionStatus failed with error: " << error << endl;
	}


	return true;
}
