// TaintTest1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


/*
#define TAINT_CODE_BEGIN()  __asm __emit 0xeb __asm __emit 0x04 __asm __emit 0x65 __asm __emit 0x92 __asm __emit 0x15 __asm __emit 0x14
#define TAINT_CODE_END()    __asm __emit 0xeb __asm __emit 0x04 __asm __emit 0x14 __asm __emit 0x15 __asm __emit 0x92 __asm __emit 0x65
#define DO_TAINT()    __asm __emit 0xeb __asm __emit 0x04 __asm __emit 0xcf __asm __emit 0xca __asm __emit 0xed __asm __emit 0xf1


#pragma data_seg(push, stack1, ".taintd")
char buf[256] = "\0";
#pragma data_seg(pop, stack1)

static const char *MyString = "show me the code";


void ProcessMessage()
{
    char tempbuf[256];
    memset(tempbuf, 0, 256);
    int len = reinterpret_cast<int *>(buf)[0];
    for (int i = 0; i < len; i++) {
        tempbuf[i] = buf[4+i];
    }
    //memcpy(tempbuf, buf+4, len);
    tempbuf[len] = '\0';
    printf("message = %s\n", tempbuf);
}


int _tmain(int argc, _TCHAR* argv[])
{
    reinterpret_cast<unsigned *>(buf)[0] = strlen(MyString);
    strcpy(buf+4, MyString);

    DO_TAINT()

    ProcessMessage();

	return 0;
}

*/

int _tmain(int argc, _TCHAR* argv[])
{
    HANDLE hInput   = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hOutput  = GetStdHandle(STD_OUTPUT_HANDLE);

    char buf[256] = "hello, world!";
    DWORD dwBytesRead;

    printf("Input some text:\n");
    if (ReadFile(hInput, buf, 256, &dwBytesRead, NULL) == FALSE) {
        printf("ReadFile() failed\n");
        return -1;
    }

    buf[dwBytesRead] = '\0';

    DWORD dwBytesWritten;
    if (WriteFile(hOutput, buf, dwBytesRead, &dwBytesWritten, NULL) == FALSE) {
        printf("WriteFile() failed\n");
        return -1;
    }

    return 0;
}