#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int bubblesort(char ** array, int sz, int s, int b) {
	if (s  == sz) return 0;
	if (b == 0 || strcmp(array[b-1], array[b]) < 0) return bubblesort(array, sz, s+1, s+1);
	__atomic_exchange(&array[b-1], &array[b], &array[b], 1);
	return bubblesort(array, sz, s, b-1);
}

int main() {
	FILE * inputFile = fopen("onegin.txt", "rb");

	char ** arr;
	int capacity = 8192;
	int sz = 0;
	char * buf = calloc(50, 1);

	arr = calloc(sizeof(char *), capacity);

	while( fgets(buf, 50, stdin) != NULL ) {
		if ( sz >= capacity ) {arr = realloc(arr, sizeof(double)*(capacity*=2));}
		arr[sz++] = strdup(buf);
	}
	bubblesort(arr, sz, 0, 0);

	fclose(inputFile);
	fprintf(stdout, "Sorted list:\n");
	for (int i = 0; i < sz; i++) {
		fprintf(stdout, "%s", arr[i]);
		free(arr[i]);
	}

	free(arr);
}
