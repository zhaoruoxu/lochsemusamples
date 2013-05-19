// SocketEcho.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

bool ProcessMessage(char *msg, int n)
{
    char buf[4096];
    ZeroMemory(buf, 4096);
    int len = ((int *) msg)[0];
    memcpy(buf, msg + sizeof(int), len);
    buf[len+1] = '\0';

    printf("Client says: %s, length = %d\n", buf, len);
    return strcmp(buf, "quit") != 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
    static const int BufferSize = 1024;
    static const int Port       = 56789;

    WSADATA wsaData;
    SOCKET socketL, socketC;
    SOCKADDR_IN serverAddr;
    int nRet = -1;

    WORD version = MAKEWORD(1, 1);
    WSAStartup(version, &wsaData);

    socketL = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    serverAddr.sin_family   = AF_INET;
    serverAddr.sin_port     = htons(Port);
    serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    bind(socketL, (SOCKADDR *) &serverAddr, sizeof(serverAddr));

    listen(socketL, 5);

    printf("listening on port %d\n", Port);

    socketC = accept(socketL, NULL, NULL);

    char buf[BufferSize];
    while (true) {
        //ZeroMemory(buf, BufferSize);
        nRet = recv(socketC, buf, BufferSize, 0);

        if (nRet > 0) {
            if (!ProcessMessage(buf, nRet)) break;
        }
    }

    closesocket(socketC);
    closesocket(socketL);

    WSACleanup();

	return 0;
}

