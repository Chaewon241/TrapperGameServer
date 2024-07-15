#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "BufferReader.h"
#include "ServerPacketHandler.h"

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

int main()
{
	ServerPacketHandler::Init();

	this_thread::sleep_for(1s);

	ClientServiceRef service = MakeShared<ClientService>(
		NetAddress(L"172.16.1.72", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>, // TODO : SessionManager 등
		1);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 2; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}

	/*Protocol::C_CHAT chatPkt;
	chatPkt.set_msg(u8"Hello World !");
	auto sendBuffer = ServerPacketHandler::MakeSendBuffer(chatPkt);

	while (true)
	{
		service->Broadcast(sendBuffer);
		this_thread::sleep_for(1s);
	}*/

	int num;

	while (true)
	{
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
			pkt.set_id(id);
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
			pkt.set_id(id);
			pkt.set_password(password);
			pkt.set_nickname(nickname);
			auto sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
			service->Broadcast(sendBuffer);
		}
		this_thread::sleep_for(1s);
	}

	GThreadManager->Join();
}