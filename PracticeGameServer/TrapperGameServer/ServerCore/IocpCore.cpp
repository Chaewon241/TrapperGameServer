#include "pch.h"
#include "IocpCore.h"
#include "IocpEvent.h"

IocpCore::IocpCore()
{
	// ó���� CP ����°�.
	_iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	ASSERT_CRASH(_iocpHandle != INVALID_HANDLE_VALUE);
}

IocpCore::~IocpCore()
{
	::CloseHandle(_iocpHandle);
}

bool IocpCore::Register(IocpObjectRef iocpObject)
{
	// ������ ����, ������ �޾Ƽ� ����� ���Ѽ� ������ ��Ų��.
	// �ٵ� �갡 �� ���Ǹ� �޾Ƽ� ��Ͻ�Ű�°� �ƴϴ�.
	// iocpObject->GetHandle() �갡 ����, ���� ����̴� ��� ���
	return ::CreateIoCompletionPort(iocpObject->GetHandle(), _iocpHandle, /*key*/0, 0);
}

bool IocpCore::Dispatch(uint32 timeoutMs)
{
	// �ϰ��� �ִ��� Ȯ��
	
	// ������ ���� �غ�
	// ���⼭ �����ؾ��� ��!
	// ����ī������ ���� �갡 recv send�� �� ����� �������� �ʰ� �ؾ��Ѵ�.
	DWORD numOfBytes = 0;
	ULONG_PTR key = 0;
	IocpEvent* iocpEvent = nullptr;

	if (::GetQueuedCompletionStatus(_iocpHandle, OUT & numOfBytes, OUT & key, OUT reinterpret_cast<LPOVERLAPPED*>(&iocpEvent), timeoutMs))
	{
		// �������� ��
		// ���δ��� ����ġ
		IocpObjectRef iocpObject = iocpEvent->owner;
		iocpObject->Dispatch(iocpEvent, numOfBytes);
	}
	else
	{
		// �������� �� �����ڵ带 ���� Ȯ���ϱ�.
		// ���� �� 100ms�� ��ٸ���� ���µ� �� ������ �ϰ��� ������
		// WAIT_TIMEOUT���� �ɸ���.
		int32 errCode = ::WSAGetLastError();
		switch (errCode)
		{
		case WAIT_TIMEOUT:
			return false;
		default:
			// TODO : �α� ���
			IocpObjectRef iocpObject = iocpEvent->owner;
			iocpObject->Dispatch(iocpEvent, numOfBytes);
			break;
		}
	}

	return true;
}
