// TaintFormat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#pragma comment(lib, "ws2_32.lib")

static const char * Port = "56789";
static const char * ServerAddress = "localhost";

static const int    BufLength = 1024;

typedef unsigned char byte;

void PrintField(char *buf, int len)
{
    char strbuf[BufLength];
    ZeroMemory(strbuf, BufLength);
    memcpy(strbuf, buf, len);
    printf("field: %s\n", strbuf);
}

void KeySchedule(byte *S, const char *key, int n)
{
    for (int i = 0; i < 256; i++)
        S[i] = i;
    byte j = 0;
    for (int i = 0; i < 256; i++) {
        j += S[i] + (byte) key[i % n];
        std::swap(S[i], S[j]);
//         byte t = S[i];
//         S[i] = S[j];
//         S[j] = t;
    }
}

byte Gen(byte *S, byte &a, byte &b)
{
    a++;
    b += S[a];
    std::swap(S[a], S[b]);
    return S[(S[a] + S[b]) & 0xff];
}

void RC4Crypt(char *dest, const char *src, int n, const char *key, int keylen)
{
    byte S[256];
    KeySchedule(S, key, keylen);

    byte a = 0, b = 0;
    for (int i = 0; i < n; i++) {
        dest[i] = src[i] ^ Gen(S, a, b);
    }
}

static const char *Key = "gossip";
void ProcessMessage(char *buf, int len)
{
    /*
     * | 32-bit length | variable len | 32-bit fixed | variable len | ( ' ' variable len ) * |
     */
    int l = reinterpret_cast<int *>(buf)[0];
    char dec[256];
    RC4Crypt(dec, buf + 4, l, Key, strlen(Key));
    dec[l] = 0;

    printf("Message: %s\n", dec);

    char *p = strtok(dec, " ");
    while (p) {
        printf("# %s\n", p);
        p = strtok(NULL, " ");
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
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

    char buf[] = "hello";

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

    char recvbuf[BufLength];
    do {
        result = recv(connectSocket, recvbuf, BufLength, 0);
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

