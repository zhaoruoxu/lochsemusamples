#pragma once
 
#ifndef __TAINTFORMAT_ZEUS_H__
#define __TAINTFORMAT_ZEUS_H__
 
struct ZeusHeader {
    byte RND;
    byte TTL;
    byte LOP;
    byte Type;
    byte SessionID[20];
    byte SourceID[20];
};

struct ZeusHttpPayloadHeader {
    int MsgLen;
    int Flag;
    int NumFields;
    byte Hash[16];
};

struct ZeusFieldHeader {
    int Type;
    int Flag;
    int SizeCompressed;
    int Size;
};

void ZeusTest(char *buf, int len);

#endif // __TAINTFORMAT_ZEUS_H__