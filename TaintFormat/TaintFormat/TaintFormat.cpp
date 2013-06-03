// TaintFormat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#pragma comment(lib, "ws2_32.lib")

#include "rc4test.h"
#include "mega_d.h"
#include "zeus.h"
#include "common.h"
#include "md5test.h"

static const char * Port = "56789";
static const char * ServerAddress = "localhost";

typedef unsigned char byte;

// void PrintField(char *buf, int len)
// {
//     char strbuf[BufLength];
//     ZeroMemory(strbuf, BufLength);
//     memcpy(strbuf, buf, len);
//     printf("field: %s\n", strbuf);
// }
// 
const char *Method[] = {
    "rc4",
    "mega-d",
    "zeus",
    "md5"
};
static int Choice = 0;

void ProcessMessage(char *buf, int len)
{
    if (Choice == 0) {
        RC4Test(buf, len);
    } else if (Choice == 1) {
        MegaDTest(buf, len);
    } else if (Choice == 2) {
        ZeusTest(buf, len);
    } else if (Choice == 3) {
        MD5Test(buf, len);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    srand(time(NULL));
#ifdef _DEBUG
    int dbgFlags;
    dbgFlags = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
    dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF;
    dbgFlags |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag( dbgFlags);
#endif

    if (argc == 1) {
        printf("Need argument\n");
        return 0;
    }

    Choice = _wtoi(argv[1]);

    // initialize Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        printf("WSAStartup failed with error: %d\n", result);
        return 1;
    }

    ADDRINFOA   hints, *addrResult = NULL;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family     = AF_UNSPEC;
    hints.ai_socktype   = SOCK_STREAM;
    hints.ai_protocol   = IPPROTO_TCP;

    // resolve server address and port
    result = GetAddrInfoA(ServerAddress, Port, &hints, &addrResult);
    if (result != 0) {
        printf("getaddrinfo() failed with error: %d\n", result);
        WSACleanup();
        return 1;
    }

    SOCKET connectSocket = INVALID_SOCKET;
    for (addrinfo *ptr = addrResult; ptr != NULL; ptr = ptr->ai_next) {
        connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (INVALID_SOCKET == connectSocket) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        result = connect(connectSocket, ptr->ai_addr, (int) ptr->ai_addrlen);
        if (result == SOCKET_ERROR) {
            closesocket(connectSocket);
            connectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(addrResult);

    if (connectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server\n");
        WSACleanup();
        return 1;
    }

    const char *buf = Method[Choice];

    result = send(connectSocket, buf, strlen(buf), 0);
    if (result == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }

    result = shutdown(connectSocket, SD_SEND);
    if (result == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }

    char recvbuf[BUF_LEN];
    do {
        result = recv(connectSocket, recvbuf, BUF_LEN, 0);
        if (result > 0) {
            ProcessMessage(recvbuf, result);
        } else if (result == 0) {
        } else {
            printf("recv failed with error: %d\n", WSAGetLastError());
        }
    } while (result > 0);

    closesocket(connectSocket);
    WSACleanup();

    return 0;
}

