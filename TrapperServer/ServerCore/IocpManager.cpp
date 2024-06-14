#include "pch.h"
#include "IocpManager.h"

#include "IocpEvent.h"
#include "IocpObject.h"

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
	IocpEvent* iocpEvent = nullptr;

	if (::GetQueuedCompletionStatus(m_IocpHandle, &numOfBytes, &key, reinterpret_cast<LPOVERLAPPED*>(&iocpEvent), INFINITE))
	{
		IocpObjectRef iocpObject = iocpEvent->owner;
		iocpObject->Dispatch(iocpEvent, numOfBytes);
	}
	else
	{
		int error = GetLastError();
		if (error == WAIT_TIMEOUT)
		{
			cout << "Timeout occurred, no I/O operation was completed." << endl;
		}
		else
		{
			cout << "GetQueuedCompletionStatus failed with error: " << error << endl;
		}
	}

	return true;
}
