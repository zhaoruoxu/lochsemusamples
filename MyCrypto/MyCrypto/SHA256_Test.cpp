#include "SHA256_Test.h"

void SHA256_Test()
{
    SHA256_CTX ctx;
    char buf[SHA256_FILE_BUFFER_SIZE];
    unsigned char md[SHA256_DIGEST_LENGTH];
    DWORD dwBytesRead;

    HANDLE hFile = CreateFileA( SHA256_INPUT_FILE_NAME, GENERIC_READ, FILE_SHARE_READ,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if ( INVALID_HANDLE_VALUE == hFile ) {
        printf( "Could not open %s\n", SHA256_INPUT_FILE_NAME );
        return;
    }

    SHA256_Init( &ctx );
    while ( ReadFile( hFile, buf, SHA256_FILE_BUFFER_SIZE, &dwBytesRead, NULL )
        && (dwBytesRead > 0) ) {
        SHA256_Update( &ctx, buf, dwBytesRead );
    }
    SHA256_Final( md, &ctx );

    printf( "SHA256 hash: " );
    OutputHexString( md, SHA256_DIGEST_LENGTH );
    printf( "\n" );
}