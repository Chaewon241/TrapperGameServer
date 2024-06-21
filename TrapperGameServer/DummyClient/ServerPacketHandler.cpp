#include "pch.h"
#include "ServerPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

// 직접 컨텐츠 작업자

void ProcessLogin(PacketSessionRef& session)
{
	Protocol::C_LOGIN loginPkt;
	cout << "id를 입력하세여 : ";
	string id;
	cin >> id;
	loginPkt.set_id(id);
	cout << "비밀번호를 입력하세여 : ";
	string password;
	cin >> password;
	loginPkt.set_password(password);

	auto sendBuffer = ServerPacketHandler::MakeSendBuffer(loginPkt);
	session->Send(sendBuffer);
}

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
	return true;
	
}

bool Handle_S_LOGIN(PacketSessionRef& session, Protocol::S_LOGIN& pkt)
{
	if (pkt.success() == false)
	{
		cout << "로그인 실패" << endl;
	}
	else
	{
		cout << "로그인 성공" << endl;
	}


	// 입장 UI 버튼 눌러서 게임 입장
	//Protocol::C_ENTER_GAME enterGamePkt;
	//enterGamePkt.set_playerindex(0); // 첫번째 캐릭터로 입장
	//auto sendBuffer = ServerPacketHandler::MakeSendBuffer(enterGamePkt);
	//session->Send(sendBuffer);

	return true;
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
