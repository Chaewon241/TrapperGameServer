#pragma once
#include "Session.h"

class ServerSession : public Session
{
public:
	ServerSession() = default;
	~ServerSession()
	{
		cout << "~ServerSession" << endl;
	}

	virtual int32 OnRecv(char* buffer, int32 len) override
	{
		// Echo
		cout << "OnRecv Len = " << len << endl;
		Send(buffer, len);
		return len;
	}

	virtual void OnSend(int32 len) override
	{
		cout << "OnSend Len = " << len << endl;
	}
};

