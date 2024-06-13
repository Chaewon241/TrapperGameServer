#pragma once
#include "pch.h"

#define DATA_BUFSIZE 2048

enum class EventType : uint8
{
	None,
	Connect,
	Disconnect,
	Accept,
	Recv,
	Send
};

enum class SocketType : uint8
{
	None,
	Client,
	Server
};

enum class IocpObjectType : uint8
{
	None,
	Listener,
	Session
};

// I/O 작업을 위한 정보
struct OVERLAPPED_STRUCT : public OVERLAPPED
{
	OVERLAPPED_STRUCT()
	{
		hEvent = 0;
		Internal = 0;
		InternalHigh = 0;
		Offset = 0;
		OffsetHigh = 0;
		ZeroMemory(m_Buffer, sizeof(2048));
		m_DataBuf.buf = m_Buffer;
		m_DataBuf.len = 0;
		m_BytesSEND = 0;
		m_BytesRECV = 0;
		m_EventType = EventType::None;
		m_Socket = INVALID_SOCKET;
		m_IocpObjectType = IocpObjectType::None;
	}
	~OVERLAPPED_STRUCT()
	{
		ZeroMemory(m_Buffer, sizeof(2048));
	}

    char m_Buffer[DATA_BUFSIZE];
    WSABUF m_DataBuf;
    int m_BytesSEND;
    int m_BytesRECV;
    EventType m_EventType;
	SOCKET m_Socket;
	IocpObjectType m_IocpObjectType;
};

// 소켓 정보
struct SOCKET_STRUCT
{
	SOCKET_STRUCT()
	{
		m_Socket = INVALID_SOCKET;
		isAvailable = false;
		m_Type = SocketType::None;
	}

    SOCKET m_Socket;
	bool isAvailable;
	SocketType m_Type;
};
