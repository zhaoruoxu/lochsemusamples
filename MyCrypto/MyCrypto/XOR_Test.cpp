#include "XOR_Test.h"

static void Xor(const unsigned char lhs[], const unsigned char rhs[],
                unsigned char result[], int n)
{
    for ( int i = 0; i < n; i++ ) {
        result[i] = lhs[i] ^ rhs[i];
    }
}

void XOR_Test()
{
    unsigned char data1[XOR_TEST_LENGTH_BYTE];
    unsigned char data2[XOR_TEST_LENGTH_BYTE];

    unsigned char result[XOR_TEST_LENGTH_BYTE];

    for ( int i = 0; i < XOR_TEST_LENGTH_BYTE; i++ ) {
        data1[i] = (unsigned char) (i + 2);
        data2[i] = (unsigned char) (i * 3);
    }

    Xor( data1, data2, result, XOR_TEST_LENGTH_BYTE );

    printf("XOR data 1:\n");
    OutputHexString(data1, XOR_TEST_LENGTH_BYTE);
    printf("\nXOR data 2:\n");
    OutputHexString(data2, XOR_TEST_LENGTH_BYTE);
    printf("\nXORed:\n");
    OutputHexString(result, XOR_TEST_LENGTH_BYTE);
    printf("\n");
}