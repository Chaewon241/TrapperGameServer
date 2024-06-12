#include "pch.h"
#include "NetworkManager.h"
#include "IocpManager.h"

int main() 
{
    NetworkManager nm;
    nm.Init();

    IocpManager im;
    
    SOCKET serverSocket = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

    SOCKET_STRUCT socketInfo;
    socketInfo.m_Socket = serverSocket;
    socketInfo.m_IP = L"127.0.0.1";
    socketInfo.m_Port = 7777;
    socketInfo.m_Type = SocketType::Server;

    im.Register(socketInfo);

    SOCKADDR_IN sockAddr;
    ::memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    ::inet_pton(AF_INET, "127.0.0.1", &(sockAddr.sin_addr));
    sockAddr.sin_port = ::htons(7777);

    nm.Accept(serverSocket, sockAddr);

    im.RegisterHandler([](OVERLAPPED_STRUCT* overlapped) { cout << "accept" << endl; });
    im.Dispatch();
}