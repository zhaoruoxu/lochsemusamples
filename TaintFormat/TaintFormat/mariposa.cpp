#include "stdafx.h"
#include "mariposa.h"
#include "common.h"

__declspec(noinline) 
void Mariposa_crypt(const byte *in, byte *out, int len)
{
    byte not = ~(unsigned char) len;
    byte xor[2];
    xor[0] = not ^ in[0];
    xor[1] = not ^ in[1];
    int alt = 0;
    out[0] = in[0]; out[1] = in[1];
    for (int i = 2; i < len; i++) {
        out[i] = in[i] ^ xor[alt];
        alt ^= 1;
    }
}

void Mariposa_GenerateServerInput()
{
    char in[256];
    ZeroMemory(in, sizeof(in));
    const char *s = "In religion, a prophet is an individual who is claimed to have been contacted by the supernatural or the divine.";
    sprintf(in, "\x01\x07\x03\x14%s", s);
    int len = strlen(s) + 1;
    Mariposa_crypt((const byte *) in + 3, (byte *) in + 3, len);

    for (int i = 0; i < len + 3; i++)
        printf("\\x%02x", (byte) in[i]);
    printf("\n");

    Mariposa_crypt((const byte *) in + 3, (byte *) in + 3, len);
    printf("s = %s\n", (char *) in + 4);

}

void MariposaTest( char *buf, int len )
{
    if (buf == NULL) {
        Mariposa_GenerateServerInput();
        return;
    }

    byte decbuf[256];
    ZeroMemory(decbuf, sizeof(decbuf));
    //memcpy(decbuf, buf, 3);
    decbuf[0] = buf[0]; decbuf[1] = buf[1]; decbuf[2] = buf[2];
    Mariposa_crypt((const byte *) buf + 3, decbuf + 3, len - 3);
    if (decbuf[0] != 0x01 || decbuf[1] != 0x07 || decbuf[2] != 0x03) {
        printf("mariposa fucking error\n");
    }
    if (decbuf[3] != 0x14) {
        printf("mariposa fucking type error\n");
    }
    printf("mariposa = %s\n", decbuf + 4);
}
