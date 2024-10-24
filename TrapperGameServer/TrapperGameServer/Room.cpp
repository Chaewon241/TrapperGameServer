#include "pch.h"
#include "Room.h"
#include "GameSession.h"

Room GRoom;

void Room::Enter()
{
	WRITE_LOCK;
	_playersNum++;
}

void Room::Leave()
{
	WRITE_LOCK;
	_playersNum--;
}