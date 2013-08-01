#include "stdafx.h"
#include "des_modes_test.h"
#include "common.h"
#include <openssl/des.h>

static const char *Motto = "Talk is cheap. Show me the code.";
static const char *SecretKey = "abcdefgh";
static const char *IV = "wwwwwwww";
static const int Length = 40;

void DES_CBC_GenerateServerContent()
{
    DES_cblock key, iv;
    ZeroMemory(&key, sizeof(DES_cblock));
    ZeroMemory(&iv, sizeof(DES_cblock));
    strncpy((char *) &key, SecretKey, sizeof(DES_cblock));
    strncpy((char *) &iv, IV, sizeof(DES_cblock));
    DES_key_schedule schedule;
    DES_set_odd_parity(&key);
    DES_set_key_checked(&key, &schedule);

    byte out[Length];
    ZeroMemory(out, sizeof(out));

    DES_cbc_encrypt((cpbyte) Motto, out, Length, &schedule, &iv, DES_ENCRYPT);

    PrintHexString(out, Length);

    byte dec[Length];
    ZeroMemory(dec, sizeof(dec));
    DES_cbc_encrypt(out, dec, Length, &schedule, &iv, DES_DECRYPT);
    printf("dec = %s\n", dec);
}

void DES_CFB_GenerateServerContent()
{
    DES_cblock key, iv;
    ZeroMemory(&key, sizeof(DES_cblock));
    ZeroMemory(&iv, sizeof(DES_cblock));
    strncpy((char *) &key, SecretKey, sizeof(DES_cblock));
    strncpy((char *) &iv, IV, sizeof(DES_cblock));
    DES_key_schedule schedule;
    DES_set_odd_parity(&key);
    DES_set_key_checked(&key, &schedule);

    byte out[Length];
    ZeroMemory(out, sizeof(out));

    DES_cfb_encrypt((cpbyte) Motto, out, 1, Length, &schedule, &iv, DES_ENCRYPT);

    PrintHexString(out, Length);

    strncpy((char *) &iv, IV, sizeof(DES_cblock));
    byte dec[Length];
    ZeroMemory(dec, sizeof(dec));
    DES_cfb_encrypt(out, dec, 1, Length, &schedule, &iv, DES_DECRYPT);
    printf("dec = %s\n", dec);
}

void DesCBCTest( char *buf, int len )
{
    if (buf == NULL) {
        DES_CBC_GenerateServerContent();
        return;
    }

    if (len != Length) {
        printf("DES CBC length error\n");
        return;
    }

    DES_cblock key, iv;
    ZeroMemory(&key, sizeof(DES_cblock));
    ZeroMemory(&iv, sizeof(DES_cblock));
    strncpy((char *) &key, SecretKey, sizeof(DES_cblock));
    strncpy((char *) &iv, IV, sizeof(DES_cblock));
    DES_key_schedule schedule;
    DES_set_odd_parity(&key);
    DES_set_key_checked(&key, &schedule);


    byte out[Length];
    ZeroMemory(out, sizeof(out));

    DES_cbc_encrypt((cpbyte) buf, out, Length, &schedule, &iv, DES_DECRYPT);

    printf("DES CBC decrypt: %s\n", out);
}

void DesCFBTest( char *buf, int len )
{
    if (buf == NULL) {
        DES_CFB_GenerateServerContent();
        return;
    }

    if (len != Length) {
        printf("DES CFB length error\n");
        return;
    }

    DES_cblock key, iv;
    ZeroMemory(&key, sizeof(DES_cblock));
    ZeroMemory(&iv, sizeof(DES_cblock));
    strncpy((char *) &key, SecretKey, sizeof(DES_cblock));
    strncpy((char *) &iv, IV, sizeof(DES_cblock));
    DES_key_schedule schedule;
    DES_set_odd_parity(&key);
    DES_set_key_checked(&key, &schedule);


    byte out[Length];
    ZeroMemory(out, sizeof(out));

    DES_cfb_encrypt((cpbyte) buf, out, 1, Length, &schedule, &iv, DES_DECRYPT);

    printf("DES CFB decrypt: %s\n", out);
}
