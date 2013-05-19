#include "Sort_Test.h"


static void Sort(const int input[], int output[], int n)
{
    memcpy( output, input, n * sizeof(int) );
    for ( int i = 0; i < SORT_TEST_LENGTH_INT - 1; i++ )
    {
        for ( int j = i + 1; j < SORT_TEST_LENGTH_INT; j++ )
        {
            if (output[i] > output[j])
            {
                int temp = output[i];
                output[i] = output[j];
                output[j] = temp;
            }
        }
    }
}

void Sort_Test()
{
    int data[SORT_TEST_LENGTH_INT];
    int output[SORT_TEST_LENGTH_INT];

    srand(0x12345);
    for ( int i = 0; i < SORT_TEST_LENGTH_INT; i++ ) {
        data[i] = rand();
    }

    printf("Array before sort:\n");
    for ( int i = 0; i < SORT_TEST_LENGTH_INT; i++ ) {
        printf("%d  ", data[i]);
    }
    printf("\n");

    Sort( data, output, SORT_TEST_LENGTH_INT );
 
    printf("Array after sort:\n");
    for ( int i = 0; i < SORT_TEST_LENGTH_INT; i++ ) {
        printf("%d  ", output[i]);
    }
    printf("\n");

}