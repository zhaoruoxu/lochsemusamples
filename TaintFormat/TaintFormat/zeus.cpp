#include "stdafx.h"
#include "zeus.h"

void ZeusEncrypt(void *buf, int len)
{
    for (int i = 1; i < len; i++) {
        ((byte *) buf)[i] ^= ((byte *) buf)[i-1];
    }
}

//__declspec(noinline) 
void ZeusDecrypt(const void *ct, void *pt, int len)
{
    ((byte *) pt)[0] = ((byte *) ct)[0];
    for (int i = len - 1; i > 0; i--) {
        ((byte *) pt)[i] = ((byte *) ct)[i-1] ^ ((byte *) ct)[i];
    }
}

void ZeusTest( char *buf, int len )
{
    char dec[256];
    ZeusDecrypt(buf, dec, len);
    dec[len] = 0;

    printf("message is: %s (%d)\n", dec + 1, len);
    dec[6] = 0;
    printf("submessage is: %s\n", dec);
}
