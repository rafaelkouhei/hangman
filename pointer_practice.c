#include <stdio.h>

void print_pointer(int var, int* pointer);

int main(){
	int x = 0;

	printf("%d\n", x);
	printf("%d\n", &x);

	print_pointer(x, &x);

	return 0;
}

void print_pointer(int var, int* pointer){
	printf("%d\n", var);
	printf("%d\n", pointer);
}