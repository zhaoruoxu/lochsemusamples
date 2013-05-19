#include "Blowfish_Test.h"

void Blowfish_Encrypt_Test()
{
    unsigned char key[8];
    memset( key, 0, 8 );
    unsigned int pt[2] = {0x0, 0x0};

    BF_KEY bf_key;
    BF_set_key( &bf_key, 8, key );
    BF_encrypt( pt, &bf_key );

    printf( "Blowfish encrypt:\n" );
    OutputHexString( (const unsigned char *) pt, 8 );
    printf( "\n" );
}