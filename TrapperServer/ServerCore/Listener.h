#pragma once
#include "IocpObject.h"

/// <summary>
/// Server의 Listener 소켓
/// Server의 Accpet를 담당한다.
/// </summary>
/// 

class AcceptEvent;

class Listener : public IocpObject
{
public:
	Listener() = default;
	~Listener();

public:
	virtual void Dispatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) override;

public:
	bool PostAccept(ServerServiceRef service);

private:
	void RegisterAccept();
	void ProcessAccept(AcceptEvent* acceptEvent);

private:
	SOCKET m_ListenSocket;
	ServerServiceRef m_pServerService;
	LPFN_ACCEPTEX m_pAcceptEx = nullptr;
};
