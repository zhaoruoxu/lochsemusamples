
#include "MD5_Test.h"

void MD5_Test() 
{
    MD5_CTX ctx;
    char buf[MD5_FILE_BUFFER_SIZE];
    unsigned char md[MD5_DIGEST_BYTES];
    DWORD dwBytesRead;

    HANDLE hFile = CreateFileA( MD5_INPUT_FILE_NAME, GENERIC_READ, FILE_SHARE_READ,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

    if ( INVALID_HANDLE_VALUE == hFile ) {
        printf( "Could not open %s\n", MD5_INPUT_FILE_NAME );
        return;
    }

    MD5_Init( &ctx );
    while ( ReadFile( hFile, buf, MD5_FILE_BUFFER_SIZE, &dwBytesRead, NULL ) 
        && dwBytesRead > 0 ) {
            MD5_Update( &ctx, buf, dwBytesRead );
    }

    MD5_Final( md, &ctx );

    printf( "MD5 hash: " );
    OutputHexString( md, MD5_DIGEST_BYTES );
    printf( "\n" );
}