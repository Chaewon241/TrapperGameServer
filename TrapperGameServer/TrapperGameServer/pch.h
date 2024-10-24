#pragma once

#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#pragma comment(lib, "ServerCore\\Debug\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#else
#pragma comment(lib, "ServerCore\\Release\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#endif

#include "CorePch.h"
#include "Enum.pb.h"
#include "Struct.pb.h"
#include "Protocol.pb.h"

using GameSessionRef = shared_ptr<class GameSession>;
using RoomRef = shared_ptr<class Room>;
using PlayerRef = shared_ptr<class Player>;
using FriendsRef = shared_ptr<class Friends>;
using RoomManagerRef = shared_ptr<class RoomManager>;
using DBManagerRef = shared_ptr<class DBManager>;