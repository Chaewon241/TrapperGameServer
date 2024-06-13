#pragma once

/// <summary>
/// ������ Ŭ���̾�Ʈ�� ����, ����ϴ� Ŭ����
/// </summary>

class Service;

class Session
{
public:
	Session();
	~Session();

public:
	SOCKET GetSocket() { return m_Socket; }

	shared_ptr<Service>	GetService() { return m_Service.lock(); }
	void SetService(shared_ptr<Service> service) { m_Service = service; }

public:
	virtual bool PostConnect();
	virtual bool PostRecv(SOCKET socket, SOCKADDR_IN address);
	virtual bool PostSend(SOCKET socket, SOCKADDR_IN address);
	virtual void Close(SOCKET& socket);

private:
	weak_ptr<Service> m_Service;

	SOCKET m_Socket = INVALID_SOCKET;
	OVERLAPPED_STRUCT m_Overlapped = {};
	LPFN_CONNECTEX m_pConnectEx = nullptr;
};

