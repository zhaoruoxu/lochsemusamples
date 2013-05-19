#include "RC4_Test.h"

#define RC4_LENGTH          32

void RC4_Test()
{
    unsigned char rc4_key[] = "RC4TestKey";
    unsigned char rc4_plaintext[] = "RC4 plain text";
    unsigned char rc4_ciphertext[RC4_LENGTH];
    memset( rc4_ciphertext, 0, sizeof(unsigned char) * RC4_LENGTH );

    RC4_KEY key;
    RC4_set_key( &key, strlen((const char *) rc4_key), rc4_key );

    RC4( &key, strlen((const char *) rc4_plaintext), rc4_plaintext, rc4_ciphertext );

    printf("RC4 encrypt:\n");
    printf("Plain text: \n");
    OutputHexString( rc4_plaintext, strlen((const char *) rc4_plaintext));
    printf("\nCipher text:\n");
    OutputHexString( rc4_ciphertext, RC4_LENGTH );
    printf("\n");
}