#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "BufferWriter.h"
#include "ClientPacketHandler.h"
#include <tchar.h>
#include "Protocol.pb.h"
#include "DBConnectionPool.h"
#include "DBBind.h"
#include "XmlParser.h"
#include "DBSynchronizer.h"
#include "GenProcedures.h"
#include "AccountManager.h"
#include "RoomManager.h"
#include "DBManager.h"

std::wstring convert_to_wstring(const std::string& str) 
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	std::wstring wstr(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size_needed);
	return wstr;
}

int main(int argc, char* argv[])
{ 
	/*ASSERT_CRASH(GDBConnectionPool->Connect(1, L"Driver={ODBC Driver 17 for SQL Server};Server=(localdb)\\MSSQLLocalDB;Database=ServerDb;Trusted_Connection=yes;"));

	DBConnection* dbConn = GDBConnectionPool->Pop();
	DBSynchronizer dbSync(*dbConn);
	dbSync.Synchronize(L"GameDB.xml");

	SP::DeleteAllRequests deleteAllGold(*dbConn);
	deleteAllGold.Execute();*/

	std::vector<std::wstring> args;
	for (int i = 0; i < argc; ++i) 
	{
		args.push_back(convert_to_wstring(argv[i]));
	}

	ClientPacketHandler::Init();

#ifdef LOGIN
	GDBManager = MakeShared<DBManager>();
	GDBManager->Initialize();
	GAccountManager = MakeShared<AccountManager>();
#endif
	GRoomManager = MakeShared<RoomManager>();

	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(args[1], 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>,
		100);

	ASSERT_CRASH(service->Start()); 
	auto startTime = std::chrono::high_resolution_clock::now();

	int numWorkers = std::thread::hardware_concurrency() * 2;
	for (int32 i = 0; i < numWorkers; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}


	GThreadManager->Join();

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - startTime;

	std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
}
