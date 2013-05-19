// TaintTest0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#include "taint.h"
//
//#pragma data_seg(push, stack1, ".taintd")
//char buf[64] = "\x04\x00\x00\x00abce";
//#pragma data_seg(pop, stack1)
//
//void Shellcode();
//
//void StringCopy(char *dest, const char *src)
//{
//    strcpy(dest, src);
//}
//
//void print(const char *str)
//{
//    char buf[16];
//    memset(buf, 0xcc, 16);
//
//    StringCopy(buf, str);
//    printf(buf);
//}

void x()
{
    int v[] = { 1, -2, 3, -4, -5, -6, 7, 8 };
    int p = 0, pplus = -1;
    while (p < _countof(v)) {
        if (v[p] < 0) {
            if (pplus >= 0) {
                std::swap(v[p], v[pplus]);
                pplus++;
            }
        } else {
            if (pplus < 0) pplus = p;
        }
        p++;
    }

    for (auto &x : v) {
        printf("%d ", x);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    x();
    //reinterpret_cast<unsigned *>(buf + 0x14)[0] = reinterpret_cast<unsigned>(&Shellcode);
    //buf[0x19] = '\0';

    //DO_TAINT()

    //int len = ((int*) buf)[0];

    //...

    //print(buf);
	//return 0;
}


//void Shellcode() 
//{
//    TAINT_CODE_BEGIN()
//
//    printf("\n\nThis is malicious code!\n\n");
//    exit(0);
//
//    TAINT_CODE_END()
//}