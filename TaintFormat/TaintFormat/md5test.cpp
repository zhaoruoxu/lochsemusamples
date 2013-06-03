#include "stdafx.h"
#include "md5test.h"
#include "common.h"

#include <openssl/md5.h>

// __declspec(noinline)
// void MD5Check(byte *dat, int len, byte *md)
// {
//     MD5(dat, len, md);
// }

__declspec(noinline)
void MD5Test( char *buf, int len )
{
    byte md[16];
    MD5((byte *) buf + 16, len - 16, md);
    if (CompareByteArray((cpbyte) buf, md, 16) == 0) {
        printf("MD5 hash verified\n");
    } else {
        printf("MD5 hash mismatch!\n");
    }
}

__declspec(noinline)
void MD5Hash( cpbyte d, int n, pbyte md )
{
    MD5_CTX c;
    static unsigned char m[MD5_DIGEST_LENGTH];

    if (md == NULL) md=m;
    if (!MD5_Init(&c))
        return;
    MD5_Update(&c, d, n);
//     char temp[1024];
//     unsigned long chunk;
// 
//     while (n > 0)
//     {
//         chunk = (n > sizeof(temp)) ? sizeof(temp) : n;
//         ebcdic2ascii(temp, d, chunk);
//         MD5_Update(&c,temp,chunk);
//         n -= chunk;
//         d += chunk;
//     }
    MD5_Final(md,&c);
}
