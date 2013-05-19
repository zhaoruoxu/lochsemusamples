// TaintTestSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
    unsigned char arr[] = { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

    for (int i = 0; i < _countof(arr) - 1; i++) {
        for (int j = i + 1; j < _countof(arr); j++) {
            if (arr[i] < arr[j]) {
                unsigned char temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }

//     for (auto x : arr) {
//         printf("%d  ", x);
//     }

    printf("all done\n");

	return 0;
}

