#pragma once
 
#ifndef __AGOBOT_NETWORK_H__
#define __AGOBOT_NETWORK_H__
 
bool InitConnection(const char *servername, const char *port);
void CloseConnection();

bool RecvIrc(char *buf, int n);
bool Send(char *buf, int n, int *bytesWritten);
bool Recv(char *buf, int n, int *bytesRead);

bool SendFormat(const char *szFmt, ...);
bool SendIrcFormat(const char *szFmt, ...);

bool Select();
 
#endif // __AGOBOT_NETWORK_H__