#include <stdio.h>

void print_pointer(int var, int* pointer);

int main(){
	int x = 0;

	printf("%d\n", x);
	printf("%d\n", &x);
	print_pointer(x, &x);

	printf("\n\n");

	int d[20] = {};
	printf("%d %d %d %d\n\n", &d[0], &d[1], &d[2], &d[3]);
	printf("%d\n\n", d);

	short s[20] = {};
	printf("%hd %hd %hd %hd\n\n", &s[0], &s[1], &s[2], &s[3]);
	printf("%hd\n\n", s);

	long l[20] = {};
	printf("%ld %ld %ld %ld\n\n", &l[0], &l[1], &l[2], &l[3]);
	printf("%ld\n\n", l);

	char c[20] = {};
	printf("%c %c %c %c\n\n", &c[0], &c[1], &c[2], &c[3]);
	printf("%c\n\n", c);

	return 0;
}

void print_pointer(int var, int* pointer){
	printf("%d\n", var);
	printf("%d\n", pointer);
}