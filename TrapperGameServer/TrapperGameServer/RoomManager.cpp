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
	// 랜덤으로 방번호 만들어서 방 만들기
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
		// todo 재귀 도는거 생각
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
	// 클라이언트가 로비에서 나갔을 때
	auto iter = _rooms.find(roomNum);
	if (iter != _rooms.end())
	{
		iter->second->SetGuestPlayer(nullptr);
		iter->second->Leave();
	}
}

void RoomManager::DestroyRoom(int32 roomNum)
{
	// 호스트가 로비에서 나갔을 때나 게임이 시작됐을때
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
		// 현재 시간(초)을 시드로 사용하여 난수 생성기를 초기화
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
	// 초대하려는 플레이어가 이미 로비에 있는지.
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
	// 입력받은 번호 -> 문자열
	std::string prefixStr = std::to_string(num);
	size_t prefixLength = prefixStr.length();

	for (const auto& room : _rooms)
	{
		// 방 번호를 문자열로 변환
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
	// Disconnect가 됐으니까 방에서 나감처리하거나 없애기
	for (const auto& pair : _rooms)
	{
		const RoomRef& roomPlayer = pair.second;
		if (roomPlayer && roomPlayer->GetGuestPlayer() && roomPlayer->GetGuestPlayer()->playerId == player)
		{
			cout << "클라이언트 나감" << endl;
			LeaveRoom(pair.first);
			return;
		}
		else if (roomPlayer && roomPlayer->GetHostPlayer() && roomPlayer->GetHostPlayer()->playerId == player)
		{
			cout << "서버 나감" << endl;
			DestroyRoom(pair.first);
			return;
		}
	}
}