#include "pch.h"
#include "Session.h"

#include "Service.h"
#include "NetworkManager.h"
#include "Protocol.h"

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
		ProcessSend(static_cast<SendEvent*>(iocpEvent), numOfBytes);
		break;
	case EventType::Recv:
		ProcessRecv(numOfBytes);
		break;
	default:
		break;
	}
}

void Session::Disconnect(const WCHAR* cause)
{
	wcout << "Disconnect : " << cause << endl;

	OnDisconnected(); // 컨텐츠 코드에서 재정의
	GetService()->ReleaseSession(static_pointer_cast<Session>(shared_from_this()));

	PostDisconnect();
}

bool Session::Send(char* buf, int len)
{
	SendEvent* sendEvent = new SendEvent;
	sendEvent->owner = shared_from_this();
	sendEvent->m_SendBuffers.resize(len);
	::memcpy(sendEvent->m_SendBuffers.data(), buf, len);

	PostSend(sendEvent);

	return false;
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

bool Session::ProcessRecv(int32 numOfBytes)
{
	m_RecvEvent.owner = nullptr;

	if (numOfBytes == 0)
	{
		Disconnect(L"Recv 0");
		return false;
	}

	// 컨텐츠 코드에서 재정의
	OnRecv(m_RecvBuffer, numOfBytes);

	// 수신 등록
	PostRecv();

	return false;
}

bool Session::ProcessSend(SendEvent* sendEvent, int32 numOfBytes)
{
	sendEvent->owner = nullptr; // RELEASE_REF
	delete sendEvent;

	if (numOfBytes == 0)
	{
		Disconnect(L"Send 0");
		return false;
	}

	// 컨텐츠 코드에서 재정의
	OnSend(numOfBytes);

	return false;
}


bool Session::PostRecv()
{
	cout << "recv 입력해놓기~" << endl;
	m_RecvEvent.Init();
	m_RecvEvent.owner = shared_from_this(); // ADD_REF

	DWORD numOfBytes = 0;
	DWORD flags = 0;

	WSABUF buf;
	buf.buf = m_RecvEvent.GetRecvBuf();
	buf.len = m_RecvEvent.GetBufLen();

	if (SOCKET_ERROR == ::WSARecv(m_Socket,
		&buf, 1,
		&numOfBytes, 
		&flags, 
		&m_RecvEvent, 
		nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			m_RecvEvent.owner = nullptr;
		}
	}

	return false;
}

bool Session::PostSend(SendEvent* sendEvent)
{
	m_SendEvent.Init();
	m_SendEvent.owner = shared_from_this(); // ADD_REF

	WSABUF wsaBuf;
	wsaBuf.buf = (char*)sendEvent->m_SendBuffers.data();
	wsaBuf.len = (ULONG)sendEvent->m_SendBuffers.size();

	DWORD numOfBytes = 0;
	if (SOCKET_ERROR == ::WSASend(m_Socket, &wsaBuf, 1, OUT & numOfBytes, 0, sendEvent, nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			sendEvent->owner = nullptr; // RELEASE_REF
			delete sendEvent;
		}
	}

	return false;
}

bool Session::PostDisconnect()
{
	m_DisconnectEvent.Init();
	m_DisconnectEvent.owner = shared_from_this(); // ADD_REF

	if (false == NetworkManager::DisconnectEx(m_Socket, &m_DisconnectEvent, TF_REUSE_SOCKET, 0))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			m_DisconnectEvent.owner = nullptr; // RELEASE_REF
			return false;
		}
	}

	return true;
}

void Session::Close(SOCKET& socket)
{
}

