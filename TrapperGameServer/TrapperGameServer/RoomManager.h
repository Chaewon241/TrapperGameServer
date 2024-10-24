#pragma once

extern RoomManagerRef GRoomManager;

class RoomManager
{
public:
	RoomManager();
	~RoomManager();

public:
	void Initialize();

	uint64 CreateRoom(string hostIp, PlayerRef hostPlayer);

	string JoinRoom(int32 roomNum, PlayerRef guestPlayer);

	void LeaveRoom(int32 roomNum);

	void DestroyRoom(int32 roomNum);

	uint64 GenerateRoomNumber();

	bool IsRoomNumberExist(int32 randomNum);

	bool IsInRoom(wstring player);

	vector<pair<int32, wstring>> SearchRoomList(int32 num);

	void PlayerInRoomDisconnected(wstring player);

private:
	USE_LOCK;
	HashMap<int32, RoomRef> _rooms;
};