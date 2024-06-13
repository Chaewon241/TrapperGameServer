#pragma once

/// <summary>
/// Server�� Listener ����
/// Server�� Accpet�� ����Ѵ�.
/// </summary>

class Listener : public enable_shared_from_this<Listener>
{
public:
	Listener() = default;
	~Listener();

public:
	bool PostAccept(ServerServiceRef service);

private:
	void RegisterAccept();
	void ProcessAccept();

private:
	SOCKET m_ListenSocket;
	ServerServiceRef m_pServerService;
	LPFN_ACCEPTEX m_pAcceptEx = nullptr;
};
