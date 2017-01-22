#include <stdio.h>
#include <string.h>

#pragma warning(disable : 4996) 

// Read before you start:
// Do not modify any part of this program that you are given. Doing so may cause you to fail automated test cases.
// You are given a partially complete program. Your job is to complete the functions in order for this program to work successfully.
// You should complete this homework assignment using Microsoft Visual Studios 2013 (or a later version).
// All instructions are given above the required functions, please read them and follow them carefully. 
// If you modify the function return types or parameters, you will fail the automated test cases.
// You can assume that all inputs are valid. Ex: If prompted for a char, the input will be a char.

// Global Macro Values
#define NUM_STRINGS 5
#define STRING_LENGTH 32

// Forward Declarations
void encryptStrings(char[NUM_STRINGS][STRING_LENGTH], int);
void decryptStrings(char[NUM_STRINGS][STRING_LENGTH], int);
void swapStrings(char[STRING_LENGTH], char[STRING_LENGTH]);
void sortStrings(char[NUM_STRINGS][STRING_LENGTH]);
void printStrings(char[NUM_STRINGS][STRING_LENGTH]);
int vowelCounter(char[STRING_LENGTH]);
int isAPalindrome(char[STRING_LENGTH]);
void removeLetter(char[STRING_LENGTH], char);

// Problem 1: encryptStrings (5 points)
// Rewrite this function to perform the same task as in hw03, using only pointer operations.
// You must use pointer operations only. If you use array operations, you will recieve no credit for this part.
// You may use the code you submitted for hw03 or you may use the solution code for hw03.
//
// Traverse the 2D array of characters variable 'strings' and encrypt each string using the integer value 'key'.
// In order to encrypt the 2D array of characters, we will shift those ASCII characters forward by the integer value of 'key'.
// If the string is "hello" and key = 2, we will shift those characters forward in ASCII by 2 and the result will be "jgnnq".
// The case above is an example of a string that has alphabetical letters in the encrypted and decrypted string.
// Once the value of 'key' gets larger, you will extend past alphabetical characters and reach non-alphabetical characters.
// NOTE: DO NOT encrypt the null terminator characters. Use the null terminators to find the end of each array of characters.
void encryptStrings(char strings[NUM_STRINGS][STRING_LENGTH], int key)
{
	char *firstCharacter = &strings[0][0];
	char *movingPointer = &strings[0][0];

	int j = 0;

	for (int i = 0; i < NUM_STRINGS; i++) {

		while(*movingPointer != 0) {

			*movingPointer = *movingPointer + key;
			 movingPointer++;
		}

		firstCharacter = firstCharacter + 32;
		movingPointer = firstCharacter;
		j = 0;

	}
}

// Problem 2: decryptStrings (5 points)
// Rewrite this function to perform the same task as in hw03, using only pointer operations.
// You must use pointer operations only. If you use array operations, you will recieve no credit for this part.
// You may use the code you submitted for hw03 or you may use the solution code for hw03.
//
// Traverse the 2D array of characters variable 'strings' and decrypt each string using the integer value 'key'.
// In order to decrypt the 2D array of characters, we will shift those ASCII characters backwards by the integer value of 'key'.
// If the string is "jgnnq" and key = 2, we will shift those characters backward in ASCII by 2 and the result will be "hello".
// NOTE: DO NOT decrypt the null terminator characters. Use the null terminators to find the end of each array of characters.
// HINT: This should be very similiar to the encryption function defined above in Problem 2.
void decryptStrings(char strings[NUM_STRINGS][STRING_LENGTH], int key)
{
	char *firstCharacter = &strings[0][0];
	char *movingPointer = &strings[0][0];

	int j = 0;

	for (int i = 0; i < NUM_STRINGS; i++) {

		while (*movingPointer != 0) {

			*movingPointer = *movingPointer - key;
			movingPointer++;
		}

		firstCharacter = firstCharacter + 32;
		movingPointer = firstCharacter;
		j = 0;

	}
}

void swapStrings(char string1[STRING_LENGTH], char string2[STRING_LENGTH])
{
	char temp[STRING_LENGTH];
	strcpy(temp, string1);
	strcpy(string1, string2);
	strcpy(string2, temp);
}

// Problem 3: sortStrings (10 points)
// Rewrite this function to perform the same task as in hw03, using only pointer operations.
// You must use pointer operations only. If you use array operations, you will recieve no credit for this part.
// You can use the swapStrings() function if you'd like, but are not required to do so.
// You may use the code you submitted for hw03 or you may use the solution code for hw03.
//
// Sort the 5 strings contained in the 2D character array parameter labeled "strings".
// Sort the strings based on their ASCII character value (use strcmp to compare strings).
// NOTE: You MUST incorporate your "swapStrings" function to recieve full points for this part.
// See the output provided in the word document for example input and output.
void sortStrings(char strings[NUM_STRINGS][STRING_LENGTH])
{
	char *p1, *p2, *p3, *p4, *p5;

	p1 = strings[0];
	p2 = strings[1];
	p3 = strings[2];
	p4 = strings[3];
	p5 = strings[4];

	for (int i = 0; i < NUM_STRINGS; i++) {
		if (strcmp(p1, p2) > 0) {
			swapStrings(p1, p2);
		}
		if (strcmp(p2, p3) > 0) {
			swapStrings(p2, p3);
		}
		if (strcmp(p3, p4) > 0) {
			swapStrings(p3, p4);
		}
		if (strcmp(p4, p5) > 0) {
			swapStrings(p4, p5);
		}
	} 
}

void printStrings(char strings[NUM_STRINGS][STRING_LENGTH])
{
	for (int i = 0; i < NUM_STRINGS; i++)
	{
		printf("%s\n", strings[i]);
	}
}

// Problem 4: vowelCounter (10 points)
// This function accepts an array of characters and returns the number of vowels in that string (an integer).
// You must use pointer operations only. If you use array operations, you will recieve no credit for this part.
// You must account for both uppercase and lowercase vowels (A, a, E, e, I, i, O, o, U, u).
// For this assignment, you can assume that the characters Y and y are not vowels.
int vowelCounter(char string[STRING_LENGTH])
{
	char *p = &string[0];

	int vowel = 0;

	while (*p != 0) {

		if (*p == 'A' || *p == 'a' || *p == 'E' || *p == 'e' || *p == 'I' || *p == 'i' || *p == 'O' || *p == 'o' || *p == 'U' || *p == 'u') {
			vowel++;
		}p++;
	}return vowel;
}

// Problem 5: isAPalindrome (10 points)
// This function accepts an array of characters and returns an integer.
// You must use pointer operations only. If you use array operations, you will recieve no credit for this part.
// This function should return 1 (true) if the parameter 'string' is a palindrome, or 0 (false) if 'string' is not a palindrome.
// A palindrome is a sequence of characters which when reversed, is the same sequence of characters.
// For this assignment, you can assume that 'string' will be a single word containing only lowercase letters and no spaces.
// Example Palindromes: mom, racecar, stats, rotator, deleveled
int isAPalindrome(char string[STRING_LENGTH])
{
	char *firstStr = &string[0];
	char *secondStr = &string[0];

	int size = 0;

	while (*firstStr != 0)
	{
		size++;
		firstStr++;
	}

	firstStr--;
	char *third = firstStr;
	firstStr = secondStr;

	while (*firstStr != 0)
	{
		if (*firstStr != *third)
		{
			return 0;
		}
		firstStr++;
		third--;
	}return 1;
} 

// Problem 6: removeLetter (10 points)
// This function accepts an array of characters as well as a character to be removed from the array of characters.
// You must use pointer operations only. If you use array operations, you will recieve no credit for this part.
// All occurances of the 'letterToBeRemoved' should be removed from character array 'string'
// Example: If string = "letter", and letterToBeRemoved = 't', after this function terminates, string should contain "leer"
void removeLetter(char string[STRING_LENGTH], char letterToBeRemoved)
{
	char *str1 = &string[0];
	char *str2 = &string[0];

	for (str1 = str2; *str1 != '\0'; str1++) {

		*str2 = *str1;

		if (*str2 != letterToBeRemoved){

			str2++;

		}else {}

	}*str2 = '\0';
}



// You should study and understand how this main function works.
// Do not modify it in any way, there is no implementation needed here.
void main()
{
	int selection;
	char input[STRING_LENGTH];

	printf("Assignment 4: Pointer Operations\n\n");
	printf("Choose one of the following: \n1. Sorting Encrypted Strings\n2. Vowel Counter\n3. Palindrome\n4. Letter Remover\n\n");
	scanf("%d", &selection); // store integer
	getchar(); // consume newline char

	if (selection == 1)
	{
		char strings[NUM_STRINGS][STRING_LENGTH]; // will store 5 strings each with a max length of 32
		int key;

		for (int i = 0; i < NUM_STRINGS; i++)
		{
			printf("\nEnter the next String: "); // prompt for string
			fgets(input, sizeof(input), stdin); // store input string
			input[strlen(input) - 1] = '\0'; // convert trailing '\n' char to '\0' (null terminator)
			strcpy(strings[i], input); // copy input to 2D strings array
		}

		printf("\nEnter a key value for encryption: "); // prompt for integer
		scanf("%d", &key); // store integer

		encryptStrings(strings, key);
		printf("\nEncrypted Strings:\n");
		printStrings(strings);
		sortStrings(strings);
		decryptStrings(strings, key);
		printf("\nSorted Strings:\n");
		printStrings(strings);

	}
	else if (selection == 2)
	{
		printf("\nEnter a String: "); // prompt for string
		fgets(input, sizeof(input), stdin); // store input string
		input[strlen(input) - 1] = '\0'; // convert trailing '\n' char to '\0' (null terminator)

		int numVowels = vowelCounter(input);

		printf("\nThere are %d vowels in \"%s\"", numVowels, input);
	}
	else if (selection == 3)
	{
		printf("\nEnter a String: "); // prompt for string
		fgets(input, sizeof(input), stdin); // store input string
		input[strlen(input) - 1] = '\0'; // convert trailing '\n' char to '\0' (null terminator)

		int isPalindrome = isAPalindrome(input);

		if (isPalindrome)
			printf("\nThe string \"%s\" is a palindrome", input);
		else
			printf("\nThe string \"%s\" is not a palindrome", input);
	}
	else if (selection == 4)
	{
		printf("\nEnter a String: "); // prompt for string
		fgets(input, sizeof(input), stdin); // store input string
		input[strlen(input) - 1] = '\0'; // convert trailing '\n' char to '\0' (null terminator)

		char letterToBeRemoved;

		printf("\nEnter a letter to be removed: "); // prompt for char
		scanf(" %c", &letterToBeRemoved); // store input char
		removeLetter(input, letterToBeRemoved);

		printf("\nResult: %s", input);
	}
	else
	{
		printf("Program terminating...");
	}
}