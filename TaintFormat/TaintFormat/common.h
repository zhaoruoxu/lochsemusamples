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
bool StrPrefix(const char *str, const char *prefix);
unsigned long Crc32_ComputeBuf( unsigned long inCrc32, const void *buf, size_t bufLen );
void PrintHexString(cpbyte dat, int len);

#endif // __TAINTFORMAT_COMMON_H__