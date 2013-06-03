#pragma once
 
#ifndef __TAINTFORMAT_COMMON_H__
#define __TAINTFORMAT_COMMON_H__
 
typedef unsigned char byte;
typedef byte * pbyte;
typedef const byte * cpbyte;

#define BUF_LEN 1024
 
char * __cdecl MyStrStr (
    const char * str1,
    const char * str2
    );

int CompareByteArray( cpbyte l, cpbyte r, int n );

#endif // __TAINTFORMAT_COMMON_H__