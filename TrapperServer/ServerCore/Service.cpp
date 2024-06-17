#include "pch.h"
#include "Service.h"

#include "Session.h"
#include "Listener.h"

Service::Service(SOCKADDR_IN netAddress, IocpManagerRef iocpManager, SessionFactory factory)
	: m_NetAddress(netAddress)
	, m_pIocpManager(iocpManager)
	, m_SessionFactory(factory)
{
}

Service::~Service()
{
}

bool Service::Start()
{
	return false;
}

SessionRef Service::CreateSession()
{
	SessionRef session = m_SessionFactory();
	session->SetService(shared_from_this());

	if (m_pIocpManager->Register(session->GetSocket()) == false)
		return nullptr;

	return session;
}

void Service::AddSession(SessionRef session)
{
	m_Sessions.insert(session);
}

void Service::ReleaseSession(SessionRef session)
{
	ASSERT_CRASH(m_Sessions.erase(session) != 0);
}

ClientService::ClientService(SOCKADDR_IN netAddress, IocpManagerRef iocpManager, SessionFactory factory)
	: Service(netAddress, iocpManager, factory)
{
}

bool ClientService::Start()
{
	SessionRef session = CreateSession();
	session->SetService(shared_from_this());
	AddSession(session);

	if (session->PostConnect() == false)
		return false;

	return true;
}


ServerService::ServerService(SOCKADDR_IN netAddress, IocpManagerRef iocpManager, SessionFactory factory)
	: Service(netAddress, iocpManager, factory)
{
}


bool ServerService::Start()
{
	m_pListener = make_shared<Listener>();
	if (m_pListener == nullptr)
		return false;

	if (m_pListener->PostAccept(static_pointer_cast<ServerService>(shared_from_this())) == false)
		return false;
	

	return true;
}

