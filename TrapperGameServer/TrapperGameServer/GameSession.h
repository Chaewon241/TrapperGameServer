#pragma once
#include "Session.h"
#include "ThreadManager.h"

class DBManager;

class GameSession : public PacketSession
{
public:
	~GameSession()
	{
		cout << "~GameSession" << endl;
	}

	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
	virtual void OnRecvPacket(BYTE* buffer, int32 len) override;
	virtual void OnSend(int32 len) override;

	PlayerRef GetPlayer();
	void SetPlayer(PlayerRef newPlayer);

	bool IsActive() { return _isActive; }
	void SetActive(bool active) { _isActive = active; }

private:
	PlayerRef _player;
	bool _isActive = false;
};