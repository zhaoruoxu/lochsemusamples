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

    SendIrcFormat("JOIN #sdf");
    SendIrcFormat("MODE #sdf");
    SendIrcFormat("WHO #sdf");


    char buf[4096];

    bool running = true;
    while (running) {
        if (!Select()) continue;
        RecvIrc(buf, sizeof(buf));
        printf("-> %s\n", buf);

        char *p = strtok(buf, " :");
        p = strtok(NULL, " :");
        if (strcmp(p, "315") == 0) {
            SendIrcFormat("QUIT :Leaving");
            running = false;
        }
    }

    

    CloseConnection();

	return 0;
}

