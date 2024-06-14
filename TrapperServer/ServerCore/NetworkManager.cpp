#include "pch.h"
#include "NetworkManager.h"

LPFN_CONNECTEX		NetworkManager::ConnectEx = nullptr;
LPFN_DISCONNECTEX	NetworkManager::DisconnectEx = nullptr;
LPFN_ACCEPTEX		NetworkManager::AcceptEx = nullptr;

void NetworkManager::Init()
{
	WSADATA wsaData;
	ASSERT_CRASH(::WSAStartup(MAKEWORD(2, 2), OUT & wsaData) == 0);

	SOCKET dummySocket = CreateSocket();
	ASSERT_CRASH(BindWindowsFunction(dummySocket, WSAID_CONNECTEX, reinterpret_cast<LPVOID*>(&ConnectEx)));
	ASSERT_CRASH(BindWindowsFunction(dummySocket, WSAID_DISCONNECTEX, reinterpret_cast<LPVOID*>(&DisconnectEx)));
	ASSERT_CRASH(BindWindowsFunction(dummySocket, WSAID_ACCEPTEX, reinterpret_cast<LPVOID*>(&AcceptEx)));
	Close(dummySocket);
}

void NetworkManager::Clear()
{
	::WSACleanup();
}

SOCKET NetworkManager::CreateSocket()
{
	// 비동기 함수를 만들기 위해 WSA_FLAG_OVERLAPPED로 설정해준다.
	return ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
}

bool NetworkManager::BindWindowsFunction(SOCKET socket, GUID guid, LPVOID* fn)
{
	// connect accept disconnect를 런타임에 불러오기 위한 함수.
	// 호환 가능한지 확인
	DWORD bytes = 0;
	return SOCKET_ERROR != ::WSAIoctl(socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guid, sizeof(guid), fn, sizeof(*fn), OUT & bytes, NULL, NULL);
}

bool NetworkManager::BindAnyAddress(SOCKET socket, uint16 port)
{
	// connectex를 위해
	SOCKADDR_IN myAddress;
	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr = ::htonl(INADDR_ANY);
	myAddress.sin_port = ::htons(port);

	return SOCKET_ERROR != ::bind(socket, reinterpret_cast<const SOCKADDR*>(&myAddress), sizeof(myAddress));
}

bool NetworkManager::Bind(SOCKET socket, SOCKADDR_IN address)
{
	return SOCKET_ERROR != ::bind(socket, reinterpret_cast<const SOCKADDR*>(&address), sizeof(address));
}

//bool NetworkManager::Connect(SOCKET socket, SOCKADDR_IN address)
//{
//	sockaddr_in service;
//	service.sin_family = AF_INET;
//	service.sin_addr.s_addr = INADDR_ANY;
//	service.sin_port = htons(0);
//
//	if (bind(socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) 
//	{
//		closesocket(socket);
//		return INVALID_SOCKET;
//	}
//
//	// overlapped 생성
//	OVERLAPPED_STRUCT* connectOverlapped = new OVERLAPPED_STRUCT;
//
//	DWORD numOfBytes = 0;
//	if (false == ConnectEx(socket, reinterpret_cast<SOCKADDR*>(&address), sizeof(address), nullptr, 0, &numOfBytes, connectOverlapped))
//	{
//		int32 errorCode = ::WSAGetLastError();
//		if (errorCode != WSA_IO_PENDING)
//		{
//			return false;
//		}
//	}
//
//	return true;
//}

bool NetworkManager::Listen(SOCKET socket, int32 backlog)
{
	return SOCKET_ERROR != ::listen(socket, backlog);
}

void NetworkManager::Close(SOCKET& socket)
{
	if (socket != INVALID_SOCKET)
		::closesocket(socket);
	socket = INVALID_SOCKET;
}