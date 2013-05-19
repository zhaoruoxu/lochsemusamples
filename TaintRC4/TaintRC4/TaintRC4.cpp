// TaintRC4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#pragma data_seg(push, stack1, ".taintd")
char Key[] = "Key";
#pragma data_seg(pop, stack1)

typedef unsigned char byte;

byte S[256];

const char pt[] = "Plaintext";

void KeySchedule(const char *key, int n)
{
    for (int i = 0; i < 256; i++)
        S[i] = i;
    byte j = 0;
    for (int i = 0; i < 256; i++) {
        j += S[i] + (byte) key[i % n];
        //std::swap(S[i], S[j]);
        byte t = S[i];
        S[i] = S[j];
        S[j] = t;
    }
}

byte Gen(byte &i, byte &j)
{
    i++;
    j += S[i];
    //std::swap(S[i], S[j]);
    byte t = S[i];
    S[i] = S[j];
    S[j] = t;
    return S[(S[i] + S[j]) & 0xff];
}

int _tmain(int argc, _TCHAR* argv[])
{
    KeySchedule(Key, strlen(Key));
    
    byte i = 0, j = 0;
    
    for (int n = 0; n < strlen(pt); n++) {
        byte val = pt[i] ^ Gen(i, j);
        printf("%02x ", val);
    }
	return 0;
}

