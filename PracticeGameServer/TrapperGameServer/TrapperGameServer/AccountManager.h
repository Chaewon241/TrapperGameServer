#pragma once
#include <unordered_map>

USING_SHARED_PTR(AccountManager);
extern AccountManagerRef GAccountManager;

class DBConnection;

class AccountManager
{
public:
	AccountManager();

public:
	bool Join(string id, string password, string nickname);
	bool Login(string id, string password);

private:
	USE_LOCK;
	unordered_map<string, string> m_ActiveAccount;
	DBConnection* m_DbConn = nullptr;
};

