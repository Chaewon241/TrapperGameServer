#pragma once
#include "IocpObject.h"

#include "IocpEvent.h"
/// <summary>
/// ������ Ŭ���̾�Ʈ�� ����, ����ϴ� Ŭ����
/// </summary>

class Service;

class Session : public IocpObject
{
public:
	Session();
	~Session();

public:
	SOCKET& GetSocket() { return m_Socket; }

	char* GetRecvBuffer() { return recvBuffer; }

	shared_ptr<Service>	GetService() { return m_Service.lock(); }
	void SetService(shared_ptr<Service> service) { m_Service = service; }

public:
	virtual void Dispatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) override;

public:
	virtual bool PostConnect();
	virtual bool ProcessConnect();
	virtual bool PostRecv();
	virtual bool PostSend();
	virtual void Close(SOCKET& socket);


protected:
	/* ������ �ڵ忡�� �����ε� */
	virtual void OnConnected() { }

private:
	weak_ptr<Service> m_Service;

	SOCKET m_Socket = INVALID_SOCKET;
	
	char recvBuffer[2048];

private:
	ConnectEvent		m_ConnectEvent;
	DisconnectEvent		m_DisconnectEvent;
	RecvEvent			m_RecvEvent;
	SendEvent			m_SendEvent;
};

