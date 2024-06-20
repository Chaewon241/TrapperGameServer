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
	bool JoinSuccess(string id, string password);
	bool LoginSuccess(string id, string password);

private:
	unordered_map<string, string> m_Account;
	DBConnection* m_DbConn = nullptr;
};

