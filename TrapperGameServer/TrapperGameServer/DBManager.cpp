#include "pch.h"
#include "DBManager.h"
#include "DBConnectionPool.h"
#include "DBBind.h"
#include "XmlParser.h"
#include "DBSynchronizer.h"
#include "GenProcedures.h"
#include "Protocol.pb.h"

DBManagerRef GDBManager;

void DBManager::Initialize()
{
	ASSERT_CRASH(GDBConnectionPool->Connect(1, L"Driver={ODBC Driver 17 for SQL Server};Server=(localdb)\\MSSQLLocalDB;Database=ServerDb;Trusted_Connection=yes;"));

	m_DbConn = GDBConnectionPool->Pop();
	DBSynchronizer dbSync(*m_DbConn);
	dbSync.Synchronize(L"GameDB.xml");

	player.Initialize(m_DbConn);
	friends.Initialize(m_DbConn);
	requests.Initialize(m_DbConn);
}

// Player테이블에 있는 정보들 다 가져오기.
void PlayerManager::Initialize(DBConnection* conn)
{
	SP::GetAllPlayers getPlayers(*conn);

	getPlayers.Execute();

	SQLHSTMT stmt = conn->GetStatement();
	SQLSMALLINT uid;
	SQLWCHAR playerId[50];
	SQLWCHAR playerPassword[50];
	SQLWCHAR playerNickname[50];
	SQLLEN uidLen = 0;
	SQLLEN playerIdLen = 0;
	SQLLEN playerPasswordLen = 0;
	SQLLEN playerNicknameLen = 0;

	SQLBindCol(stmt, 1, SQL_C_SSHORT, &uid, sizeof(uid), &uidLen);
	SQLBindCol(stmt, 2, SQL_C_WCHAR, playerId, sizeof(playerId), &playerIdLen);
	SQLBindCol(stmt, 3, SQL_C_WCHAR, playerPassword, sizeof(playerPassword), &playerPasswordLen);
	SQLBindCol(stmt, 4, SQL_C_WCHAR, playerNickname, sizeof(playerNickname), &playerNicknameLen);

	while (getPlayers.Fetch())
	{
		int32 convertUid = (int32)uid;
		wstring convertId = std::wstring(reinterpret_cast<const wchar_t*>(playerId));
		wstring convertPassword = std::wstring(reinterpret_cast<const wchar_t*>(playerPassword));
		wstring convertNickname = std::wstring(reinterpret_cast<const wchar_t*>(playerNickname));

		Player player(convertUid, convertId, convertPassword, convertNickname);

		add_record(player);
	}
}

// Friends테이블에 있는 정보들 다 가져오기.
void FriendsManager::Initialize(DBConnection* conn)
{
	SP::GetAllFriends getFriends(*conn);

	getFriends.Execute();

	SQLHSTMT stmt = conn->GetStatement();
	SQLWCHAR playerId[50];
	SQLWCHAR friendId[50];
	SQLLEN playerIdLen;
	SQLLEN friendIdLen;

	SQLBindCol(stmt, 1, SQL_C_WCHAR, playerId, sizeof(playerId), &playerIdLen);
	SQLBindCol(stmt, 2, SQL_C_WCHAR, friendId, sizeof(friendId), &friendIdLen);

	while (getFriends.Fetch())
	{
		wstring convertplayerId = std::wstring(reinterpret_cast<const wchar_t*>(playerId));
		wstring convertfriendId = std::wstring(reinterpret_cast<const wchar_t*>(friendId));

		Friends friends(convertplayerId, convertfriendId);

		add_record(friends);
	}
}

void RequestsManager::Initialize(DBConnection* conn)
{
	SP::GetAllRequests getRequests(*conn);

	getRequests.Execute();

	SQLHSTMT stmt = conn->GetStatement();
	SQLWCHAR playerId[50];
	SQLWCHAR requestId[50];
	SQLLEN playerIdLen;
	SQLLEN reuquestIdLen;

	SQLBindCol(stmt, 1, SQL_C_WCHAR, playerId, sizeof(playerId), &playerIdLen);
	SQLBindCol(stmt, 2, SQL_C_WCHAR, requestId, sizeof(requestId), &reuquestIdLen);

	while (getRequests.Fetch())
	{
		wstring convertplayerId = std::wstring(reinterpret_cast<const wchar_t*>(playerId));
		wstring convertrequestId = std::wstring(reinterpret_cast<const wchar_t*>(requestId));

		Requests requests(convertplayerId, convertrequestId);

		add_record(requests);
	}
}
