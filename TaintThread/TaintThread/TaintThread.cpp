// TaintThread.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

DWORD WINAPI MyThread(LPVOID lpParam)
{
    printf("I'm from thread\n");

    ExitThread(6);
    return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) &MyThread, NULL, 0, NULL);
    
    Sleep(1);
    printf("I'm from main\n");
    WaitForSingleObject(hThread, INFINITE);
	return 0;
}

