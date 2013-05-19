// MyCrypto.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "MyCrypto.h"
#include "MD5_Test.h"
#include "SHA1_Test.h"
#include "SHA256_Test.h"
#include "SHA512_Test.h"
#include "Whirlpool_Test.h"
#include "AES_Encrypt_Test.h"
#include "XOR_Test.h"
#include "Sort_Test.h"
#include "AES_256_Encrypt_Test.h"
#include "RC4_Test.h"
#include "Blowfish_Test.h"
#include "rsatest.h"

void OutputHexString( const unsigned char *data, int n );
void RunTest( const vector<MyCryptoTest> &tests );
void InitTest( vector<MyCryptoTest> &tests );

void OutputHexString( const unsigned char *data, int n )
{
    for ( int i = 0; i < n; i++ ) {
        printf( "%02X", data[i] );
        if ( i % 4 == 3 ) printf( " " );
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    vector<MyCryptoTest> tests;

    InitTest( tests );
    RunTest( tests );

	return 0;
}

void InitTest( vector<MyCryptoTest> &tests )
{
    tests.push_back( MyCryptoTest( "MD5 hash", MD5_Test ) );
    tests.push_back( MyCryptoTest( "SHA1 hash", SHA1_Test ) );
    tests.push_back( MyCryptoTest( "SHA256 hash", SHA256_Test ) );
    tests.push_back( MyCryptoTest( "SHA512 hash", SHA512_Test ) );
    tests.push_back( MyCryptoTest( "Whirlpool hash", Whirlpool_Test ) );
    tests.push_back( MyCryptoTest( "AES 128 encrypt", AES_Encrypt_Test ) );
    tests.push_back( MyCryptoTest( "XOR", XOR_Test ) );
    tests.push_back( MyCryptoTest( "Sort", Sort_Test ) );
    tests.push_back( MyCryptoTest( "AES 256 encrypt", AES_256_Encrypt_Test ) );
    tests.push_back( MyCryptoTest( "RC4 encrypt", RC4_Test ) );
    tests.push_back( MyCryptoTest( "Blowfish encrypt", Blowfish_Encrypt_Test ) );
    tests.push_back( MyCryptoTest( "RSA test", RSATest) );
}

void RunTest( const vector<MyCryptoTest> &tests )
{
    printf( "Select a test to run:\n" );
    for ( unsigned testIndex = 0; testIndex < tests.size(); testIndex++ ) {
        printf( "[%d] %s\n", testIndex, tests[testIndex].name.c_str() );
    }
    int testNr;
    char buf[256];
    gets( buf );
    sscanf( buf, "%d", &testNr );

    if ( testNr < 0 || testNr >= (int) tests.size() ) {
        printf( "Invalid test\n" );
        return;
    }

    tests[testNr].func();
}

