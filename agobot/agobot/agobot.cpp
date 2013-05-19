// agobot.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "network.h"

#pragma comment(lib, "ws2_32.lib")

const char *Host = "localhost";

int _tmain(int argc, _TCHAR* argv[])
{
    if (!InitConnection(Host, "6667")) {
        printf("connection failed\n");
        return EXIT_FAILURE;
    }

    SendIrcFormat("NICK moxiao");
    SendIrcFormat("USER %s %s bla :%s", "Moxiao", Host, "mxReal");

    char buf[4096];

    RecvIrc(buf, sizeof(buf));

    printf("received: %s\n", buf);

    SendIrcFormat("QUIT :Leaving");

    CloseConnection();

	return 0;
}

