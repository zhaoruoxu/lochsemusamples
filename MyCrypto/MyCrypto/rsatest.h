#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __rsatest_h__
#define __rsatest_h__

#include "MyCrypto.h"
#include <openssl/pem.h>
#include <openssl/rsa.h>

#define RSA_KEY_LENGTH      1024

void RSATest();

#endif // __rsatest_h__
