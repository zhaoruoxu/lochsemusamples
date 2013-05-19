#include "SHA1_Test.h"

void SHA1_Test()
{
    SHA_CTX ctx;
    char buf[SHA1_FILE_BUFFER_SIZE];
    unsigned char md[SHA_DIGEST_LENGTH];
    DWORD dwBytesRead;

    HANDLE hFile = CreateFileA( SHA1_INPUT_FILE_NAME, GENERIC_READ, FILE_SHARE_READ,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

    if ( INVALID_HANDLE_VALUE == hFile ) {
        printf( "Could not open %s\n", SHA1_INPUT_FILE_NAME );
        return;
    }

    SHA1_Init( &ctx );
    while ( ReadFile( hFile, buf, SHA1_FILE_BUFFER_SIZE, &dwBytesRead, NULL ) 
        && (dwBytesRead > 0) ) {
        SHA1_Update( &ctx, buf, dwBytesRead );
    }
    SHA1_Final( md, &ctx );

    printf( "SHA1 hash: " );
    OutputHexString( md, SHA_DIGEST_LENGTH );
    printf( "\n" );
}