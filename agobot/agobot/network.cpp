#include "stdafx.h"
#include "network.h"

static const int    BufLength = 1024;

static SOCKET g_connSocket = INVALID_SOCKET;

bool InitConnection(const char *serveraddr, const char *port)
{
    // initialize Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        printf("WSAStartup failed with error: %d\n", result);
        return false;
    }

    ADDRINFOA   hints, *addrResult = NULL;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family     = AF_UNSPEC;
    hints.ai_socktype   = SOCK_STREAM;
    hints.ai_protocol   = IPPROTO_TCP;

    // resolve server address and port
    result = GetAddrInfoA(serveraddr, port, &hints, &addrResult);
    if (result != 0) {
        printf("getaddrinfo() failed with error: %d\n", result);
        WSACleanup();
        return false;
    }

    for (addrinfo *ptr = addrResult; ptr != NULL; ptr = ptr->ai_next) {
        g_connSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (INVALID_SOCKET == g_connSocket) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return false;
        }

        result = connect(g_connSocket, ptr->ai_addr, (int) ptr->ai_addrlen);
        if (result == SOCKET_ERROR) {
            closesocket(g_connSocket);
            g_connSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(addrResult);

    if (g_connSocket == INVALID_SOCKET) {
        printf("Unable to connect to server\n");
        WSACleanup();
        return false;
    }
    return true;
}

void CloseConnection() 
{
    closesocket(g_connSocket);
    WSACleanup();
}

bool RecvIrc( char *buf, int n )
{
    int index = 0;
    buf[index] = '\0';
    bool receiving = true;
    while (index < n - 1) {
        if (!Recv(buf + index, 1, NULL)) return false;
        buf[index + 1] = '\0';
        if (buf[index] == '\n') {
            if (buf[index-1] == '\r')
                buf[index-1] = '\0';
            else
                buf[index] = '\0';
            break;
        }
        index++;
    }
    return true;
}

bool Send( char *buf, int n, int *bytesWritten )
{
    int bytes = send(g_connSocket, buf, n, 0);
    if (bytes == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        return false;
    }
    if (bytesWritten) *bytesWritten = bytes;
    return true;
}

bool Recv( char *buf, int n, int *bytesRead )
{
    int bytes = recv(g_connSocket, buf, n, 0);
    if (bytes == SOCKET_ERROR) {
        printf("recv failed with error: %d\n", WSAGetLastError());
        return false;
    }
    if (bytesRead) *bytesRead = bytes;
    return true;
}

bool SendFormat( const char *szFmt, ... )
{
    va_list valist;
    char buf[8192];
    va_start(valist, szFmt);
    vsnprintf(buf, sizeof(buf), szFmt, valist);
    va_end(valist);
    return Send(buf, strlen(buf), NULL);
}

bool SendIrcFormat( const char *szFmt, ... )
{
    va_list valist;
    char buf[8192];
    va_start(valist, szFmt);
    vsnprintf(buf, sizeof(buf), szFmt, valist);
    va_end(valist);
    strcat(buf, "\r\n");
    return Send(buf, strlen(buf), NULL);
}

bool Select()
{
    timeval tv;
    tv.tv_usec = 0;
    tv.tv_sec = 2;
    fd_set fd;
    FD_ZERO(&fd);
    FD_SET(g_connSocket, &fd);
    int r = select(g_connSocket+1, &fd, NULL, NULL, &tv);
    if (r == 0) {
        return false;
    } else if (FD_ISSET(g_connSocket, &fd)) {
        return true;
    } else {
        printf("select error: %d\n", WSAGetLastError());
        return false;
    }
}
