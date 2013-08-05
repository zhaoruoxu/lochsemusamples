#include "stdafx.h"
#include "festi.h"
#include "common.h"

__declspec(noinline) 
void Festi_crypt(const byte *in, byte *out, int len)
{
    static byte key[4] = { 0x17, 0xfb, 0x71, 0x5c };
    for (int i = 0; i < len; i++) {
        out[i] = in[i] ^ key[i % 4];
    }
}

void Festi_GenerateServerInput()
{
    char in[256], out[256];
    const char *s = "In religion, a prophet is an individual who is claimed to have been contacted by the supernatural or the divine.";
    in[0] = 0xe2; in[1] = 0x36;
    strcpy(in + 2, s);
    in[3+strlen(s)] = 0xab;
    in[4+strlen(s)] = 0xdc;

    int l = 2 + strlen(s) + 3;
    Festi_crypt((const byte *) in, (byte *) out, l);

    for (int i = 0; i < l; i++)
        printf("\\x%02x", (byte) out[i]);
    printf("\n");
    Festi_crypt((const byte *) out, (byte *) out, l);

    printf("s=%s\n", out + 2);
}

void FestiTest( char *buf, int len )
{
    if (buf == NULL) {
        Festi_GenerateServerInput();
        return;
    }

    byte decbuf[256];
    ZeroMemory(decbuf, sizeof(decbuf));
    Festi_crypt((const byte *) buf, decbuf, len);

    if (reinterpret_cast<unsigned short *>(decbuf)[0] != 0x36e2) {
        printf("tag incorrect\n");
    }
    printf("s = %s\n", (char *) decbuf + 2);
    if (reinterpret_cast<unsigned short *>(decbuf + 3 + strlen((char *) decbuf + 2))[0]
        != 0xdcab) 
    {
        printf("term incorrect\n");
    }
}
