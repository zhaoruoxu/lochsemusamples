// myssl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#pragma warning(disable: 4996)
#include <openssl/applink.c>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

void RunClient();
void RunClientUnencrypted();

int _tmain(int argc, _TCHAR* argv[])
{
    OPENSSL_ia32cap &= ~(1 << 26);
    OPENSSL_ia32cap &= ~(1 << 25);
    OPENSSL_ia32cap &= ~(1 << 23);

    CRYPTO_malloc_init();
    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();

    RunClient();

	return 0;
}

void RunClientUnencrypted()
{
    BIO *bio = BIO_new_connect("loccs.sjtu.edu.cn:80");
    if (NULL == bio) {
        printf("Error creating BIO!\n");
        ERR_print_errors_fp(stderr);
        return;
    }

    if (BIO_do_connect(bio) <= 0) {
        printf("Failed to connect!\n");
        return;
    }

    char buf[1024];
    ZeroMemory(buf, sizeof(buf));

    char send[1024];
    ZeroMemory(send, sizeof(send));

    strcat(send, "GET / HTTP/1.1\nHost:bbs.sjtu.edu.cn\nUser Agent: Mozilla/5.0 " \
        "(compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0)\nConnection: Close\n\n");

    BIO_puts(bio, send);
    while (true) {
        int x = BIO_read(bio, buf, sizeof(buf) - 1);
        if (x == 0) break;

        if (x < 0) {
            if (!BIO_should_retry(bio)) {
                printf("\nRead Failed\n");
                BIO_free_all(bio);
                return;
            }
        }

        buf[x] = 0;
        printf("%s", buf);
    }
}

void RunClient()
{
    SSL_CTX *ctx = SSL_CTX_new(SSLv23_client_method());
    SSL *ssl;
    BIO *bio = BIO_new_ssl_connect(ctx);

    if (NULL == bio) {
        printf("error creating BIO\n");
        ERR_print_errors_fp(stderr);
        SSL_CTX_free(ctx);
        return;
    }

    BIO_get_ssl(bio, &ssl);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
    BIO_set_conn_hostname(bio, "bbs.sjtu.edu.cn:https");

    if (BIO_do_connect(bio) <= 0) {
        printf("failed to connect\n");
        BIO_free_all(bio);
        SSL_CTX_free(ctx);
        return;
    }

    if (BIO_do_handshake(bio) <= 0) {
        printf("Failed to do SSL handshake\n");
        BIO_free_all(bio);
        SSL_CTX_free(ctx);
        return;
    }

    char buf[1024];
    ZeroMemory(buf, sizeof(buf));
    char send[1024];
    ZeroMemory(send, sizeof(send));

    strcat(send, "GET /file/bbs/index/index.htm HTTP/1.1\nHost:bbs.sjtu.edu.cn\nUser Agent: Mozilla/5.0 "
        "(compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0)\nConnection: Close\n\n");

    BIO_puts(bio, send);
    while (true) {
        int x = BIO_read(bio, buf, sizeof(buf) - 1);
        if (x == 0) break;
        if (x < 0) {
            if (!BIO_should_retry(bio)) {
                printf("read failed\n");
                BIO_free_all(bio);
                SSL_CTX_free(ctx);
                return;
            }
        }
        buf[x] = 0;
        printf("%s", buf);
    }

    BIO_free_all(bio);
    SSL_CTX_free(ctx);
}