#include "pch.h"
#include "Service.h"

#include "Session.h"
#include "Listener.h"

Service::Service(SOCKADDR_IN netAddress, IocpManagerRef iocpManager)
	: m_NetAddress(netAddress)
	, m_pIocpManager(iocpManager)
{
}

Service::~Service()
{
}

bool Service::Start()
{
	return false;
}


ClientService::ClientService(SOCKADDR_IN netAddress, IocpManagerRef iocpManager)
	: Service(netAddress, iocpManager)
{
}

bool ClientService::Start()
{
	SessionRef session = make_shared<Session>();
	session->SetService(shared_from_this());

	if (session->PostConnect() == false)
		return false;

	return true;
}


ServerService::ServerService(SOCKADDR_IN netAddress, IocpManagerRef iocpManager)
	: Service(netAddress, iocpManager)
{
}


bool ServerService::Start()
{
	m_pListener = make_shared<Listener>();
	if (m_pListener == nullptr)
		return false;

	ServerServiceRef service = static_pointer_cast<ServerService>(shared_from_this());
	if (m_pListener->PostAccept(service) == false)
		return false;

	return true;
}

