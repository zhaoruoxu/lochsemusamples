// TaintCipher.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


static const unsigned char Key[] = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
};

static const int BufLen = 16;

#pragma data_seg(push, stack1, ".taintp")
unsigned char Text[BufLen] = "Hello Prophet!";
#pragma data_seg(pop, stack1)

unsigned char Encrypted[BufLen];
unsigned char Decrypted[BufLen];

void PrintHex(unsigned char *buf, int len)
{
    for (int i = 0; i < len; i++) {
        printf("%02x", buf[i]);
        if (i % 16 == 15)
            printf("\n");
        else if (i % 4 == 3)
            printf(" ");
    }
    printf("\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
    ZeroMemory(Encrypted, BufLen);
    ZeroMemory(Decrypted, BufLen);

    AES_KEY keyenc, keydec;

    AES_set_encrypt_key(Key, 128,  &keyenc);
    AES_encrypt(Text, Encrypted, &keyenc);

    PrintHex(Text, BufLen);
    PrintHex(Encrypted, BufLen);

    AES_set_decrypt_key(Key, 128, &keydec);
    AES_decrypt(Encrypted, Decrypted, &keydec);

    PrintHex(Decrypted, BufLen);

	return 0;
}

