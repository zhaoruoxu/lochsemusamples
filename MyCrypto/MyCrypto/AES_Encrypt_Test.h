#pragma once
#ifndef AES_ENCRYPT_TEST_H
#define AES_ENCRYPT_TEST_H

#include "stdafx.h"

#include "MyCrypto.h"
#include <openssl/aes.h>

#define AES_ENCRYPT_FILE_BUFFER_SIZE    4096
#define AES_ENCRYPT_INPUT_FILE_NAME     ("AES_Encrypt_Input.txt")

extern void AES_Encrypt_Test();

#endif // AES_ENCRYPT_TEST_H