#include "pch.h"
#include "ClientPacketHandler.h"
#include "Room.h"
#include "RoomManager.h"
#include "GameSession.h"

#include "DBConnectionPool.h"
#include "DBBind.h"
#include "DBSynchronizer.h"
#include "GenProcedures.h"
#include "AccountManager.h"
#include "DBManager.h"
#include "GameSessionManager.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warnings(disable: 4996)

PacketHandlerFunc GPacketHandler[UINT16_MAX];

static atomic<int32> playerNum(1);

// 직접 컨텐츠 작업자

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO : Log
	return false;
}

bool Handle_C_CREATE_ACCOUNT(PacketSessionRef& session, Protocol::C_CREATE_ACCOUNT& pkt)
{
	if (GAccountManager == nullptr)
		return false;

	string sid = pkt.playerid();
	string spassword = pkt.password();
	string snickname = pkt.nickname();

	Protocol::S_CREATE_ACCOUNT createPkt;

	if (GAccountManager->Join(sid, spassword, snickname))
	{
		createPkt.set_success(true);
		GConsoleLogger->WriteStdOut(Color::BLUE, L"CreateAccount Success");
	}
	else
	{
		createPkt.set_success(false);
		GConsoleLogger->WriteStdOut(Color::BLUE, L"CreateAccount Failed");
	}

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(createPkt);
	session->Send(sendBuffer);

	return true;
}

bool Handle_C_CHECK_DUPLICATE_ID(PacketSessionRef& session, Protocol::C_CHECK_DUPLICATE_ID& pkt)
{
	if (GAccountManager == nullptr)
		return false;

	Protocol::S_CHECK_DUPLICATE_ID ckPkt;
	bool duplicated = GAccountManager->IsDuplicateId(pkt.playerid());
	ckPkt.set_duplicated(duplicated);

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(ckPkt);
	session->Send(sendBuffer);

	return false;
}

bool Handle_C_LOGIN(PacketSessionRef& session, Protocol::C_LOGIN& pkt)
{
	if (GAccountManager == nullptr)
		return false;

	Protocol::S_LOGIN loginPkt;

	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);

	if(GAccountManager->Login(session, pkt.playerid(), pkt.password()))
	{
		// 플레이어 생성
		PlayerRef player = MakeShared<Player>(GAccountManager->GetAccountInfo(pkt.playerid(), pkt.password()));
		// Session에 Player를 설정해준다.
		gameSession->SetPlayer(player);
		// 로그인한 상태임을 설정해준다.
		gameSession->SetActive(true);
		// 모든 친구들한테 나 로그인 했다고 알리기.
		GAccountManager->BroadcastAllFriends(pkt.playerid(), std::string(player->playerNickname.begin(), player->playerNickname.end()));
		// 이제부터 패킷 만들기.
		loginPkt.set_success(true);
		Protocol::UserInfo* userInfo = loginPkt.mutable_user();
		userInfo->set_id(player->id);
		userInfo->set_playerid(std::string(player->playerId.begin(), player->playerId.end()));
		userInfo->set_nickname(std::string(player->playerNickname.begin(), player->playerNickname.end()));
	}
	else
		loginPkt.set_success(false);

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(loginPkt);
	session->Send(sendBuffer);

	return true;
}

bool Handle_C_SEND_REQUEST(PacketSessionRef& session, Protocol::C_SEND_REQUEST& pkt)
{
	if (GAccountManager == nullptr)
		return false;

	vector<Player>& players = GDBManager->GetPlayerManager().get_all();

	wstring friendId;
	wstring myId = GDBManager->ConvertStringToWstring(pkt.playerid());
	for (auto player : players)
	{
		if (pkt.friendnickname() == string(player.playerNickname.begin(), player.playerNickname.end()))
		{
			friendId = player.playerId;
			break;
		}
	}

	// 친구 요청에 저장
	/* DB에서 UserId가 요청 받은 사람(FriendId)이고 RequestId가 요청한 사람(myId)*/
	SP::AddRequest addRequest(*GDBManager->GetDBConn());
	addRequest.In_PlayerId(friendId.c_str(), static_cast<int32>(friendId.length()));
	addRequest.In_RequestId(myId.c_str(), static_cast<int32>(myId.length()));
	addRequest.Execute();

	Protocol::S_SEND_REQUEST sendRequestPkt;
	sendRequestPkt.set_playerid(pkt.playerid());
	
	// 아이디 중복 확인
	for (auto p : players)
	{
		string player = GDBManager->ConvertWstringToString(p.playerId);

		if (player.compare(pkt.playerid()) == 0)
		{
			sendRequestPkt.set_friendnickname(string(p.playerNickname.begin(), p.playerNickname.end()));
		}
	}

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(sendRequestPkt);

	GSessionManager.Send(friendId, sendBuffer);

	Requests request(friendId, myId);
	GDBManager->GetRequestsManager().add_record(request);

	return false;
}

bool Handle_C_ADD_FRIEND(PacketSessionRef& session, Protocol::C_ADD_FRIEND& pkt)
{
	if (GAccountManager == nullptr)
		return false;

	GAccountManager->AddFriend(pkt.myid(), pkt.friendid(), pkt.approve());

	return true;
}

bool Handle_C_CHECK_FRIEND(PacketSessionRef& session, Protocol::C_CHECK_FRIEND& pkt)
{
	if (GAccountManager == nullptr)
		return false;

	string myId;
	for (auto id : GDBManager->GetPlayerManager().get_all())
	{
		if (string(id.playerNickname.begin(), id.playerNickname.end()) == pkt.mynickname())
		{
			myId = string(id.playerId.begin(), id.playerId.end());
			break;
		}
	}

	vector<Player> friendsArray = GAccountManager->SearchFriendNickname(pkt.requestnickname());

	Protocol::S_CHECK_FRIEND checkFriendPkt;

	for (auto friends : friendsArray)
	{
		// friendnickname이랑 내 닉네임이랑 같을 때
		if (string(friends.playerNickname.begin(), friends.playerNickname.end()) == pkt.mynickname())
			continue;

		int32 checkFriendResult = GAccountManager->CheckFriend(myId, string(friends.playerId.begin(), friends.playerId.end()));

		// 이미 친구거나 친구가 이미 요청을 보냈을 때는 안 보내지게
		if (checkFriendResult == AlreadyFriend || checkFriendResult == FriendAlreadyRequests)
			continue;

		checkFriendPkt.add_success(checkFriendResult);
		checkFriendPkt.add_playernickname(string(friends.playerNickname.begin(), friends.playerNickname.end()));
	}

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(checkFriendPkt);
	session->Send(sendBuffer);

	return true;
}

bool Handle_C_GET_FRIEND(PacketSessionRef& session, Protocol::C_GET_FRIEND& pkt)
{
	if (GAccountManager == nullptr)
		return false;

	vector<Friends>& friends = GDBManager->GetFriendsManager().get_all();
	vector<Player>& players = GDBManager->GetPlayerManager().get_all();
	Protocol::S_GET_FRIEND getFriendPkt;

	// 내 ID
	string myId;
	myId.assign(pkt.playerid().begin(), pkt.playerid().end());

	for (auto f : friends)
	{
		// UserId가 내 아이디인거 찾기
		string findId;
		findId.assign(f.UserId.begin(), f.UserId.end());
		if (findId.compare(myId) == 0)
		{
			// UserId가 내 아이디인 FriendId 가져오기
			string friendId;
			friendId.assign(f.FriendId.begin(), f.FriendId.end());
			for (auto p : players)
			{
				// FriendId를 
				string pId;
				pId.assign(p.playerId.begin(), p.playerId.end());
				if (pId.compare(friendId) == 0)
				{
					bool isActiveAccount = GAccountManager->IsActiveAccount(pId);
					
					auto userInfo = getFriendPkt.add_friends();
					userInfo->set_id(p.id);
					userInfo->set_playerid(pId);
					string pNickname;
					pNickname.assign(p.playerNickname.begin(), p.playerNickname.end());
					userInfo->set_nickname(pNickname);
					userInfo->set_isonline(isActiveAccount);

				}
			}
		}
	}

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(getFriendPkt);
	session->Send(sendBuffer);
	
	return false;
}

bool Handle_C_GET_REQUESTS(PacketSessionRef& session, Protocol::C_GET_REQUESTS& pkt)
{
	if (GAccountManager == nullptr)
		return false;

	vector<Player>& players = GDBManager->GetPlayerManager().get_all();
	vector<Requests>& requests = GDBManager->GetRequestsManager().get_all();

	Protocol::S_GET_REQUESTS getRequestsPkt;

	string myId;
	myId.assign(pkt.playerid().begin(), pkt.playerid().end());

	for (auto r : requests)
	{
		// UserId가 내 아이디인거 찾기
		string findId;
		findId.assign(r.UserId.begin(),  r.UserId.end());
		if (findId.compare(myId) == 0)
		{
			// UserId가 내 아이디인 RequestId 가져오기
			string requestId;
			requestId.assign(r.RequestId.begin(), r.RequestId.end());
			for (auto p : players)
			{
				string pId;
				pId.assign(p.playerId.begin(), p.playerId.end());
				if (pId.compare(requestId) == 0)
				{
					bool isActiveAccount = GAccountManager->IsActiveAccount(pId);

					auto userInfo = getRequestsPkt.add_requests();
					userInfo->set_id(p.id);
					userInfo->set_playerid(pId);
					string pNickname;
					pNickname.assign(p.playerNickname.begin(), p.playerNickname.end());
					userInfo->set_nickname(pNickname);
					userInfo->set_isonline(isActiveAccount);

				}
			}
		}
	}

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(getRequestsPkt);
	session->Send(sendBuffer);

	return true;
}

bool Handle_C_CREATE_ROOM(PacketSessionRef& session, Protocol::C_CREATE_ROOM& pkt)
{
	if (GRoomManager == nullptr)
	{
		GConsoleLogger->WriteStdOut(Color::BLUE, L"No RoomManager");
		return false;
	}

	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);

	Protocol::S_CREATE_ROOM createRoomPkt;
	if (gameSession->GetPlayer() == nullptr)
	{
		PlayerRef tempPlayer = MakeShared<Player>();
		tempPlayer->playerNickname = L"Player" + to_wstring(playerNum++);
		tempPlayer->playerId = L"Player" + to_wstring(playerNum);
		gameSession->SetPlayer(tempPlayer);
	}
	createRoomPkt.set_roomnum(GRoomManager->CreateRoom(pkt.ip(), gameSession->GetPlayer()));
	createRoomPkt.set_success(true);
	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(createRoomPkt);
	session->Send(sendBuffer);
	return true;
}

bool Handle_C_SHOW_ROOM(PacketSessionRef& session, Protocol::C_SHOW_ROOM& pkt)
{
	if (GRoomManager == nullptr)
	{
		GConsoleLogger->WriteStdOut(Color::BLUE, L"No RoomManager");
		return false;
	}

	vector<pair<int32, wstring>> roomList = GRoomManager->SearchRoomList(pkt.roomnum());

	Protocol::S_SHOW_ROOM showRoomPkt;

	if (roomList.size() > 0)
	{
		for (auto room : roomList)
		{
			showRoomPkt.add_roomnums(room.first);
			showRoomPkt.add_hostnickname(string(room.second.begin(), room.second.end()));
		}
	}
	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(showRoomPkt);
	session->Send(sendBuffer);

	return false;
}

bool Handle_C_JOIN_ROOM(PacketSessionRef& session, Protocol::C_JOIN_ROOM& pkt)
{
	if (GRoomManager == nullptr)
	{
		GConsoleLogger->WriteStdOut(Color::BLUE, L"No RoomManager");
		return false;
	}

	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);

	Protocol::S_JOIN_ROOM joinPkt;
	if (gameSession->GetPlayer() == nullptr)
	{
		PlayerRef tempPlayer = MakeShared<Player>();
		tempPlayer->playerNickname = L"Player" + to_wstring(playerNum++);
		tempPlayer->playerId = L"Player" + to_wstring(playerNum);
		gameSession->SetPlayer(tempPlayer);
	}
	string tmpIp = GRoomManager->JoinRoom(pkt.roomnum(), gameSession->GetPlayer());
	
	if (tmpIp.compare("") == 0 || tmpIp.compare("FULL") == 0)
	{
		// Room이 없거나 다 찼을 때
		joinPkt.set_success(false);
		joinPkt.set_roomnum(pkt.roomnum());
	}
	else
	{
		joinPkt.set_success(true);
		joinPkt.set_roomnum(pkt.roomnum());
	}
	joinPkt.set_ip(tmpIp);

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(joinPkt);
	session->Send(sendBuffer);

	return true; 
}

bool Handle_C_LEAVE_ROOM(PacketSessionRef& session, Protocol::C_LEAVE_ROOM& pkt)
{
	if (GRoomManager == nullptr)
	{
		GConsoleLogger->WriteStdOut(Color::BLUE, L"No RoomManager");
		return false;
	}

	GRoomManager->LeaveRoom(pkt.roomnum());

	return true;
}

bool Handle_C_DESTROY_ROOM(PacketSessionRef& session, Protocol::C_DESTROY_ROOM& pkt)
{
	if (GRoomManager == nullptr)
	{
		GConsoleLogger->WriteStdOut(Color::BLUE, L"No RoomManager");
		return false;
	}

	GRoomManager->DestroyRoom(pkt.roomnum());

	return true;
}

bool Handle_C_SEND_INVITATION(PacketSessionRef& session, Protocol::C_SEND_INVITATION& pkt)
{
	if (GAccountManager == nullptr)
		return false;

	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
	wstring myNickname = gameSession->GetPlayer()->playerNickname;

	Protocol::S_SEND_INVITATION invitationPkt;

	vector<Player>& players = GDBManager->GetPlayerManager().get_all();

	wstring pktFriendNickname = wstring(pkt.friendnickname().begin(), pkt.friendnickname().end());
	wstring wFriendId;
	for (auto player : players)
	{
		if (player.playerNickname == pktFriendNickname)
		{
			wFriendId = player.playerId;
			// todo 채원
			// 플레이어가 이미 room에 속해있는지
			if (GRoomManager->IsInRoom(wFriendId))
			{
				invitationPkt.set_success(false);
				
				auto sendBuffer = ClientPacketHandler::MakeSendBuffer(invitationPkt);
				session->Send(sendBuffer);
			}
			else
			{
				invitationPkt.set_success(true);
				invitationPkt.set_mynickname(string(myNickname.begin(), myNickname.end()));
				invitationPkt.set_roomnum(pkt.roomnum());

				auto sendBuffer = ClientPacketHandler::MakeSendBuffer(invitationPkt);

				GSessionManager.Send(wFriendId, sendBuffer);
			}

			break;
		}
	}

	return false;
}

bool Handle_C_ENTER_GAME(PacketSessionRef& session, Protocol::C_ENTER_GAME& pkt)
{
	//GameSessionRef gameSession = static_pointer_cast<GameSession>(session);

	//uint64 index = pkt.playerindex();
	//// TODO : Validation

	//PlayerRef player = gameSession->_players[index]; // READ_ONLY?
	////GRoom.Enter(player); // WRITE_LOCK

	//Protocol::S_ENTER_GAME enterGamePkt;
	//enterGamePkt.set_success(true);
	//auto sendBuffer = ClientPacketHandler::MakeSendBuffer(enterGamePkt);
	//player->ownerSession->Send(sendBuffer);

	return true;
}

bool Handle_C_CHAT(PacketSessionRef& session, Protocol::C_CHAT& pkt)
{
	std::cout << pkt.msg() << endl;

	Protocol::S_CHAT chatPkt;
	chatPkt.set_msg(pkt.msg());
	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(chatPkt);

	return true;
}
