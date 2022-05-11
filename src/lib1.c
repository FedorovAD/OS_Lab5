#include "my_lib.h"
#include <stdlib.h>
#include <stdio.h>

int gcf(int a, int b){
    if (a % b == 0){
        return b;
    }
    return gcf(b, a % b);
}

void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void sort(int *array, int size) {
	printf("Sorting integers using the first implementation.\n");
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size - 1; ++j) {
			if (array[j] > array[j + 1]) {
				swap(array + j, array + j + 1);
			}
		}
	}
}
