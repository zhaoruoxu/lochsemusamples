#include "stdafx.h"
#include "common.h"
#include <openssl/des.h>

static const char *Key = "abcdefgh";

inline void SwapEndian(short &val)
{
    val = (val<<8) | (val>>8);
}

inline void SwapEndian(int &val)
{
    val = (val<<24) | ((val<<8) & 0x00ff0000) |
        ((val>>8) & 0x0000ff00) | (val>>24);
}

void Decrypt(const char *key, const char *ct, char *pt, int nBlocks)
{
    DES_cblock desKey;
    ZeroMemory(&desKey, sizeof(DES_cblock));
    strncpy((char *) &desKey, key, sizeof(DES_cblock));
    DES_key_schedule schedule;

    DES_set_odd_parity(&desKey);
    DES_set_key_checked(&desKey, &schedule);

    const_DES_cblock *cipherText = (const_DES_cblock *) ct;
    DES_cblock *plainText = (DES_cblock *) pt;

    for (int i = 0; i < nBlocks; i++) {
        DES_ecb_encrypt(cipherText + i, plainText + i, &schedule, DES_DECRYPT);
    }
}

void MegaDTest( char *buf, int len )
{
    char decbuf[256];
    ZeroMemory(decbuf, sizeof(decbuf));
    short nBlocks = reinterpret_cast<short *>(buf)[0];
    SwapEndian(nBlocks);
    Decrypt(Key, buf + 2, decbuf, nBlocks);

    printf("%s\n", decbuf);
}
