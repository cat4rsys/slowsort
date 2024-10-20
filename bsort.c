#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int bubblesort(char ** array, int sz, int s, int b) {
	if (s  == sz) return 0;
	if (b == 0 || strcmp(array[b-1], array[b]) < 0) return bubblesort(array, sz, s+1, s+1);
	__atomic_exchange(&array[b-1], &array[b], &array[b], 1);
	//double x = array[b-1];
	//array[b-1] = array[b];
	//array[b] = x;
	return bubblesort(array, sz, s, b-1);
}

int main() {
	FILE * inputFile = fopen("onegin.txt", "rb");

	char ** arr;
	int capacity = 8192;
	int sz = 0;
	char * buf = calloc(50, 1);

	arr = calloc(sizeof(char *), capacity);

	//printf("%p, %p, %p", arr, inputFile, buf);
	while( feof(stdin) == 0) {
		//printf("%d", feof(stdin));
		if ( sz >= capacity ) {arr = realloc(arr, sizeof(double)*(capacity*=2));}
		fgets(buf, 50, stdin);
		if (feof(stdin) == 0) {
			arr[sz++] = strdup(buf);
		}
	}
	bubblesort(arr, sz, 0, 0);
	//for( int i =0; i < sz; i++ )
		//printf("%s", arr[i]);
	//free(arr);

}
