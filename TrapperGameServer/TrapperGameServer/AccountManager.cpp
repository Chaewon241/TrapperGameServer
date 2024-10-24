#include "pch.h"
#include "AccountManager.h"
#include "DBConnectionPool.h"
#include "DBBind.h"
#include "XmlParser.h"
#include "DBSynchronizer.h"
#include "GenProcedures.h"
#include "GameSession.h"
#include "DBManager.h"
#include "GameSessionManager.h"
#include "Protocol.pb.h"
#include "ClientPacketHandler.h"
#include "../ServerCore/Types.h"

#include <algorithm>

#define _CRT_SECURE_NO_WARNINGS

AccountManagerRef GAccountManager = nullptr;

AccountManager::AccountManager()
{
}

bool AccountManager::Join(string id, string password, string nickname)
{
	WRITE_LOCK;

	wstring wId = GDBManager->ConvertStringToWstring(id);
	wstring wNickname = GDBManager->ConvertStringToWstring(nickname);
	wstring wPassword = GDBManager->ConvertStringToWstring(password);

	SP::InsertPlayer insertPlayer(*GDBManager->GetDBConn());
	insertPlayer.In_PlayerId(wId.c_str(), static_cast<int32>(wId.length()));
	insertPlayer.In_PlayerPassword(wPassword.c_str(), static_cast<int32>(wPassword.length()));
	insertPlayer.In_PlayerNickname(wNickname.c_str(), static_cast<int32>(wNickname.length()));

	if (insertPlayer.Execute())
	{
		int insertedId;
		if (insertPlayer.Fetch())
		{
			SQLGetData(GDBManager->GetDBConn()->GetStatement(), 1, SQL_C_SLONG, &insertedId, 0, nullptr);

			Player player(insertedId, wId, wPassword, wNickname);

			GDBManager->GetPlayerManager().add_record(player);
		}
	}

	return true;
}

bool AccountManager::Login(PacketSessionRef session, string id, string password)
{
	WRITE_LOCK; 

	// 이미 로그인된 ID일 때
	if (IsActiveAccount(id))
	{
		return false;
	}

	vector<Player>& players = GDBManager->GetPlayerManager().get_all();

	for (auto p : players)
	{
		string playerId = GDBManager->ConvertWstringToString(p.playerId);
		string playerPassword = GDBManager->ConvertWstringToString(p.playerPassword);

		if (playerId.compare(id) == 0)
		{
			// id와 연결된 비밀번호가 같다면 로그인 성공
			if(playerPassword.compare(password) == 0)
			{
				// 활성화된 계정으로 session과 함께 push 해주기
				PushActiveAccount(session, id);
				return true;
			}
			else
				return false;
		}
	}
	// 아이디가 없을 때
	return false;
}

Player AccountManager::GetAccountInfo(string id, string password)
{
	vector<Player>& players = GDBManager->GetPlayerManager().get_all();

	for (auto p : players)
	{
		string playerId = GDBManager->ConvertWstringToString(p.playerId);
		string playerPassword = GDBManager->ConvertWstringToString(p.playerNickname);

		if (playerId.compare(id) == 0)
		{
			Player player(p.id, p.playerId, p.playerPassword, p.playerNickname);
			return player;
		}
	}
}

bool AccountManager::IsActiveAccount(string id)
{
	// 활성화된 계정인지 체크
	if (m_ActiveAccount.find(id) != m_ActiveAccount.end()) 
	{
		return true;
	}

	return false;
}

int32 AccountManager::CheckFriend(string myId, string friendId)
{
	WRITE_LOCK;
	int32 result = AddPossible;
	
	vector<Friends> friendsArr = GDBManager->GetFriendsManager().get_all();
	vector<Requests> requestsArr = GDBManager->GetRequestsManager().get_all();

	for (auto f : friendsArr)
	{
		// 이미 친구일 때
		if (string(f.UserId.begin(), f.UserId.end()) == myId && string(f.FriendId.begin(), f.FriendId.end()) == friendId)
		{
			result = AlreadyFriend;
			return result;
		}
	}

	for (auto r : requestsArr)
	{
		// 내가 친구 요청을 보냈거나 상대가 보냈을 때
		if (string(r.UserId.begin(), r.UserId.end()) == myId && string(r.RequestId.begin(), r.RequestId.end()) == friendId)
		{
			result = FriendAlreadyRequests;
			return result;
		}
		else if (string(r.UserId.begin(), r.UserId.end()) == friendId && string(r.RequestId.begin(), r.RequestId.end()) == myId)
		{
			result = AlreadyRequest;
			return result;
		}
	}
	return result;
}

bool AccountManager::IsDuplicateId(string id)
{
	vector<Player>& players = GDBManager->GetPlayerManager().get_all();;

	// 아이디 중복 확인
	for (auto p : players)
	{
		string player = GDBManager->ConvertWstringToString(p.playerId);
		if (player.compare(id) == 0)
			return true;
	}

	return false;
}

void AccountManager::AddFriend(string myId, string friendId, bool approve)
{
	wstring wMyId(myId.begin(), myId.end());

	// 친구 추가할 친구 아이디
	wstring wFriendId(friendId.begin(), friendId.end());
	
	// 수락을 눌렀을 때
	if (approve)
	{
		// 친구 추가해주기
		SP::AddFriend addFriend(*GDBManager->GetDBConn());
		addFriend.In_PlayerId(wMyId.c_str(), static_cast<int32>(wMyId.length()));
		addFriend.In_FriendId(wFriendId.c_str(), static_cast<int32>(wFriendId.length()));

		addFriend.Execute();

		// 메모리에 저장
		// 뒤집어서도 저장해주기
		Friends friends1(wMyId, wFriendId);
		GDBManager->GetFriendsManager().add_record(friends1);
		Friends friends2(wFriendId, wMyId);
		GDBManager->GetFriendsManager().add_record(friends2);

		vector<Player>& players = GDBManager->GetPlayerManager().get_all();
		
		for (auto p : players)
		{
			// 친구 추가하는거 broadcast
			string playerId;
			playerId.assign(p.playerId.begin(), p.playerId.end());
			Player player(p.id, p.playerId, p.playerPassword, p.playerNickname);

			// 수락 누른 입장에서 클라한테 요청온 친구를 친구 목록에 추가했다고 send
			if (playerId.compare(myId) == 0)
			{
				Protocol::S_ADD_FRIEND addFriendPkt;
				Protocol::UserInfo* userInfo = nullptr;

				userInfo = addFriendPkt.mutable_friend_();
				userInfo->set_id(player.id);
				userInfo->set_playerid(std::string(player.playerId.begin(), player.playerId.end()));
				userInfo->set_nickname(std::string(player.playerNickname.begin(), player.playerNickname.end()));
				userInfo->set_isonline(IsActiveAccount(myId));

				auto sendbuffer = ClientPacketHandler::MakeSendBuffer(addFriendPkt);
				GSessionManager.Send(wFriendId, sendbuffer);
				continue;
			}

			// 친구 요청을 보낸 애가 수락을 눌렀을 때, 클라한테도 얘가 수락 눌렀으니 우리 친구다 하는 것을 send
			if (playerId.compare(friendId) == 0)
			{
				Protocol::S_ADD_FRIEND addFriendPkt;
				Protocol::UserInfo* userInfo = nullptr;

				userInfo = addFriendPkt.mutable_friend_();
				userInfo->set_id(player.id);
				userInfo->set_playerid(std::string(player.playerId.begin(), player.playerId.end()));
				userInfo->set_nickname(std::string(player.playerNickname.begin(), player.playerNickname.end()));
				userInfo->set_isonline(IsActiveAccount(friendId));

				auto sendbuffer = ClientPacketHandler::MakeSendBuffer(addFriendPkt);
				GSessionManager.Send(wMyId, sendbuffer);
				continue;
			}
		}
	}

	// 친구 요청에서 지워준다
	SP::DeleteRequest deleteRequest(*GDBManager->GetDBConn());
	deleteRequest.In_PlayerId(wMyId.c_str(), static_cast<int32>(wMyId.length()));
	deleteRequest.In_RequestId(wFriendId.c_str(), static_cast<int32>(wFriendId.length()));

	deleteRequest.Execute();
	
}

void AccountManager::PushActiveAccount(PacketSessionRef session, string id)
{
	auto gameSession = static_pointer_cast<GameSession>(session);
	m_ActiveAccount.insert({ id, gameSession });
}

void AccountManager::DelActiveAccount(string id)
{
	WRITE_LOCK;
	m_ActiveAccount.erase(id);
}

void AccountManager::BroadcastAllFriends(string id, string playerNickname)
{
	Protocol::S_ACTIVE_FRIEND activeFriendPkt;
	
	activeFriendPkt.set_nickname(playerNickname);
	activeFriendPkt.set_isactive(true);
	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(activeFriendPkt);

	std::wstring wid;
	vector<Friends> friends = GDBManager->GetFriendsManager().find_by_UserId(wid.assign(id.begin(), id.end()));

	for (auto f : friends)
	{
		GSessionManager.Send(f.FriendId, sendBuffer);
	}
}

vector<Player> AccountManager::SearchFriendNickname(string friendNickname)
{
	string lowerFriendNickname = friendNickname;
	transform(lowerFriendNickname.begin(), lowerFriendNickname.end(), lowerFriendNickname.begin(), ::towlower);

	vector<Player> friendsArray;
	vector<Player>& players = GDBManager->GetPlayerManager().get_all();
	
	for (auto player : players)
	{
		string strNickname = string(player.playerNickname.begin(), player.playerNickname.end());
		string lowerStrNickname = strNickname;
		transform(lowerStrNickname.begin(), lowerStrNickname.end(), lowerStrNickname.begin(), ::towlower);
		if (lowerStrNickname.compare(0, lowerFriendNickname.size(), lowerFriendNickname) == 0)
		{  
			friendsArray.push_back(player);
		}
	}

	return friendsArray;
}
