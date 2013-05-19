#pragma once
#ifndef SHA512_TEST_H
#define SHA512_TEST_H

#include "stdafx.h"

#include "MyCrypto.h"
#include <openssl/sha.h>

#define SHA512_FILE_BUFFER_SIZE     4096
#define SHA512_INPUT_FILE_NAME      ("SHA512_Input.txt")

extern void SHA512_Test();

#endif // SHA512_TEST_H