#pragma once
 
#ifndef __TAINTFORMAT_RC4TEST_H__
#define __TAINTFORMAT_RC4TEST_H__
 
void RC4Crypt(char *dest, const char *src, int n, const char *key, int keylen);
void RC4Test(char *buf, int len);
 
#endif // __TAINTFORMAT_RC4TEST_H__