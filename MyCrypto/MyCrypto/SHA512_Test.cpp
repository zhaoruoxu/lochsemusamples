#include "SHA512_Test.h"
#include "openssl/whrlpool.h"
void SHA512_Test() 
{
    SHA512_CTX ctx;
    char buf[SHA512_FILE_BUFFER_SIZE];
    unsigned char md[SHA512_DIGEST_LENGTH];
    DWORD dwBytesRead;

    HANDLE hFile = CreateFileA( SHA512_INPUT_FILE_NAME, GENERIC_READ, FILE_SHARE_READ,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

    if ( INVALID_HANDLE_VALUE == hFile ) {
        printf( "Could not open %s\n", SHA512_INPUT_FILE_NAME );
        return;
    }

    SHA512_Init( &ctx );
    while ( ReadFile( hFile, buf, SHA512_FILE_BUFFER_SIZE, &dwBytesRead, NULL ) 
        && (dwBytesRead > 0)) {
        SHA512_Update( &ctx, buf, dwBytesRead );
    }
    SHA512_Final( md, &ctx );

    printf( "SHA512 hash: " );
    OutputHexString( md, SHA512_DIGEST_LENGTH );
    printf( "\n" );
}
