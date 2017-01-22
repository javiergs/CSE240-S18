#include <stdio.h>
#include <string.h>

#pragma warning(disable : 4996) 

// Read before you start:
// Do not modify any part of this program that you are given. Doing so may cause you to fail automated test cases.
// You are given a partially complete program. Your job is to complete the functions in order for this program to work successfully.
// You should complete this homework assignment using Microsoft Visual Studios 2013 (or a later version).
// All instructions are given above the required functions, please read them and follow them carefully. 
// If you modify the function return types or parameters, you will fail the automated test cases.
// You can assume that all inputs are valid. Ex: If prompted for an integer, an integer will be input.
// NOTE: For this assignment, you can assume that all input characters will be lowercase characters.

// Global Macro Values. They are used to define the size of a 5 x 32 two-dimensional array of characters
#define NUM_STRINGS 5
#define STRING_LENGTH 32

// Forward Declarations
void initializeStrings(char[NUM_STRINGS][STRING_LENGTH]);
void encryptStrings(char[NUM_STRINGS][STRING_LENGTH], int);
void decryptStrings(char[NUM_STRINGS][STRING_LENGTH], int);
void swapStrings(char[STRING_LENGTH], char[STRING_LENGTH]);
void sortStrings(char[NUM_STRINGS][STRING_LENGTH]);
void printStrings(char[NUM_STRINGS][STRING_LENGTH]);

// Problem 1: initializeStrings (5 points)
// Traverse the 2D array of characters variable 'strings' (in the main program) and set all 32 characters in each of 
// the 5 char arrays to a null terminator so that there is a 5 row and 32 column 2D array full of null terminators.
// The null terminator is represented by the character value '\0' and is used to denote the end of a string.
// This will come in use later in the program when you will need to print the 2D array of characters.
void initializeStrings(char strings[NUM_STRINGS][STRING_LENGTH])
{
	for (int i = 0; i < NUM_STRINGS; i++) {
		for (int j = 0; j < STRING_LENGTH; j++){
			strings[i][j] = '\0';
		}
	}
}

// Problem 2: encryptStrings (5 points)
// Traverse the 2D array of characters variable 'strings' and encrypt each string using the integer value 'key'.
// In order to encrypt the 2D array of characters, we will shift those ASCII characters forward by the integer value of 'key'.
// If the string is "hello" and key = 2, we will shift those characters forward in ASCII by 2 and the result will be "jgnnq".
// The case above is an example of a string that has alphabetical letters in the encrypted and decrypted string.
// Once the value of 'key' gets larger, you will extend past alphabetical characters and reach non-alphabetical characters.
// NOTE: DO NOT encrypt the null terminator characters. Use the null terminators to find the end of each array of characters.
void encryptStrings(char strings[NUM_STRINGS][STRING_LENGTH], int key)
{
	for (int i = 0; i < NUM_STRINGS; i++) {
		for (int j = 0; j < STRING_LENGTH; j++){
			if (strings[i][j] == '\0') {
				break;
			}
			strings[i][j] = strings[i][j] + key;
		}
	}
}

// Problem 3: decryptStrings (5 points)
// Traverse the 2D array of characters variable 'strings' and decrypt each string using the integer value 'key'.
// In order to decrypt the 2D array of characters, we will shift those ASCII characters backwards by the integer value of 'key'.
// If the string is "jgnnq" and key = 2, we will shift those characters backward in ASCII by 2 and the result will be "hello".
// NOTE: DO NOT decrypt the null terminator characters. Use the null terminators to find the end of each array of characters.
// HINT: This should be very similiar to the encryption function defined above in Problem 2.
void decryptStrings(char strings[NUM_STRINGS][STRING_LENGTH], int key)
{
	for (int i = 0; i < NUM_STRINGS; i++) {
		for (int j = 0; j < STRING_LENGTH; j++){
			if (strings[i][j] == '\0') {
				break;
			}
			strings[i][j] = strings[i][j] - key;
		}
	}
}

// Problem 4: swapStrings (5 points)
// Swap the strings that are passed as parameters, this function will be used in Problem 5.
// If string1 is "hello" and string2 is "goodbye", after calling this function, string1 will be "goodbye" and string2 will be "hello".
void swapStrings(char string1[STRING_LENGTH], char string2[STRING_LENGTH])
{
	char temp[STRING_LENGTH];
	strcpy(temp, string1);
	strcpy(string1, string2);
	strcpy(string2, temp);
}

// Problem 5: sortStrings (20 points)
// Sort the 5 strings contained in the 2D character array parameter labeled "strings".
// Sort the strings based on their ASCII character value (use strcmp to compare strings).
// NOTE: You MUST incorporate your "swapStrings" function to recieve full points for this part.
// See the output provided in the word document for example input and output.
void sortStrings(char strings[NUM_STRINGS][STRING_LENGTH])
{
	for (int i = 0; i < NUM_STRINGS; i++){
		for (int j = 0; j < NUM_STRINGS; j++){
			do{
				break;
			} while (j == 4);
			int compareValue = strcmp(strings[j], strings[i]);
			if (compareValue > 0){
				swapStrings(strings[j], strings[i]);
			}else{}
		}
	}
}

// Problem 6: printStrings (10 points)
// Traverse the 2D character array "strings" and print each of the contained strings.
// See the example outputs provided in the word document. Your output should match the example outputs.
void printStrings(char strings[NUM_STRINGS][STRING_LENGTH])
{
	for (int i = 0; i < NUM_STRINGS; i++) {
		for (int j = 0; j < STRING_LENGTH; j++){
			if (strings[i][j] == '\0') {
				printf("\n");
				break;
			} else {
				printf("%c", strings[i][j]);
			}
		}
	}
}


// You should study and understand how this main function works.
// Do not modify it in any way, there is no implementation needed here.
void main()
{
	char strings[NUM_STRINGS][STRING_LENGTH]; // will store 5 strings each with a max length of 32
	int key;
	char input[STRING_LENGTH];
	initializeStrings(strings);

	printf("Assignment 3: 2D Character Arrays\n\n");

	for (int i = 0; i < NUM_STRINGS; i++)
	{
		printf("Enter the next String: "); // prompt for string
		fgets(input, sizeof(input), stdin); // store input string
		input[strlen(input) - 1] = '\0'; // convert trailing '\n' char to '\0' (null terminator)
		strcpy(strings[i], input); // copy input to 2D strings array
	}

	printf("Enter a key value for encryption: "); // prompt for integer
	scanf("%d", &key); // store integer

	encryptStrings(strings, key);
	printf("\nEncrypted Strings:\n");
	printStrings(strings);
	sortStrings(strings);
	decryptStrings(strings, key);
	printf("\nSorted Strings:\n");
	printStrings(strings);
}