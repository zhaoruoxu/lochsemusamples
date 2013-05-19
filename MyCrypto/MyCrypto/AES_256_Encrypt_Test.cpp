#include "AES_256_Encrypt_Test.h"

void AES_256_Encrypt_Test()
{
    unsigned char aes_input[] = "aes 256-bit encryption test data";
    unsigned char aes_output[AES_BLOCK_SIZE];
    memset(aes_output, 0, sizeof(unsigned char) * AES_BLOCK_SIZE);

    AES_KEY aes_key;
    unsigned char keytest[]   = "aes256testkey256hahahohohehehuhuhaha";

    AES_set_encrypt_key(keytest, 256, &aes_key);
    AES_encrypt(aes_input, aes_output, &aes_key);

    printf("AES 256-bit encrypt:\n");
    OutputHexString( aes_output, AES_BLOCK_SIZE );
    printf("\n");
}