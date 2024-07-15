#include "pch.h"
#include "RoomManager.h"
#include "Room.h"

#include <random>
#include <ctime>

RoomManagerRef GRoomManager;

RoomManager::RoomManager()
{
}

RoomManager::~RoomManager()
{
}

void RoomManager::Initialize()
{
}

uint64 RoomManager::CreateRoom(string hostIp)
{
	// �������� ���ȣ ���� �� �����
	uint64 roomNumber = GenerateRoomNumber();
	
	auto iter = _rooms.find(roomNumber);
	if (iter == _rooms.end())
	{
		RoomRef room = MakeShared<Room>();
		room->SetHostIp(hostIp);
		room->Enter();
		_rooms.insert({ roomNumber, room });
	}
	else if (iter != _rooms.end())
	{
		// todo ��� ���°� ����
		roomNumber = CreateRoom(hostIp);
	}

	return roomNumber;
}

string RoomManager::JoinRoom(int32 roomNum)
{
	auto iter = _rooms.find(roomNum);
	if (iter != _rooms.end())
	{
		if (iter->second->IsRoomFull())
			return "FULL";
		iter->second->Enter();
		return iter->second->GetHostIp();
	}
	else
	{
		return "";
	}
}

void RoomManager::DestroyRoom(int32 roomNum)
{
	// ȣ��Ʈ�� �κ񿡼� ������ ���� ������ ���۵�����
	auto iter = _rooms.find(roomNum);
	if (iter != _rooms.end())
	{
		_rooms.erase(roomNum);
	}
}

uint64 RoomManager::GenerateRoomNumber()
{
	// ���� �ð�(��)�� �õ�� ����Ͽ� ���� �����⸦ �ʱ�ȭ
	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	// 1000���� 9999 ������ ������ �����ϴ� ����
	std::uniform_int_distribution<int> dist(1000, 9999);
	// ������ �����ϰ� ��ȯ
	return dist(rng);
}
