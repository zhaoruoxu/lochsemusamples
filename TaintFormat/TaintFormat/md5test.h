#pragma once
 
#ifndef __TAINTFORMAT_MD5TEST_H__
#define __TAINTFORMAT_MD5TEST_H__
 
#include "common.h"

void MD5Hash(cpbyte d, int n, pbyte md);
void MD5Test(char *buf, int len);
 
#endif // __TAINTFORMAT_MD5TEST_H__