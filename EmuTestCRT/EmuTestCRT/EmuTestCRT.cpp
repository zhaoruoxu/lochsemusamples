// EmuTestCRT.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

double func(double x) {
    return x+1;
}

int _tmain(int argc, _TCHAR* argv[])
{
    printf("HELLO, LOCHSEMU!\n");
    long double x = 10;

    double y = func(2);
    
    printf("%d\n", sizeof(long double));
	return 0;
}

