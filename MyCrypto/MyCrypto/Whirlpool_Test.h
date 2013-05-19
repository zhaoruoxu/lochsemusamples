#pragma once
#ifndef WHIRLPOOL_TEST_H
#define WHIRLPOOL_TEST_H

#include "stdafx.h"
#include "MyCrypto.h"
#include <openssl/whrlpool.h>

#define WHIRLPOOL_FILE_BUFFER_SIZE      4096
#define WHIRLPOOL_INPUT_FILE_NAME       ("Whirlpool_Input.txt")

extern void Whirlpool_Test();

#endif // WHIRLPOOL_TEST_H