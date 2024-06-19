#pragma once

/// <summary>
/// IOCP�� ����� �� �ִ� ObjectŬ����
/// ���ǰ� �����
/// </summary>

class IocpObject : public enable_shared_from_this<IocpObject>
{
public:
	virtual HANDLE GetHandle() abstract;
	virtual void Dispatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) abstract;
};

/// <summary>
/// IOCP�� CP�� ����� ��
/// </summary>

class IocpCore
{
public:
	IocpCore();
	~IocpCore();

	HANDLE		GetHandle() { return _iocpHandle; }

	// �����̳� ������ ������� �� ����� ��Ų��.
	bool		Register(IocpObjectRef iocpObject);
	// worker �����忡 �ϰ��� ���� �θ��� �Ÿ��� �Լ�.
	bool		Dispatch(uint32 timeoutMs = INFINITE);

private:
	HANDLE		_iocpHandle;
};