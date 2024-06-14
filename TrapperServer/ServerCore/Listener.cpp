#include "pch.h"
#include "Listener.h"

#include "Session.h"
#include "Service.h"
#include "NetworkManager.h"
#include "IocpEvent.h"

Listener::~Listener()
{
	if (m_ListenSocket != INVALID_SOCKET)
		::closesocket(m_ListenSocket);
	m_ListenSocket = INVALID_SOCKET;
}

void Listener::Dispatch(IocpEvent* iocpEvent, int32 numOfBytes)
{
	AcceptEvent* acceptEvent = static_cast<AcceptEvent*>(iocpEvent);
	ProcessAccept(acceptEvent);
}

bool Listener::PostAccept(ServerServiceRef service)
{
	m_pServerService = service;
	if (m_pServerService == nullptr)
		return false;

	m_ListenSocket = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (m_ListenSocket == INVALID_SOCKET)
		return false;

	// listensocket을 iocp에 등록시킨다.
	if (m_pServerService->GetIocpManager()->Register(m_ListenSocket) == false)
		return false;

	if ((SOCKET_ERROR != ::bind(m_ListenSocket,
		reinterpret_cast<const SOCKADDR*>(&m_pServerService->GetNetAddress()), sizeof(SOCKADDR_IN))) == false)
	{
		cout << GetLastError() << endl;
		return false;
	}

	if ((SOCKET_ERROR != ::listen(m_ListenSocket, SOMAXCONN)) == false)
		return false;

	RegisterAccept();
	
	return true;
}

void Listener::RegisterAccept()
{
	// 클라이언트와 통신할 server세션
	SessionRef acceptSession = m_pServerService->CreateSession();
	m_pServerService->AddSession(acceptSession);

	AcceptEvent* acceptEvent = new AcceptEvent;
	acceptEvent->Init();
	acceptEvent->session = acceptSession;
	acceptEvent->owner = shared_from_this();

	DWORD bytesReceived = 0;
	if (false == NetworkManager::AcceptEx(m_ListenSocket,
		acceptSession->GetSocket(),
		acceptSession->GetRecvBuffer(),
		0, sizeof(SOCKADDR_IN) + 16,
		sizeof(SOCKADDR_IN) + 16,
		&bytesReceived,
		static_cast<LPOVERLAPPED>(acceptEvent)))
	{
		const int32 errorCode = ::WSAGetLastError();

		if (errorCode != WSA_IO_PENDING)
		{
			RegisterAccept();
		}
	}
}

void Listener::ProcessAccept(AcceptEvent* acceptEvent)
{
	SessionRef session = acceptEvent->session;

	cout << "Client Connected!" << endl;
	session->ProcessConnect();
	RegisterAccept();
	delete acceptEvent;
}
