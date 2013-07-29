#include "stdafx.h"
#include "stormtest.h"


void StormDecrypt(const char *buf, int len, byte *decbuf, int *declen)
{
    if (len % 4 != 0) {
        printf("error StormDecrypt\n");
        DebugBreak();
    }
    *declen = len / 4 * 3;
    for (int i = 0; i < len / 4; i++) {
        decbuf[i*3] = ((buf[i*4] - 0x21) << 2) + ((buf[i*4+1] - 0x21) >> 4);
        decbuf[i*3+1] = (((buf[i*4+1] - 0x21) & 0xf) << 4) + ((buf[i*4+2] - 0x21) >> 2);
        decbuf[i*3+2] = (((buf[i*4+2] - 0x21) & 0x3) << 6) + (buf[i*4+3] - 0x21);
    }
}

byte ChecksumXor(byte *buf, int len)
{
    byte r = 0;
    for (int i = 0; i < len; i++)
        r ^= buf[i];
    return r;
}

byte ChecksumAdd(byte *buf, int len)
{
    byte r = 0;
    for (int i = 0; i < len; i++)
        r += buf[i];
    return r;
}

void StormTest( char *buf, int len )
{
    byte decbuf[256];
    int declen;
    ZeroMemory(decbuf, sizeof(decbuf));
    StormDecrypt(buf, len, decbuf, &declen);
    printf("storm decrypted: %s\n", decbuf);
    printf("checksum xor match: %02x, %02x\n", decbuf[0], ChecksumXor(decbuf + 3, declen - 3));
    printf("checksum add match: %02x, %02x\n", decbuf[1], ChecksumAdd(decbuf + 3, declen - 3));
}
