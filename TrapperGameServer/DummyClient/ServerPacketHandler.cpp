#include "pch.h"
#include "ServerPacketHandler.h"
#include "ClientContent.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

// 직접 컨텐츠 작업자

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO : Log
	return false;
}

bool Handle_S_CREATE_ACCOUNT(PacketSessionRef& session, Protocol::S_CREATE_ACCOUNT& pkt)
{
	if (pkt.success() == false)
	{
		cout << "회원가입 실패" << endl;
	}
	else
	{
		cout << "회원가입 성공" << endl;
	}
	GClientContent->StartMain();

	return true;
	
}

bool Handle_S_CHECK_DUPLICATE_ID(PacketSessionRef& session, Protocol::S_CHECK_DUPLICATE_ID& pkt)
{
	return false;
}

bool Handle_S_LOGIN(PacketSessionRef& session, Protocol::S_LOGIN& pkt)
{
	if (pkt.success() == false)
	{
		cout << "로그인 실패" << endl;
		GClientContent->StartMain();
	}
	else
	{
		cout << "로그인 성공" << endl;
		GClientContent->SetMyId(pkt.user().playerid());
		GClientContent->AfterLogin();
	}

	return true;
}

bool Handle_S_ACTIVE_FRIEND(PacketSessionRef& session, Protocol::S_ACTIVE_FRIEND& pkt)
{
	return false;
}

bool Handle_S_SEND_REQUEST(PacketSessionRef& session, Protocol::S_SEND_REQUEST& pkt)
{
	return false;
}

bool Handle_S_ADD_FRIEND(PacketSessionRef& session, Protocol::S_ADD_FRIEND& pkt)
{
	/*auto result = pkt.approve();

	if (result == AddSuccess)
		cout << "친구추가 성공" << endl;
	else if (result == UserAndFriendSameId)
		cout << "유저아이디랑 친구아이디랑 똑같으면 안됨" << endl;
	else if (result == NotExistFriendId)
		cout << "친구아이디가 없음" << endl;
	else if (result == AlreadyFriend)
		cout << "이미 친구임" << endl;
	else if (result == InsertFailed)
		cout << "친구추가 실패" << endl;*/

	GClientContent->AfterLogin();

	return false;
}

bool Handle_S_CHECK_FRIEND(PacketSessionRef& session, Protocol::S_CHECK_FRIEND& pkt)
{
	return false;
}

bool Handle_S_GET_FRIEND(PacketSessionRef& session, Protocol::S_GET_FRIEND& pkt)
{
	for (int i = 0; i < pkt.friends_size(); i++)
	{
		cout << "친구" << i + 1 << " 닉네임 : " << pkt.friends()[i].nickname() << endl;
	}

	GClientContent->AfterLogin();

	return true;
}

bool Handle_S_GET_REQUESTS(PacketSessionRef& session, Protocol::S_GET_REQUESTS& pkt)
{
	return false;
}


bool Handle_S_CREATE_ROOM(PacketSessionRef& session, Protocol::S_CREATE_ROOM& pkt)
{
	return false;
}

bool Handle_S_SHOW_ROOM(PacketSessionRef& session, Protocol::S_SHOW_ROOM& pkt)
{
	return false;
}

bool Handle_S_JOIN_ROOM(PacketSessionRef& session, Protocol::S_JOIN_ROOM& pkt)
{
	return false;
}

bool Handle_S_LEAVE_ROOM(PacketSessionRef& session, Protocol::S_LEAVE_ROOM& pkt)
{
	return false;
}

bool Handle_S_DESTROY_ROOM(PacketSessionRef& session, Protocol::S_DESTROY_ROOM& pkt)
{
	return false;
}

bool Handle_S_SEND_INVITATION(PacketSessionRef& session, Protocol::S_SEND_INVITATION& pkt)
{
	return false;
}

bool Handle_S_ENTER_GAME(PacketSessionRef& session, Protocol::S_ENTER_GAME& pkt)
{
	// TODO
	return true;
}

bool Handle_S_CHAT(PacketSessionRef& session, Protocol::S_CHAT& pkt)
{
	std::cout << pkt.msg() << endl;
	return true;
}
