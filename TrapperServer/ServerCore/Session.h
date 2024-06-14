#pragma once
#include "IocpObject.h"

#include "IocpEvent.h"
/// <summary>
/// 서버와 클라이언트가 연결, 통신하는 클래스
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
	/* 컨텐츠 코드에서 오버로딩 */
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

