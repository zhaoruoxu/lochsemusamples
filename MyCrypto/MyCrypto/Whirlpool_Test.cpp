#include "Whirlpool_Test.h"

void Whirlpool_Test()
{
    WHIRLPOOL_CTX ctx;
    char buf[WHIRLPOOL_FILE_BUFFER_SIZE];
    unsigned char md[WHIRLPOOL_DIGEST_LENGTH];
    DWORD dwBytesRead;

    HANDLE hFile = CreateFileA( WHIRLPOOL_INPUT_FILE_NAME, GENERIC_READ, FILE_SHARE_READ, 
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

    if ( INVALID_HANDLE_VALUE == hFile ) {
        printf( "Could not open %s\n", WHIRLPOOL_INPUT_FILE_NAME );
        return;
    }

    WHIRLPOOL_Init( &ctx );
    while ( ReadFile( hFile, buf, WHIRLPOOL_FILE_BUFFER_SIZE, &dwBytesRead, NULL )
        && (dwBytesRead > 0)) {
        WHIRLPOOL_Update( &ctx, buf, dwBytesRead );
    }
    WHIRLPOOL_Final( md, &ctx );

    printf( "Whirlpool hash: " );
    OutputHexString( md, WHIRLPOOL_DIGEST_LENGTH );
    printf( "\n" );
}