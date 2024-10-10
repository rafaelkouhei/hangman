#include <stdio.h>

void print_pointer(int var, int* pointer);

int main(){
	int x = 0;

	printf("%d\n", x);
	printf("%d\n", &x);
	print_pointer(x, &x);

	printf("\n\n");

	int d[20] = {};
	printf("int %d %d %d %d\n\n", &d[0], &d[1], &d[2], &d[3]);
	printf("int %d\n\n", d);

	short s[20] = {};
	printf("short %hd %hd %hd %hd\n\n", &s[0], &s[1], &s[2], &s[3]);
	printf("short %hd\n\n", s);

	long l[20] = {};
	printf("long %ld %ld %ld %ld\n\n", &l[0], &l[1], &l[2], &l[3]);
	printf("long %ld\n\n", l);

	char c[20] = {};
	printf("char %c %c %c %c\n\n", &c[0], &c[1], &c[2], &c[3]);
	printf("char %c\n\n", c);

	return 0;
}

void print_pointer(int var, int* pointer){
	printf("---------- Function printing ----------\n");
	printf("%d\n", var);
	printf("%d\n", pointer);
	printf("---------------------------------------\n");

	int y = 0;
	y = *pointer;
	printf("Y: %d\n", y);
}