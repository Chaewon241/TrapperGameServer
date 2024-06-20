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
		//Protocol::C_LOGIN pkt;
		cout << "회원가입은 1, 로그인은 2";
		int num;
		cin >> num;

		bool flag = false;

		MainLogin(num, flag);

		//auto sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
		//Send(sendBuffer);
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

	void MainLogin(int16 num, bool& flag)
	{
		switch (num)
		{
		case 1:
			CreateAccount();
			break;
		case 2:
			ProcessLogin(flag);
			break;
		default:
			break;
		}
	}
	void CreateAccount()
	{
		Protocol::C_CREATE_ACCOUNT createAccountPkt;
		cout << "id를 입력하세여 : ";
		string id;
		cin >> id;
		createAccountPkt.set_id(id);
		cout << "비밀번호를 입력하세여 : ";
		string password;
		cin >> password;
		createAccountPkt.set_password(password);

		auto sendBuffer = ServerPacketHandler::MakeSendBuffer(createAccountPkt);
		Send(sendBuffer);
	}

	void ProcessLogin(bool& flag)
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
		Send(sendBuffer);
	}
};

int main()
{
	ServerPacketHandler::Init();

	this_thread::sleep_for(1s);

	ClientServiceRef service = MakeShared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>, // TODO : SessionManager 등
		100);

	ASSERT_CRASH(service->Start());

		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});


	/*Protocol::C_CHAT chatPkt;
	chatPkt.set_msg(u8"Hello World !");
	auto sendBuffer = ServerPacketHandler::MakeSendBuffer(chatPkt);

	while (true)
	{
		service->Broadcast(sendBuffer);
		this_thread::sleep_for(1s);
	}*/

	GThreadManager->Join();
}