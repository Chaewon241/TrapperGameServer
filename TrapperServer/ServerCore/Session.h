#pragma once
#include "IocpObject.h"

#include "IocpEvent.h"

#include <concurrent_queue.h>
/// <summary>
/// ������ Ŭ���̾�Ʈ�� ����, ����ϴ� Ŭ����
/// </summary>
/// 

using namespace Concurrency;

class Service;

struct PacketHeader
{
	uint16 size;
	uint16 id;
};

class Session : public IocpObject
{
public:
	Session();
	~Session();

public:
	SOCKET& GetSocket() { return m_Socket; }

	shared_ptr<Service>	GetService() { return m_Service.lock(); }
	void SetService(shared_ptr<Service> service) { m_Service = service; }

public:
	virtual void Dispatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) override;
	void Disconnect(const WCHAR* cause);

public:
	virtual bool Send(char* buf, int len);

	virtual bool PostConnect();
	virtual bool PostRecv();
	virtual bool PostSend(SendEvent* sendEvent);
	virtual bool PostDisconnect();

	virtual bool ProcessConnect();
	virtual bool ProcessRecv(int32 numOfBytes);
	virtual bool ProcessSend(SendEvent* sendEvent, int32 numOfBytes);

	virtual void Close(SOCKET& socket);

public:
	char* GetRecvBuffer() { return m_RecvBuffer; }

protected:
	/* ������ �ڵ忡�� �����ε� */
	virtual void OnConnected() { }
	virtual int32 OnRecv(char* buffer, int32 len) { return len; }
	virtual void OnSend(int32 len) { }
	virtual void OnDisconnected() { }

private:
	weak_ptr<Service> m_Service;

	SOCKET m_Socket = INVALID_SOCKET;
	
	concurrent_queue<char*> m_RecvQueue;
	concurrent_queue<char*> m_SendQueue;

	char m_RecvBuffer[1000];

private:
	ConnectEvent		m_ConnectEvent;
	DisconnectEvent		m_DisconnectEvent;
	RecvEvent			m_RecvEvent;
	SendEvent			m_SendEvent;
};

