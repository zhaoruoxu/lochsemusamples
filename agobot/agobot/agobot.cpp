#include "stdafx.h"
#include "network.h"
#include "agobot.h"

const char *Host = "localhost";
const char *Channel = "#agochan";
const char *Nick = "moxiao";
const char *User = "mxuser";
const char *Real = "mxreal";

enum AgobotState {
    STATE_IDLE,
    STATE_NAMES,
    STATE_WHO,

};

bool g_running;

inline strp FirstToken(strp buf, strp delim)
{
    return strtok(buf, delim);
}

inline strp NextToken(strp delim)
{
    return strtok(NULL, delim);
}

void Msg_315();
void Msg_353();
void Msg_366();
void Msg_324();
void Msg_352();

struct CmdHandler {
    strp cmd;
    void (*handler)();
} g_handlers[] = {
    { "353", Msg_353 },
    { "315", Msg_315 },
    { "366", Msg_366 },
    { "324", Msg_324 },
    { "352", Msg_352 },
};

void RunAgobot()
{
    if (!InitConnection(Host, "6667")) {
        printf("connection failed\n");
        return;
    }

    SendIrcFormat("NICK %s", Nick);
    SendIrcFormat("USER %s %s bla :%s", User, Host, Real);

    SendIrcFormat("JOIN %s", Channel);

    char buf[4096];

    g_running = true;
    while (g_running) {
        if (!Select()) continue;
        RecvIrc(buf, sizeof(buf));
        printf("-> %s\n", buf);

        char *p = FirstToken(buf, " ");
        p = NextToken(" ");

        for (int i = 0; i < _countof(g_handlers); i++) {
            if (!strcmp(p, g_handlers[i].cmd)) {
                g_handlers[i].handler();
            }
        }
    }

    CloseConnection();
}

void Msg_315()
{
    SendIrcFormat("QUIT :Leaving");
    g_running = false;
}

void Msg_353()
{
    strp nick = NextToken(" ");
    strp chanMode = NextToken(" ");
    strp chan = NextToken(" ");

    printf("Channel members: ");
    strp member = NextToken(":");
    member = FirstToken(member, " ");
    while (member) {
        printf("%s  ", member);
        member = NextToken(" ");
    }
    printf("\n");
}

void Msg_366()
{
    SendIrcFormat("MODE %s", Channel);
}

void Msg_324()
{
    SendIrcFormat("WHO %s", Channel);
}

void Msg_352()
{
    strp mynick = NextToken(" ");
    strp chan = NextToken(" ");
    strp user = NextToken(" ");
    strp host = NextToken(" ");
    strp server = NextToken(" ");
    strp nick = NextToken(" ");
    strp HG = NextToken(" ");

    strp hopcount = FirstToken(NextToken(":"), " ");
    strp realname = NextToken(" ");

    printf("Chan=%s, User=%s, Host=%s, Server=%s, Nick=%s, Hop=%s, Real=%s\n",
        chan, user, host, server, nick, hopcount, realname);
}