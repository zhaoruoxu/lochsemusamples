// AnalyzeSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void Sort(int data[], int n)
{
    for (int i = n-1; i >= 0; i--) {
        for (int j = 0; j <= i-1; j++) {
            if (data[j] > data[j+1]) {
                int temp    = data[j];
                data[j]     = data[j+1];
                data[j+1]   = temp;
            }
        }
    }
}

void Print(int data[], int n) 
{
    for (int i = 0; i < n; i++)
        printf("%d ", data[i]);
    printf("\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
    int x[] = {4, 9, 2, 5, 3, 7};

    Print(x, sizeof(x)/sizeof(int));
    Sort(x, sizeof(x)/sizeof(int));
    Print(x, sizeof(x)/sizeof(int));
	return 0;
}

