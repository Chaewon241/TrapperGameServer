#include "pch.h"
#include "NetworkManager.h"
#include "IocpManager.h"
#include "Service.h"
#include "ThreadManager.h"
#include "ClientSession.h"

int main()
{
    shared_ptr<NetworkManager> networkManager = make_shared<NetworkManager>();
    networkManager->Init();
    SOCKET clientSocket = networkManager->CreateSocket();

    SOCKADDR_IN sockAddr;
    ::memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    ::inet_pton(AF_INET, "127.0.0.1", &(sockAddr.sin_addr));
    sockAddr.sin_port = htons(7777);

    shared_ptr<IocpManager> iocpManager = make_shared<IocpManager>();

    SessionFactory factory = []() { return make_shared<ClientSession>(); };

    ClientServiceRef clientService = make_shared<ClientService>(sockAddr, iocpManager, factory);

    ASSERT_CRASH(clientService->Start());

    shared_ptr<ThreadManager> threadManager = make_shared<ThreadManager>();

    for (int32 i = 0; i < 2; i++)
    {
        threadManager->Launch([=]()
            {
                while (true)
                {
                    clientService->GetIocpManager()->Dispatch();
                }
            });
    }

    threadManager->Join();
}