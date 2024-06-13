#include "pch.h"
#include "Session.h"

#include "Service.h"

Session::Session()
{
	m_Socket= ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
}

Session::~Session()
{
	if (m_Socket != INVALID_SOCKET)
		::closesocket(m_Socket);
	m_Socket = INVALID_SOCKET;
}

bool Session::PostConnect()
{
	auto address = GetService()->GetNetAddress();

	if (::bind(m_Socket, (SOCKADDR*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		closesocket(m_Socket);
		return INVALID_SOCKET;
	}

	// overlapped »ý¼º
	OVERLAPPED_STRUCT* connectOverlapped = new OVERLAPPED_STRUCT;

	GUID guidAcceptEx = WSAID_CONNECTEX;

	DWORD dwBytes;
	int result = WSAIoctl(m_Socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidAcceptEx, sizeof(guidAcceptEx),
		&m_pConnectEx, sizeof(m_pConnectEx), &dwBytes, NULL, NULL);

	DWORD numOfBytes = 0;
	if (false == m_pConnectEx(m_Socket, reinterpret_cast<SOCKADDR*>(&address), sizeof(address), nullptr, 0, &numOfBytes, connectOverlapped))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			return false;
		}
	}

	return true;
}

bool Session::PostRecv(SOCKET socket, SOCKADDR_IN address)
{
	return false;
}

bool Session::PostSend(SOCKET socket, SOCKADDR_IN address)
{
	return false;
}

void Session::Close(SOCKET& socket)
{
}

