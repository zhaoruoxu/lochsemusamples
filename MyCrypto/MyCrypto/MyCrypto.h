#pragma once

#ifndef MYCRYPTO_H
#define MYCRYPTO_H

#include "stdafx.h"

#pragma warning( disable : 4996 )

typedef void ( *MyCryptoTestFunc ) ( void );

struct MyCryptoTest {
    string name;
    MyCryptoTestFunc func;

    MyCryptoTest( const char *n, MyCryptoTestFunc f ) {
        name = string( n );
        func = f;
    }
};

void OutputHexString( const unsigned char *data, int n );

#endif // MYCRYPTO_H