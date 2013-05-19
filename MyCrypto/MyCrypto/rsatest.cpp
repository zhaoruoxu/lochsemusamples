#include "stdafx.h"
#include "rsatest.h"

#include <openssl/applink.c>

#define RSA_TEXT        "01234567"

void RSATest()
{
    RSA *key = NULL;
    BIO *bio_sec = NULL;
    BIO *bio_pub = NULL;
    FILE *fp_sec = NULL;
    FILE *fp_pub = NULL;
    fopen_s(&fp_sec, "sec.pem", "r");
    fopen_s(&fp_pub, "pub.pem", "r");
    bio_sec = BIO_new_fp(fp_sec, BIO_CLOSE);
    bio_pub = BIO_new_fp(fp_pub, BIO_CLOSE);

    if (!bio_sec || !bio_pub) {
        printf("fucked BIO_new_file\n");
        return;
    }

    if (!PEM_read_bio_RSAPrivateKey(bio_sec, &key, NULL, "")) {
        printf("fucked PEM_read_bio_RSAPrivateKey\n");
        return;
    }

    if (!PEM_read_bio_RSAPublicKey(bio_pub, &key, NULL, "")) {
        printf("fucked PEM_read_bio_RSAPublicKey\n");
        return;
    }

    int len = RSA_size(key);
    unsigned char *buf = new unsigned char[len];
    memset(buf, 0, len);

    if (-1 == RSA_private_encrypt(strlen(RSA_TEXT), (const unsigned char *)RSA_TEXT, buf, key, RSA_PKCS1_PADDING) ) {
        printf("fucked RSA_private_encrypt\n");
        return;
    }

    OutputHexString(buf, len);
    printf("\n");


    /*
    unsigned char *buf_test = new unsigned char[len];
    memset(buf_test, 0, len);

    if (-1 == RSA_public_decrypt(len, buf, buf_test, key, RSA_PKCS1_PADDING) ) {
        printf("fucked RSA_public_decrypt\n");
        return;
    }

    OutputHexString(buf_test, strlen(RSA_TEXT));
    printf("\n");
    delete [] buf_test;
    */

    delete [] buf;
    

    BIO_free(bio_sec);

}