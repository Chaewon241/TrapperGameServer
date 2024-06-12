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

bool IocpManager::Register(SOCKET_STRUCT& socket)
{
	return ::CreateIoCompletionPort(reinterpret_cast<HANDLE>(socket.m_Socket), m_IocpHandle, 0, 0);
}


bool IocpManager::Dispatch(uint32 timeoutMs)
{
	DWORD numOfBytes = 0;
	ULONG_PTR key = 0;
	OVERLAPPED_STRUCT* overlapped = nullptr;

	if (::GetQueuedCompletionStatus(m_IocpHandle, &numOfBytes, &key, reinterpret_cast<LPOVERLAPPED*>(&overlapped), INFINITE))
	{
	}
	
	// ����� �ݹ��Լ� ȣ��
	m_Callback(overlapped);

	// �̰� ���⼭ ������ ���� �����ʿ��� ���ֱ�
	/*switch (overlapped->m_EventType)
	{
	case EventType::Accept:
		numOfBytes = 0;
		break;
	case EventType::Connect:
		break;
	default:
		break;
	}*/

	return true;
}
