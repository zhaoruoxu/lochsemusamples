#pragma once
 
#ifndef __TAINTFORMAT_DES_MODES_TEST_H__
#define __TAINTFORMAT_DES_MODES_TEST_H__

void DesCBCTest(char *buf, int len);
void DesCFBTest(char *buf, int len);

#endif // __TAINTFORMAT_DES_MODES_TEST_H__