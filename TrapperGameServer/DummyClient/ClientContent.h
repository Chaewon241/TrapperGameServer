#pragma once

USING_SHARED_PTR(ClientContent);
extern ClientContentRef GClientContent;

class ClientContent
{
public:
	void Start();
	void SetMyId(string id);

	void StartMain();
	void AfterLogin();

private:
	bool _clientRun = true;
	ClientServiceRef service = nullptr;
	string myId = "";
};

