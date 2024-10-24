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
	// ģ�� �߰� ��ư�� ������ �� ģ���� ���� Ȯ��
	int32 CheckFriend(string myId, string friendId);
	// id�� �ߺ����� Ȯ��
	bool IsDuplicateId(string id);
	// ģ�� ��û���� ������ ������ �� ģ�� �߰�
	void AddFriend(string myId, string friendId, bool approve);
	
	void PushActiveAccount(PacketSessionRef session, string id);
	void DelActiveAccount(string id);
	// �α��� ���� �� �� Active �ƴٰ� Broadcast �ϴ� �Լ�
	void BroadcastAllFriends(string playerId, string playerNickname);

	vector<Player> SearchFriendNickname(string friendNickname);

private:
	USE_LOCK;
	unordered_map<string, GameSessionRef> m_ActiveAccount;
};

