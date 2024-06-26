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

	SP::GetPlayer getPlayer(*m_DbConn);

	WCHAR wid[100];
	WCHAR wpassword[100];

	getPlayer.Out_PlayerId(OUT wid);
	getPlayer.Out_PlayerPassword(OUT wpassword);

	getPlayer.Execute();

	while (getPlayer.Fetch())
	{
		int idLength = WideCharToMultiByte(CP_UTF8, 0, wid, -1, nullptr, 0, NULL, NULL);
		int passwordLength = WideCharToMultiByte(CP_UTF8, 0, wpassword, -1, nullptr, 0, NULL, NULL);

		string id(idLength-1, '\0');
		WideCharToMultiByte(CP_UTF8, 0, wid, -1, &id[0], idLength, NULL, NULL);
		string password(passwordLength-1, '\0');
		WideCharToMultiByte(CP_UTF8, 0, wpassword, -1, &password[0], passwordLength, NULL, NULL);

		m_Account[id] = password;
	}
}

bool AccountManager::Join(string id, string password)
{
	WRITE_LOCK;
	if (m_Account.find(id) != m_Account.end())
		return false;

	const size_t idLength = 50;
	WCHAR wId[idLength];
	ZeroMemory(wId, sizeof(wId));

	const size_t passwordLength = 50;
	WCHAR wPassword[passwordLength];
	ZeroMemory(wPassword, sizeof(wPassword));

	MultiByteToWideChar(CP_UTF8, 0, id.c_str(), -1, wId, idLength);
	MultiByteToWideChar(CP_UTF8, 0, password.c_str(), -1, wPassword, passwordLength);

	SP::InsertPlayer insertPlayer(*m_DbConn);
	insertPlayer.In_PlayerId(wId);
	insertPlayer.In_PlayerPassword(wPassword);

	insertPlayer.Execute();

	m_Account[id] = password;

	return true;
}

bool AccountManager::Login(string id, string password)
{
	if (m_Account.find(id) == m_Account.end())
		return false;

	if (m_Account[id] != password)
		return false;

	return true;
}
