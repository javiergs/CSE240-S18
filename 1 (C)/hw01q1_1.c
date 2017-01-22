/* This C program demonstrates the switch statement without using breaks. */
/* The program is tested on MS Visual C++ platform                        */
#include <stdio.h>
#pragma warning(disable : 4996) 
int main() {

	// Variable Initialization
	char ch; 
	ch = '+';
	int f, a = 10, b = 20;

	//Added double initialization to print 0.5 on the "/" switch case
    double e, c = 10.0, d = 20.0;

	// Print statement to show user what character they inputed
	printf("ch = %c\n", ch);

	//Enter switch case based on input
	switch (ch) {
	case '+': f = a + b; printf("f = %d\n", f); break;
	case '-': f = a - b; printf("f = %d\n", f); break;
	case '*': f = a * b; printf("f = %d\n", f); break;
	case '/': f = a / b; printf("f = %d\n", f); break;
	default: printf("invalid operator\n");
	}
	ch = '-';
	printf("ch = %c\n", ch);
	switch (ch) {
	case '+': f = a + b; printf("f = %d\n", f); break;
	case '-': f = a - b; printf("f = %d\n", f); break;
	case '*': f = a * b; printf("f = %d\n", f); break;
	case '/': f = a / b; printf("f = %d\n", f); break;
	default: printf("invalid operator\n");
	}
	ch = '*';
	printf("ch = %c\n", ch);
	switch (ch) {
	case '+': f = a + b; printf("f = %d\n", f); break;
	case '-': f = a - b; printf("f = %d\n", f); break;
	case '*': f = a * b; printf("f = %d\n", f); break;
	case '/': f = a / b; printf("f = %d\n", f); break;
	default: printf("invalid operator\n");
	}
	ch = '/';
	printf("ch = %c\n", ch);
	switch (ch) {
	case '+': f = a + b; printf("f = %d\n", f); break;
	case '-': f = a - b; printf("f = %d\n", f); break;
	case '*': f = a * b; printf("f = %d\n", f); break;
	case '/': e = c / d; printf("f = %.2f\n", e); break; // Added so the 0.5 would print
	default: printf("invalid operator\n");
	}
	ch = '%';
	printf("ch = %c\n", ch);
	switch (ch) {
	case '+': f = a + b; printf("f = %d\n", f); break;
	case '-': f = a - b; printf("f = %d\n", f); break;
	case '*': f = a * b; printf("f = %d\n", f); break;
	case '/': f = a / b; printf("f = %d\n", f); break;
	default: printf("invalid operator\n");
	}
}

