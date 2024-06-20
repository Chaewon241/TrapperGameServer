#include "pch.h"
#include "ClientPacketHandler.h"
#include "Player.h"
#include "Room.h"
#include "GameSession.h"

#include "DBConnectionPool.h"
#include "DBBind.h"
#include "DBSynchronizer.h"
#include "GenProcedures.h"
#include "AccountManager.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warnings(disable: 4996)

PacketHandlerFunc GPacketHandler[UINT16_MAX];

// 직접 컨텐츠 작업자

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO : Log
	return false;
}

bool Handle_C_CREATE_ACCOUNT(PacketSessionRef& session, Protocol::C_CREATE_ACCOUNT& pkt)
{
	string sid = pkt.id();
	string spassword = pkt.password();

	Protocol::S_CREATE_ACCOUNT createPkt;

	if (GAccountManager->JoinSuccess(sid, spassword))
		createPkt.set_success(true);
	else
		createPkt.set_success(false);

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(createPkt);
	session->Send(sendBuffer);

	return false;
}

bool Handle_C_LOGIN(PacketSessionRef& session, Protocol::C_LOGIN& pkt)
{
	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);

	// TODO : Validation 체크

	Protocol::S_LOGIN loginPkt;

	ASSERT_CRASH(GDBConnectionPool->Connect(1, L"Driver={ODBC Driver 17 for SQL Server};Server=(localdb)\\MSSQLLocalDB;Database=ServerDb;Trusted_Connection=yes;"));

	DBConnection* dbConn = GDBConnectionPool->Pop();
	DBSynchronizer dbSync(*dbConn);
	dbSync.Synchronize(L"GameDB.xml");


	loginPkt.set_success(true);

	// DB에서 플레이 정보를 긁어온다
	// GameSession에 플레이 정보를 저장 (메모리)

	// ID 발급 (DB 아이디가 아니고, 인게임 아이디)
	//static Atomic<uint64> idGenerator = 1;

	//{
	//	auto player = loginPkt.add_players();
	//	player->set_name(u8"DB에서긁어온이름1");
	//	player->set_playertype(Protocol::PLAYER_TYPE_KNIGHT);

	//	PlayerRef playerRef = MakeShared<Player>();
	//	playerRef->playerId = idGenerator++;
	//	playerRef->name = player->name();
	//	playerRef->type = player->playertype();
	//	playerRef->ownerSession = gameSession;
	//	
	//	gameSession->_players.push_back(playerRef);
	//}

	//{
	//	auto player = loginPkt.add_players();
	//	player->set_name(u8"DB에서긁어온이름2");
	//	player->set_playertype(Protocol::PLAYER_TYPE_MAGE);

	//	PlayerRef playerRef = MakeShared<Player>();
	//	playerRef->playerId = idGenerator++;
	//	playerRef->name = player->name();
	//	playerRef->type = player->playertype();
	//	playerRef->ownerSession = gameSession;

	//	gameSession->_players.push_back(playerRef);
	//}

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(loginPkt);
	session->Send(sendBuffer);

	return true;
}

bool Handle_C_ENTER_GAME(PacketSessionRef& session, Protocol::C_ENTER_GAME& pkt)
{
	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);

	uint64 index = pkt.playerindex();
	// TODO : Validation

	PlayerRef player = gameSession->_players[index]; // READ_ONLY?
	GRoom.Enter(player); // WRITE_LOCK

	Protocol::S_ENTER_GAME enterGamePkt;
	enterGamePkt.set_success(true);
	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(enterGamePkt);
	player->ownerSession->Send(sendBuffer);

	return true;
}

bool Handle_C_CHAT(PacketSessionRef& session, Protocol::C_CHAT& pkt)
{
	std::cout << pkt.msg() << endl;

	Protocol::S_CHAT chatPkt;
	chatPkt.set_msg(pkt.msg());
	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(chatPkt);

	GRoom.Broadcast(sendBuffer); // WRITE_LOCK

	return true;
}
