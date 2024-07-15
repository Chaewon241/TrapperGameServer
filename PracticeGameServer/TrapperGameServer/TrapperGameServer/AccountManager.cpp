#include "pch.h"
#include "AccountManager.h"
#include "DBConnectionPool.h"
#include "DBBind.h"
#include "XmlParser.h"
#include "DBSynchronizer.h"
#include "GenProcedures.h"

#define _CRT_SECURE_NO_WARNINGS

AccountManagerRef GAccountManager;

AccountManager::AccountManager()
{
	ASSERT_CRASH(GDBConnectionPool->Connect(1, L"Driver={ODBC Driver 17 for SQL Server};Server=(localdb)\\MSSQLLocalDB;Database=ServerDb;Trusted_Connection=yes;"));

	m_DbConn = GDBConnectionPool->Pop();
	DBSynchronizer dbSync(*m_DbConn);
	dbSync.Synchronize(L"GameDB.xml");
}

bool AccountManager::Join(string id, string password, string nickname)
{
	WRITE_LOCK;

	const size_t idLength = 50;
	WCHAR wId[idLength];
	ZeroMemory(wId, sizeof(wId));
	MultiByteToWideChar(CP_UTF8, 0, id.c_str(), -1, wId, idLength);

	SP::CheckPlayerIdExists checkPlayer(*m_DbConn);
	checkPlayer.In_PlayerId(wId);

	checkPlayer.Execute();

	SQLHSTMT stmt = m_DbConn->GetStatement();
	SQLLEN indicator;
	SQLSMALLINT exists = 0;
	SQLRETURN ret = checkPlayer.Fetch();

	if (SQL_SUCCEEDED(ret)) 
	{
		ret = SQLGetData(stmt, 1, SQL_C_SSHORT, &exists, 0, &indicator);
		if (SQL_SUCCEEDED(ret)) 
		{
			if (exists) 
			{
				return false;
			}
		}
	}

	const size_t nicknameLength = 50;
	WCHAR wNickname[nicknameLength];
	ZeroMemory(wNickname, sizeof(wNickname));
	MultiByteToWideChar(CP_UTF8, 0, nickname.c_str(), -1, wNickname, nicknameLength);

	const size_t passwordLength = 50;
	WCHAR wPassword[passwordLength];
	ZeroMemory(wPassword, sizeof(wPassword));

	MultiByteToWideChar(CP_UTF8, 0, password.c_str(), -1, wPassword, passwordLength);

	SP::InsertPlayer insertPlayer(*m_DbConn);
	insertPlayer.In_PlayerId(wId);
	insertPlayer.In_PlayerPassword(wPassword);
	insertPlayer.In_PlayerNickname(wNickname);

	insertPlayer.Execute();

	return true;
}

bool AccountManager::Login(string id, string password)
{
	SP::LoginPlayer loginPlayer(*m_DbConn);

	const size_t idLength = 50;
	WCHAR wId[idLength];
	ZeroMemory(wId, sizeof(wId));
	MultiByteToWideChar(CP_UTF8, 0, id.c_str(), -1, wId, idLength);
	loginPlayer.In_PlayerId(wId);

	const size_t passwordLength = 50;
	WCHAR wPassword[passwordLength];
	ZeroMemory(wPassword, sizeof(wPassword));
	MultiByteToWideChar(CP_UTF8, 0, password.c_str(), -1, wPassword, passwordLength);
	loginPlayer.In_PlayerPassword(wPassword);

	loginPlayer.Execute();

	SQLHSTMT stmt = m_DbConn->GetStatement();
	SQLLEN indicator;
	SQLSMALLINT exists = 0;
	SQLRETURN ret = loginPlayer.Fetch();

	if (SQL_SUCCEEDED(ret))
	{
		ret = SQLGetData(stmt, 1, SQL_C_SSHORT, &exists, 0, &indicator);
		if (SQL_SUCCEEDED(ret))
		{
			if (exists == 0)
			{
				return false;
			}
			else if (exists == 1)
			{
				return true;
			}
			else if (exists == 2)
			{
				return false;
			}
		}
	}

	return true;
}
