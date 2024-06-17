#pragma once
#include "Session.h"



class ClientSession : public Session
{
public:
	ClientSession() = default;
	~ClientSession()
	{
		cout << "~ClientSession" << endl;
	}

	virtual void OnConnected() override
	{
		cout << "Connected To Server" << endl;
		Send(sendBuffer, sizeof(sendBuffer));
	}

	virtual int32 OnRecv(char* buffer, int32 len) override
	{
		cout << "OnRecv Len = " << len << endl;

		this_thread::sleep_for(1s);

		Send(sendBuffer, sizeof(sendBuffer));
		cout << sendBuffer << endl;

		return len;
	}

	virtual void OnSend(int32 len) override
	{
		cout << "OnSend Len = " << len << endl;
	}

	virtual void OnDisconnected() override
	{
		cout << "Disconnected" << endl;
	}

private:
	char sendBuffer[2048] = "Hello World";
};

