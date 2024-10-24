#pragma once
#include <unordered_map>
USING_SHARED_PTR(AccountManager);
extern AccountManagerRef GAccountManager;

class DBConnection;
class DBManager;

class AccountManager
{
public:
	AccountManager();

public:
	bool Join(string id, string password, string nickname);
	bool Login(PacketSessionRef session, string id, string password);

	Player GetAccountInfo(string id, string password);

	bool IsActiveAccount(string id);
	// 친구 추가 버튼을 눌렀을 때 친구의 상태 확인
	int32 CheckFriend(string myId, string friendId);
	// id가 중복인지 확인
	bool IsDuplicateId(string id);
	// 친구 요청에서 수락을 눌렀을 때 친구 추가
	void AddFriend(string myId, string friendId, bool approve);
	
	void PushActiveAccount(PacketSessionRef session, string id);
	void DelActiveAccount(string id);
	// 로그인 했을 때 나 Active 됐다고 Broadcast 하는 함수
	void BroadcastAllFriends(string playerId, string playerNickname);

	vector<Player> SearchFriendNickname(string friendNickname);

private:
	USE_LOCK;
	unordered_map<string, GameSessionRef> m_ActiveAccount;
};

