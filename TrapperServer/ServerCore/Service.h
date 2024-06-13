#pragma once
#include "IocpManager.h"

#include "Listener.h"

#include <functional>

/// <summary>
/// Server와 Client의 Service를 담당하는 클래스
/// </summary>

enum class ServiceType : uint8
{
	Server,
	Client
};

class Service : public enable_shared_from_this<Service>
{
public:
	Service(SOCKADDR_IN netAddress, IocpManagerRef iocpManager);

	virtual ~Service();
public:
	virtual bool Start() abstract;

	SOCKADDR_IN& GetNetAddress() { return m_NetAddress; }

public:
	IocpManagerRef& GetIocpManager() { return m_pIocpManager; }

protected:
	IocpManagerRef m_pIocpManager;
	SOCKADDR_IN m_NetAddress;
};

/*-----------------
	ClientService
------------------*/

class ClientService : public Service
{
public:
	ClientService(SOCKADDR_IN netAddress, IocpManagerRef iocpManager);
	virtual ~ClientService() {}

	virtual bool Start() override;
};

/*-----------------
	ServerService
------------------*/

class ServerService : public Service
{
public:
	ServerService(SOCKADDR_IN netAddress, IocpManagerRef iocpManager);
	virtual ~ServerService() {}

	virtual bool Start() override;

private:
	ListenerRef m_pListener = nullptr;
};