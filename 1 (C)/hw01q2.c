#include <stdio.h>
#pragma warning(disable : 4996) 

// CSE 240 Fall 2016 Homework 1 Question 2 (25 points)
// Before starting this assignment, please compile and run this program. 
// You will first notice that the program will not compile. Fix the errors and define the error types.
// Next, you will notice that the program is printing incorrect information. Fix the errors and define those error types.

void main() {

	// Problem 1: (5 points)
	// The statement below should cause the program to not compile. Correct the error(s). (2.5 points).

	int y = 100;

	printf("Integer y is equal to %d\n", y);

	// Define what type of error this is, your answer should replace the space next to "Error Type: " below (2.5 points).
	// Your answer should be either Syntactic, Semantic, or Contextual.
	printf("Error Type: Syntactic\n\n");


	// Problem 2: (5 points)
	// Half of 10 is 5, why is the program printing that half of 10 is 0? Correct the error(s) (2.5 points).

	int x = 10;

	printf("Half of %.0f is %.0f\n", (float)x, (float)x * (1.0 / 2));

	// Define what type of error this is, your answer should replace the space next to "Error Type: " below (2.5 points).
	// Your answer should be either Syntactic, Semantic, or Contextual.
	printf("Error Type: Contextual \n\n");


	// Problem 3: (5 points)
	// Integer variable x has been initialized to 10, why does the program seem to think otherwise? Correct the error(s) (2.5 points).

	x = 10;

	if (x == 20) {
		printf("x is equal to 20.\n");
	}

	if (x > 20) {
		printf("x is greater than 20.\n");
	}

	else {
		printf("x is less than 20.\n");
	}

	// Define what type of error this is, your answer should replace the space next to "Error Type: " below (2.5 points).
	// Your answer should be either Syntactic, Semantic, or Contextual.
	printf("Error Type: Semantic \n\n");


	// Problem 4: (5 points)
	// Surely, 10 is an even number. Why is the program printing that 10 is an odd number? Correct the error(s) (2.5 points).

	x = 10;

	if (x % 2 == 0) {
		printf("%d is an even number.\n", x);
	}
	if (x % 2 != 0) {
		printf("%d is an odd number.\n", x);
	}
	// Define what type of error this is, your answer should replace the space next to "Error Type: " below (2.5 points).
	// Your answer should be either Syntactic, Semantic, or Contextual.
	printf("Error Type: Semantic \n\n");


	// Problem 5: (5 points)
	// This bit of code is meant to print "Hello World!". Correct the error(s) (2.5 points).

	printf("Hello %s\n", "World!");

	// Define what type of error this is, your answer should replace the space next to "Error Type: " below (2.5 points).
	// Your answer should be either Syntactic, Semantic, or Contextual.
	printf("Error Type: Contextual \n\n");
}