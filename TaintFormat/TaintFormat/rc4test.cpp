#include "stdafx.h"


void KeySchedule(byte *S, const char *key, int n)
{
    for (int i = 0; i < 256; i++)
        S[i] = i;
    byte j = 0;
    for (int i = 0; i < 256; i++) {
        j += S[i] + (byte) key[i % n];
        std::swap(S[i], S[j]);
        //         byte t = S[i];
        //         S[i] = S[j];
        //         S[j] = t;
    }
}

byte Gen(byte *S, byte &a, byte &b)
{
    a++;
    b += S[a];
    std::swap(S[a], S[b]);
    return S[(S[a] + S[b]) & 0xff];
}

void RC4Crypt(char *dest, const char *src, int n, const char *key, int keylen)
{
    byte S[256];
    KeySchedule(S, key, keylen);

    byte a = 0, b = 0;
    for (int i = 0; i < n; i++) {
        dest[i] = src[i] ^ Gen(S, a, b);
    }
}

static const char *Key = "gossip";
void RC4Test( char *buf, int len )
{
    int l = reinterpret_cast<int *>(buf)[0];
    char dec[256];
    RC4Crypt(dec, buf + 4, l, Key, strlen(Key));
    dec[l] = 0;

    printf("Message: %s\n", dec);

    char *p = strtok(dec, " ");
    while (p) {
        printf("# %s\n", p);
        p = strtok(NULL, " ");
    }
}
