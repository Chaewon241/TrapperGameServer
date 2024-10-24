#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ClientPacketHandler.h"
#include "AccountManager.h"
#include "RoomManager.h"
#include "DBManager.h"

void GameSession::OnConnected()
{
	GSessionManager.Add(static_pointer_cast<GameSession>(shared_from_this()));
}

void GameSession::OnDisconnected()
{
	GSessionManager.Remove(static_pointer_cast<GameSession>(shared_from_this()));
#ifdef LOGIN
	if(_player != nullptr)
		GAccountManager->DelActiveAccount(string(_player->playerId.begin(), _player->playerId.end()));
#endif

	if (_player)
		GRoomManager->PlayerInRoomDisconnected(_player->playerId);


}

void GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketSessionRef session = GetPacketSessionRef();
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

	// TODO : packetId 대역 체크
	ClientPacketHandler::HandlePacket(session, buffer, len);
}

void GameSession::OnSend(int32 len)
{
}

PlayerRef GameSession::GetPlayer()
{
	return _player;
}

void GameSession::SetPlayer(PlayerRef newPlayer)
{
	_player = newPlayer;
}
