/* This C program demonstrates the switch statement without using breaks. */
/* The program is tested on MS Visual C++ platform                        */
#include <stdio.h>
#pragma warning(disable : 4996) 

void main() {

	// Variable Initialization
	char ch;
	int f, a = 10, b = 20;

	// Variable Initialization to make sure the "/" command will print 0.5
	double e, c = 10.0, d = 20.0;

	for (int i = 0; i < 5; i++)
	{
		ch = getchar();

		switch (ch) {
		case '+': f = a + b; printf("f = %d\n", f); break;
		case '-': f = a - b; printf("f = %d\n", f); break;
		case '*': f = a * b; printf("f = %d\n", f); break;
		case '/': e = c / d; printf("f = %.2f\n", e); break; // Variables were changed to make sure 0.5 was printed
		default: printf("invalid operator\n");

		}
		getchar();
	}
}
