#pragma once
#ifndef SHA1_TEST_H
#define SHA1_TEST_H

#include "stdafx.h"

#include "MyCrypto.h"
#include <openssl/sha.h>

#define SHA1_FILE_BUFFER_SIZE   4096
#define SHA1_INPUT_FILE_NAME    ("SHA1_Input.txt")

extern void SHA1_Test();

#endif // SHA1_TEST_H