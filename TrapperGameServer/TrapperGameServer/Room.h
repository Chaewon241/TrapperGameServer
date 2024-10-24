#pragma once

class Room
{
public:
	void Enter();
	void Leave();

	void SetHostIp(string hostIp) { _hostIp = hostIp; }
	string& GetHostIp() { return _hostIp ; }

	void SetHostPlayer(PlayerRef player) { _hostPlayer = player; }
	PlayerRef GetHostPlayer() { return _hostPlayer; }

	void SetGuestPlayer(PlayerRef player) { _guestPlayer = player; }
	PlayerRef GetGuestPlayer() { return _guestPlayer; }

	bool IsRoomFull() { return _playersNum == 2 ? true : false; }

private:
	USE_LOCK;
	uint64 _playersNum = 0;
	string _hostIp = "";

	PlayerRef _hostPlayer = nullptr;
	PlayerRef _guestPlayer = nullptr;
};

extern Room GRoom;