#pragma once
#include "pch.h"

#define DATA_BUFSIZE 4096

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
};

// 소켓 정보
struct SOCKET_STRUCT
{
	SOCKET_STRUCT()
	{
		m_Socket = INVALID_SOCKET;
		m_Port = 0;
		isAvailable = false;
		m_Type = SocketType::None;
	}

    SOCKET m_Socket;
	wstring m_IP;
	uint16 m_Port;
	bool isAvailable;
	SocketType m_Type;
};
