// AnalyzeRC4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void RC4KeySchedule(unsigned int *S, unsigned int *key, int len)
{
    for (unsigned i = 0; i < 256; i++)
        S[i] = i;

    unsigned int j = 0;
    for (unsigned i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % len]) & 0xff;

        unsigned int temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
}


void Print(unsigned int *S, int len)
{
    for (int i = 0; i < len; i++)
        printf("%02x ", S[i]);
    printf("\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
    if (argc == 2) {
        wprintf(L"command line is: %s\n", argv[1]);
    }
    unsigned int key[] = {'R', 'C', '4', 'T', 'e', 's', 't', 'K', 'e', 'y'};
    //unsigned int key[] = {'K', 'e', 'y', 0};
    unsigned int S[256] = {0};
    RC4KeySchedule(S, key, sizeof(key)/sizeof(unsigned int));
    //GenerateRC4SBox(key, 5, S);
    Print(S, 256);

	return 0;
}

