#include "pch.h"
#include "ServerPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

// ���� ������ �۾���

void ProcessLogin(PacketSessionRef& session)
{
	Protocol::C_LOGIN loginPkt;
	cout << "id�� �Է��ϼ��� : ";
	string id;
	cin >> id;
	loginPkt.set_id(id);
	cout << "��й�ȣ�� �Է��ϼ��� : ";
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
		cout << "ȸ������ ����" << endl;
	}
	else
	{
		cout << "ȸ������ ����" << endl;
	}
	return true;
	
}

bool Handle_S_LOGIN(PacketSessionRef& session, Protocol::S_LOGIN& pkt)
{
	if (pkt.success() == false)
	{
		cout << "�α��� ����" << endl;
	}
	else
	{
		cout << "�α��� ����" << endl;
	}


	// ���� UI ��ư ������ ���� ����
	//Protocol::C_ENTER_GAME enterGamePkt;
	//enterGamePkt.set_playerindex(0); // ù��° ĳ���ͷ� ����
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
