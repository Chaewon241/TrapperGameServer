#include "pch.h"
#include "Session.h"

#include "Service.h"
#include "NetworkManager.h"

Session::Session()
{
	m_Socket = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
}

Session::~Session()
{
	if (m_Socket != INVALID_SOCKET)
		::closesocket(m_Socket);
	m_Socket = INVALID_SOCKET;
}



void Session::Dispatch(IocpEvent* iocpEvent, int32 numOfBytes)
{
	switch (iocpEvent->eventType)
	{
	case EventType::Connect:
		ProcessConnect();
		break;
	case EventType::Send:
		break;
	case EventType::Recv:
		break;
	default:
		break;
	}
}

bool Session::PostConnect()
{
	auto address = GetService()->GetNetAddress();

	SOCKADDR_IN myAddress;
	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr = ::htonl(INADDR_ANY);
	myAddress.sin_port = ::htons(0);

	if (::bind(m_Socket, (SOCKADDR*)&myAddress, sizeof(myAddress)) == SOCKET_ERROR)
	{
		closesocket(m_Socket);
		return INVALID_SOCKET;
	}

	m_ConnectEvent.Init();
	m_ConnectEvent.owner = shared_from_this();

	DWORD numOfBytes = 0;
	if (false == NetworkManager::ConnectEx(m_Socket, reinterpret_cast<SOCKADDR*>(&address), sizeof(address), nullptr, 0, &numOfBytes, &m_ConnectEvent))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			return false;
		}
	}

	return true;
}

bool Session::ProcessConnect()
{
	m_ConnectEvent.owner = nullptr; // RELEASE_REF

	// 세션 등록
	GetService()->AddSession(static_pointer_cast<Session>(shared_from_this()));

	// 컨텐츠 코드에서 오버로딩
	OnConnected();

	// 수신 등록
	PostRecv();
	return true;
}

bool Session::PostRecv()
{
	cout << "recv 입력해놓기~" << endl;
	return false;
}

bool Session::PostSend()
{
	return false;
}

void Session::Close(SOCKET& socket)
{
}

