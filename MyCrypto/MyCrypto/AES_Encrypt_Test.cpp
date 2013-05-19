#include "AES_Encrypt_Test.h"

void AES_Encrypt_Test()
{
    unsigned char aes_input[] = "aes 128-bit encryption test data";
    unsigned char aes_output[AES_BLOCK_SIZE];
    memset(aes_output, 0, sizeof(unsigned char) * AES_BLOCK_SIZE );

    AES_KEY aes_enc_key;

    unsigned char ckey[16] = "aes128testkey";

    AES_set_encrypt_key(ckey, 128, &aes_enc_key);
    AES_encrypt(aes_input, aes_output, &aes_enc_key);

    printf( "AES 128-bit Encrypt: " );
    OutputHexString( aes_output, AES_BLOCK_SIZE );
    printf( "\n" );
}