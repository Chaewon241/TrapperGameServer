#pragma once

class NetworkManager
{
public:
	LPFN_CONNECTEX		ConnectEx;
	LPFN_DISCONNECTEX	DisconnectEx;
	LPFN_ACCEPTEX		AcceptEx;
public:
	virtual void Init();
	void Clear();

	bool BindWindowsFunction(SOCKET socket, GUID guid, LPVOID* fn);
	SOCKET CreateSocket();

	virtual bool Accept(SOCKET socket, SOCKADDR_IN address);
	virtual bool Bind(SOCKET socket, SOCKADDR_IN address);
	virtual bool Connect(SOCKET socket, SOCKADDR_IN address);
	virtual bool Listen(SOCKET socket, int32 backlog = SOMAXCONN);
	virtual bool BindAnyAddress(SOCKET socket, uint16 port);
	virtual void Close(SOCKET& socket);
};

