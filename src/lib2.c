#include "my_lib.h"
#include <stdlib.h>
#include <stdio.h>

int gcf(int a, int b){
    if (a < b){
        int tmp = b;
        b = a;
        a = tmp;
    }
    for (int i = b; i > 0; --i){
        if ((a % i == 0) && (b % i == 0)){
            return i;
        }
    }
    return -1;
}

int compare(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

void sort(int* array, int size) {
	printf("Sorting integers using the second implementation.\n");
	qsort(array, size, sizeof(int), compare);
}
