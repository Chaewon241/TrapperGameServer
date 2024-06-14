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
};

