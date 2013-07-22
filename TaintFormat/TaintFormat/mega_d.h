#pragma once
 
#ifndef __TAINTFORMAT_MEGA_D_H__
#define __TAINTFORMAT_MEGA_D_H__
 
struct MegaD_Header {
    unsigned short Version;
    unsigned short MsgType;
};

struct MegaD_INFO {     // len 34(32+2), MsgType is 0x01
    byte ID1[16];
    int D;
    byte ID2[8];
};

void MegaDTest(char *buf, int len);
 
#endif // __TAINTFORMAT_MEGA_D_H__