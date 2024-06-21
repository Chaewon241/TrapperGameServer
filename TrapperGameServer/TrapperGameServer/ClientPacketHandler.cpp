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

// 流立 牧刨明 累诀磊

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

	auto player = createPkt.add_players();
	player->set_id(sid);
	player->set_pwd(spassword);

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(createPkt);
	session->Send(sendBuffer);

	return true;
}

bool Handle_C_LOGIN(PacketSessionRef& session, Protocol::C_LOGIN& pkt)
{
	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);

	// TODO : Validation 眉农

	Protocol::S_LOGIN loginPkt;

	if(GAccountManager->LoginSuccess(pkt.id(), pkt.password()))
		loginPkt.set_success(true);
	else
		loginPkt.set_success(false);

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
