#include "pch.h"
#include "RoomManager.h"
#include "Room.h"
#include "DBManager.h"

#include <random>
#include <ctime>
#include <sstream>

RoomManagerRef GRoomManager = nullptr;

RoomManager::RoomManager()
{
}

RoomManager::~RoomManager()
{
}

void RoomManager::Initialize()
{
}

uint64 RoomManager::CreateRoom(string hostIp, PlayerRef hostPlayer)
{
	// �������� ���ȣ ���� �� �����
	WRITE_LOCK;

	uint64 roomNumber = GenerateRoomNumber();
	
	auto iter = _rooms.find(roomNumber);
	if (iter == _rooms.end())
	{
		RoomRef room = MakeShared<Room>();
		room->SetHostIp(hostIp);
		room->SetHostPlayer(hostPlayer);
		room->Enter();
		_rooms.insert({ roomNumber, room });
	}
	else if (iter != _rooms.end())
	{
		// todo ��� ���°� ����
		roomNumber = CreateRoom(hostIp, hostPlayer);
	}

	return roomNumber;
}

string RoomManager::JoinRoom(int32 roomNum, PlayerRef guestPlayer)
{
	auto iter = _rooms.find(roomNum);
	if (iter != _rooms.end())
	{
		if (iter->second->IsRoomFull())
			return "FULL";
		iter->second->Enter();
		iter->second->SetGuestPlayer(guestPlayer);
		return iter->second->GetHostIp();
	}
	else 
	{
		return "";
	}
}

void RoomManager::LeaveRoom(int32 roomNum)
{
	// Ŭ���̾�Ʈ�� �κ񿡼� ������ ��
	auto iter = _rooms.find(roomNum);
	if (iter != _rooms.end())
	{
		iter->second->SetGuestPlayer(nullptr);
		iter->second->Leave();
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
	int random_number;

	while (true)
	{
		// ���� �ð�(��)�� �õ�� ����Ͽ� ���� �����⸦ �ʱ�ȭ
		std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
		std::uniform_int_distribution<int> dist(1000, 9999);
		random_number = dist(rng);
		if (!GRoomManager->IsRoomNumberExist(random_number))
		{
			break;
		}
	}

	return random_number;
}

bool RoomManager::IsRoomNumberExist(int32 randomNum)
{
	for (auto room : _rooms)
	{
		if (room.first == randomNum)
			return true;
	}

	return false;
}

bool RoomManager::IsInRoom(wstring player)
{
	// �ʴ��Ϸ��� �÷��̾ �̹� �κ� �ִ���.
	for (const auto& pair : _rooms)
	{
		const RoomRef& room = pair.second;
		if (room && ((room->GetGuestPlayer() && room->GetGuestPlayer()->playerId == player)
			|| (room->GetHostPlayer() && room->GetHostPlayer()->playerId == player)))
		{
			return true;
		}
	}
	return false;
}

vector<pair<int32, wstring>> RoomManager::SearchRoomList(int32 num)
{
	vector<pair<int32, wstring>> roomList;
	// �Է¹��� ��ȣ -> ���ڿ�
	std::string prefixStr = std::to_string(num);
	size_t prefixLength = prefixStr.length();

	for (const auto& room : _rooms)
	{
		// �� ��ȣ�� ���ڿ��� ��ȯ
		std::string roomStr = std::to_string(room.first);

		if (roomStr.compare(0, prefixLength, prefixStr) == 0)
		{
			roomList.push_back({ room.first, room.second->GetHostPlayer()->playerNickname });
		}
	}

	return roomList;
}

void RoomManager::PlayerInRoomDisconnected(wstring player)
{
	// Disconnect�� �����ϱ� �濡�� ����ó���ϰų� ���ֱ�
	for (const auto& pair : _rooms)
	{
		const RoomRef& roomPlayer = pair.second;
		if (roomPlayer && roomPlayer->GetGuestPlayer() && roomPlayer->GetGuestPlayer()->playerId == player)
		{
			cout << "Ŭ���̾�Ʈ ����" << endl;
			LeaveRoom(pair.first);
			return;
		}
		else if (roomPlayer && roomPlayer->GetHostPlayer() && roomPlayer->GetHostPlayer()->playerId == player)
		{
			cout << "���� ����" << endl;
			DestroyRoom(pair.first);
			return;
		}
	}
}