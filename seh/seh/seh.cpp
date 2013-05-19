// seh.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int ExceptionHandler(int code, PEXCEPTION_POINTERS p)
{
    printf("Code = %08x\n", code);
    printf("EIP = %08x\n", p->ContextRecord->Eip);
    return EXCEPTION_EXECUTE_HANDLER;
}


int _tmain(int argc, _TCHAR* argv[])
{
    int a = 0;
    int b = a*2;
    __try {
        a /= b;
        printf("okay! a=%d\n", a);
    } __except(ExceptionHandler(_exception_code(), (PEXCEPTION_POINTERS) _exception_info())) {
    }
	return 0;
}

