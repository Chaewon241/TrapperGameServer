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
};

