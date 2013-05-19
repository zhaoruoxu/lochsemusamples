#pragma once
#ifndef SHA256_TEST_H
#define SHA256_TEST_H

#include "stdafx.h"

#include "MyCrypto.h"
#include <openssl/sha.h>

#define SHA256_FILE_BUFFER_SIZE     4096
#define SHA256_INPUT_FILE_NAME      ("SHA256_Input.txt")

extern void SHA256_Test();

#endif // SHA256_TEST_H