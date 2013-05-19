#pragma once
#ifndef MD5_TEST_H
#define MD5_TEST_H

#include "stdafx.h"

#include "MyCrypto.h"
#include <openssl/md5.h>

#define MD5_FILE_BUFFER_SIZE    4096
#define MD5_DIGEST_BYTES        16
#define MD5_INPUT_FILE_NAME     ("MD5_Input.txt")

extern void MD5_Test();


#endif // MD5_TEST_H