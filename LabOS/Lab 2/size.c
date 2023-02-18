#include <stdio.h>
int main(){
	int a=1;
	long b=1;
	float c=1.0;
	double d=1.0;
	char e='1';

	printf("%d\n", a);
	printf("%ld\n\n", sizeof(a));

	printf("%ld\n",b);
	printf("%ld\n\n", sizeof(b));

	printf("%f\n", c);
	printf("%ld\n\n", sizeof(c));

	printf("%f\n", d);
	printf("%ld\n\n", sizeof(d));

	printf("%c\n", e);
	printf("%ld\n\n", sizeof(e));
	return 0;
}
