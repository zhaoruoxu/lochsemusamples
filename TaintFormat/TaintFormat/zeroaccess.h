#pragma once
 
#ifndef __TAINTFORMAT_ZEROACCESS_H__
#define __TAINTFORMAT_ZEROACCESS_H__

struct ZAPacket {
    unsigned int Magic;
    unsigned int CRC;
    unsigned int Cmd;
    unsigned int Length;
    unsigned int Data;
};

void ZeroAccessTest(char *buf, int len);

#endif // __TAINTFORMAT_ZEROACCESS_H__