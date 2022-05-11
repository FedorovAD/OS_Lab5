#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dlfcn.h>

void* lib1;
void* lib2;
int (*gcf)(int, int);
void (*sort)(int*, int);

void do_gcf() {
	int a, b;
	if (scanf("%d%d", &a, &b) != 2) {
		fprintf(stderr, "Function prime_count error input.\n");
		exit(1);
	}
	printf("The count of prime numbers is %d\n", gcf(a, b));
}

void read_array(int* array, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		if (scanf("%d", array + i) != 1) {
			fprintf(stderr, "Function sort array input error\n");
			exit(2);
		}
	}
}

void print_array(int* array, size_t size) {
	printf("Sorted sequence: ");
	for (size_t i = 0; i < size; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

void do_sort() {
	int size;
	if (scanf("%d", &size) != 1) {
		fprintf(stderr, "Function sort size input error\n");
		exit(3);
	}
	int* array = malloc(size * sizeof(int));
	read_array(array, size);
	sort(array, size);
	print_array(array, size);
	free(array);
}

int main() {
	lib1 = dlopen("lib1.so", RTLD_LAZY);
	if (!lib1) {
		fprintf(stderr, "Cannot open library lib1.so\n");
		return -2;
	}
	lib2 = dlopen("lib2.so", RTLD_LAZY);
	if (!lib2) {
		fprintf(stderr, "Cannot open library lib2.so\n");
		return -2;
	}
	gcf = dlsym(lib1, "gcf");
	sort = dlsym(lib1, "sort");
	int cmd;
	bool first_realise = false;
	printf("Change lib - 0\n");
	printf("gcf - 1 (int)arg1 (int)arg2\n");
	printf("sort - 2 (int)arg1 (int)arg2 ... \n");
	printf("Enter number the command and args: ");
	while (scanf("%d", &cmd) == 1) {
		if (cmd == 0) {
			if (first_realise) {
				gcf = dlsym(lib1, "gcf");
				sort = dlsym(lib1, "sort");
			} 
			else {
				gcf = dlsym(lib2, "gcf");
				sort = dlsym(lib2, "sort");
			}
			first_realise = !first_realise;
			if (gcf == NULL || sort == NULL) {
				fprintf(stderr, "Cannot find functions\n");
				exit(2);
			}
		}
		else if (cmd == 1) {
			do_gcf();
		}
		else if (cmd == 2) {
			do_sort();
		}
		else {
			fprintf(stderr, "Undefined command\n");
			dlclose(lib1);
			dlclose(lib2);
			return -1;
		}
		printf("Enter number the command and args: ");
	}
	dlclose(lib1);
	dlclose(lib2);
	return 0;
}
