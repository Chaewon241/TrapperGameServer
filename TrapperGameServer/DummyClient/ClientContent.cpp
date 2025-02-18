#include "pch.h"
#include "ClientContent.h"
#include "ServerPacketHandler.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"

ClientContentRef GClientContent;

char sendData[] = "Hello World";

class ServerSession : public PacketSession
{
public:
	~ServerSession()
	{
		cout << "~ServerSession" << endl;
	}

	virtual void OnConnected() override
	{
	}

	virtual void OnRecvPacket(BYTE* buffer, int32 len) override
	{
		PacketSessionRef session = GetPacketSessionRef();
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

		// TODO : packetId 대역 체크
		ServerPacketHandler::HandlePacket(session, buffer, len);
	}

	virtual void OnSend(int32 len) override
	{
		//cout << "OnSend Len = " << len << endl;
	}

	virtual void OnDisconnected() override
	{
		//cout << "Disconnected" << endl;
	}
};

void ClientContent::Start()
{
	this_thread::sleep_for(1s);

	 service = MakeShared<ClientService>(
		NetAddress(L"172.36.1.23", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>, // TODO : SessionManager 등
		5000);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 100; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}

	StartMain();

	while (true)
	{

	}

	GThreadManager->Join();
	
}

void ClientContent::SetMyId(string id)
{
	myId = id;
}

void ClientContent::AfterLogin()
{
	int num;

	cout << "친구 추가(1) 친구 목록(2) : ";
	cin >> num;
	
	if (num == 1)
	{
		string id;
		cout << "친구추가할 아이디 : ";
		cin >> id;

		Protocol::C_ADD_FRIEND pkt;
		pkt.set_myid(myId);
		pkt.set_friendid(id);
		auto sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
		service->Broadcast(sendBuffer);
	}
	else if (num == 2)
	{
		Protocol::C_GET_FRIEND pkt;
		pkt.set_playerid(myId);
		auto sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
		service->Broadcast(sendBuffer);
	}

}

void ClientContent::StartMain()
{
	int num;

	cout << "회원가입(1) 로그인(2) : ";
	cin >> num;
	string id, password;
	cout << "아이디 : ";
	cin >> id;
	cout << "비밀번호 : ";
	cin >> password;

	if (num == 2)
	{
		Protocol::C_LOGIN pkt;
		pkt.set_playerid(id);
		pkt.set_password(password);
		auto sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
		service->Broadcast(sendBuffer);
	}
	else if (num == 1)
	{
		cout << "닉네임을 입력하세요 : " << endl;

		string nickname;
		cin >> nickname;

		Protocol::C_CREATE_ACCOUNT pkt;
		pkt.set_playerid(id);
		pkt.set_password(password);
		pkt.set_nickname(nickname);
		auto sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
		service->Broadcast(sendBuffer);
	}
}

