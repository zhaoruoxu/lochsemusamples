#include "stdafx.h"
#include "network.h"
#include "agobot.h"

const char *Host = "localhost";
const char *Channel = "#Agonet";
const char *Nick = "bot_00000001";
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

void Msg_315(strp p);
void Msg_353(strp p);
void Msg_366(strp p);
void Msg_324(strp p);
void Msg_352(strp p);
void Msg_376(strp p);

void Ping_Handler(strp p);

struct CmdHandler {
    strp cmd;
    void (*handler)(strp p);
};

CmdHandler g_handlers1[] = {
    { "PING", Ping_Handler }
};

CmdHandler g_handlers2[] = {
    { "353", Msg_353 },
    { "315", Msg_315 },
    { "366", Msg_366 },
    { "324", Msg_324 },
    { "352", Msg_352 },
    { "376", Msg_376 },
};

void RunAgobot()
{
    if (!InitConnection(Host, "6667")) {
        printf("connection failed\n");
        return;
    }

    SendIrcFormat("NICK %s", Nick);
    SendIrcFormat("USER %s 0 * :%s", User, Host, Real);

    //

    char buf[4096];

    g_running = true;
    while (g_running) {
        if (!Select()) continue;
        RecvIrc(buf, sizeof(buf));
        printf("-> %s\n", buf);

        char *p = FirstToken(buf, " ");
        char *q = NextToken(" ");

        for (int i = 0; i < _countof(g_handlers1); i++) {
            if (!strcmp(p, g_handlers1[i].cmd)) {
                g_handlers1[i].handler(q);
            }
        }

        for (int i = 0; i < _countof(g_handlers2); i++) {
            if (!strcmp(q, g_handlers2[i].cmd)) {
                g_handlers2[i].handler(q);
            }
        }
    }

    CloseConnection();
}

void Ping_Handler(strp p)
{
    char buf[128];
    sprintf(buf, "PONG %s", p);
    SendIrcFormat(buf);
}

void Msg_315(strp p)
{
    SendIrcFormat("QUIT :Leaving");
    g_running = false;
}

__declspec(noinline)
void ProcessMember(const char *name)
{
    printf("Member: %s\n", name);
}

void Msg_353(strp p)
{
    strp nick = NextToken(" ");
    strp chanMode = NextToken(" ");
    strp chan = NextToken(" ");

    strp member = FirstToken(NextToken(":"), " ");
    while (member) {
        ProcessMember(member);
        member = NextToken(" ");
    }
    printf("\n");
}

void Msg_366(strp p)
{
    SendIrcFormat("MODE %s", Channel);
}

void Msg_324(strp p)
{
    SendIrcFormat("WHO %s", Channel);
}

void Msg_352(strp p)
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

void Msg_376(strp p)
{
    SendIrcFormat("JOIN %s", Channel);
}
