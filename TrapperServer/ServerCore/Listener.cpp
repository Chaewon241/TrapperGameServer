#include "pch.h"
#include "Listener.h"

#include "Session.h"
#include "Service.h"

Listener::~Listener()
{
	if (m_ListenSocket != INVALID_SOCKET)
		::closesocket(m_ListenSocket);
	m_ListenSocket = INVALID_SOCKET;
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
		return false;

	if ((SOCKET_ERROR != ::listen(m_ListenSocket, SOMAXCONN)) == false)
		return false;

	// 클라이언트와 통신할 server세션
	SessionRef accpetSession = make_shared<Session>();
	accpetSession->SetService(service);

	OVERLAPPED_STRUCT* acceptOverlapped = new OVERLAPPED_STRUCT;

	acceptOverlapped->m_EventType = EventType::Accept;
	acceptOverlapped->m_Socket = accpetSession->GetSocket();
	acceptOverlapped->m_IocpObjectType = IocpObjectType::Listener;

	// AcceptEx 초기화
	GUID guidAcceptEx = WSAID_ACCEPTEX;
	DWORD dwBytes;
	int result = WSAIoctl(m_ListenSocket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidAcceptEx, sizeof(guidAcceptEx),
		&m_pAcceptEx, sizeof(m_pAcceptEx), &dwBytes, NULL, NULL);
	if (result == SOCKET_ERROR)
	{
		std::cerr << "WSAIoctl failed with error: " << WSAGetLastError() << std::endl;
		return false;
	}

	DWORD bytesReceived = 0;

	if (false == m_pAcceptEx(m_ListenSocket,
		accpetSession->GetSocket(),
		&acceptOverlapped->m_Buffer[0],
		0, sizeof(SOCKADDR_IN) + 16,
		sizeof(SOCKADDR_IN) + 16,
		&bytesReceived,
		static_cast<LPOVERLAPPED>(acceptOverlapped)))
	{
		const int32 errorCode = ::WSAGetLastError();

		if (errorCode != WSA_IO_PENDING)
		{
			cout << "accept 문제있음" << endl;
		}
	}

	return true;
}
