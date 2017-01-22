// READ BEFORE YOU START:
// You are given a partially completed program that creates a list of dogs for an adoption shelter.
// Each dog has the corresponding information: name, gender, breed, age, and weight.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, the return types, or the parameters, you risk failing the automated test cases.
//
// The following will be accepted as input in the following format: "name:gender:breed:age:weight"
// Example Input: "Spot:M:Terrier:5:15.45" or "Daisy:F:Poodle:3:15"
// Valid name: String containing alphabetical letters beginning with a capital letter
// Valid gender: Char value 'M' or 'F'
// Valid breed: String containing alphabetical letters beginning with a capital letter
// Valid age: Positive integer value
// Valid weight: Float containing no more than 2 decimal value, for example: 15.45 or 20.7 or 27
// All input will be a valid length and no more than the allowed number of dogs will be added to the list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// included to check for memory leaks
#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#pragma warning(disable: 4996)

typedef enum { male = 0, female } gender; // enumeration type gender

struct dog {
	char name[30];
	gender genderValue;
	char breed[30];
	int age;
	float weight;
	struct dog* next;
} *list = NULL;

// forward declaration of functions
void flush();
void branching(char);
void helper(char);
int add(char*, char*, char*, int, float); // 15
struct dog* search(char*); // 5
void remove_one(char*); // 10
void remove_all(struct dog*); // 5
struct dog* create_list_by_age(int age); // 15
void display(struct dog*);

int main()
{
	char ch = 'i';
	printf("Assignment 6: Linked Lists\n\n");
	printf("Dog Adoption Center\n\n");

	do
	{
		printf("Please enter your selection:\n");
		printf("\ta: add a new dog to the list\n");
		printf("\ts: search for a dog on the list\n");
		printf("\td: display list of dogs\n");
		printf("\tr: remove a dog from the list\n");
		printf("\tp: print list of dogs of a certain age\n");
		printf("\tq: quit\n");
		ch = tolower(getchar());
		flush();
		branching(ch);
	} while (ch != 'q');

	remove_all(list);
	list = NULL;
	_CrtDumpMemoryLeaks(); // check for memory leaks (VS will let you know in output if they exist)
	return 0;
}

// consume leftover '\n' characters
void flush()
{
	int c;
	do c = getchar(); while (c != '\n' && c != EOF);
}

// branch to different tasks
void branching(char c)
{
	switch (c)
	{
	case 'a':
	case 's':
	case 'r':
	case 'p': helper(c); break;
	case 'd': display(list); break;
	case 'q': break;
	default: printf("Invalid input!\n");
	}
}

// The helper function is used to determine how much information is needed and which function to send that information to.
// It uses values that are returned from some functions to produce the correct ouput.
// There is no implementation needed here, but you should study this function and know how it works.
// It is always helpful to understand how the code works before implementing new features.
// Do not change anything in this function or you risk failing the automated test cases.
void helper(char c)
{
	char input[100];

	if (c == 'a')
	{
		printf("\nPlease enter the dog's information in the following format:\n");
		printf("\tname:gender:breed:age:weight\n");
		fgets(input, sizeof(input), stdin);

		// discard '\n' chars attached to input
		input[strlen(input) - 1] = '\0';

		char* name = strtok(input, ":"); // strtok used to parse string
		char* genderValueString = strtok(NULL, ":");
		char* breed = strtok(NULL, ":");
		int age = atoi(strtok(NULL, ":")); // atoi used to convert string to int
		float weight = atof(strtok(NULL, ":")); // atof used to convert string to float

		int result = add(name, genderValueString, breed, age, weight);

		if (result == 0)
			printf("\nThat dog is already on the list\n\n");
		else
			printf("\nDog added to list successfully\n\n");
	}
	else if (c == 's' || c == 'r')
	{
		printf("\nPlease enter the dog's name:\n");
		fgets(input, sizeof(input), stdin);

		// discard '\n' chars attached to input
		input[strlen(input) - 1] = '\0';

		struct dog* result = search(input);

		if (result == NULL)
			printf("\nThat dog is not on the list\n\n");
		else if (c == 's')
			printf("\nBreed: %s\n\n", result->breed);
		else if (c == 'r')
		{
			remove_one(input);
			printf("\nDog removed from the list\n\n");
		}
	}
	else // c = 'p'
	{
		int age = 0;

		printf("\nPlease enter an age:\n");
		scanf("%d", &age); getchar();

		struct dog* result = create_list_by_age(age);

		display(result);
		remove_all(result);
	}
}

// Q1: add (15)
// Similar to hw05, you will be inserting into a list of dogs sorted alphabetically by their name.
// Differing from hw05, there is no limit to how many dogs can be on this list.
// For this assignment, you can also assume that no 2 dogs will have the same name.
// NOTE: You still need to check if the input dog already exists on the list.
//
// This means that if the name of the dog to be added matches the name of a dog on the list,
// then it is enough to assume that the dog is already on the list and should not be added.
// To clarify, you will be tested to assure that a dog is not added to the list twice.
//
// If the dog is already on the list, do not add the dog to the list AND return the integer value 0.
// If the dog is not on the list, add the dog to the list and return the integer value 1.
//
// "list" is initialized as NULL. Use this as your 'head' of the list and insert into it accordingly. 
// NOTE: You will need to allocate memory (malloc) for a new node to add to the linked list of dogs.
//
// To insert the dog at sorted place, you need to consider 4 possibilities for inserting into the list:
//	- inserting into an empty list
//	- inserting at the beginning of the list
//	- inserting inbetween 2 nodes in the list
//	- inserting at the end of the list
int add(char* name, char* genderValueString, char* breed, int age, float weight)
{
	if (search(name) == NULL)
	{
		struct dog *insertDog;
		insertDog = (struct dog*) malloc(sizeof(struct dog));
		if (insertDog == 0) { return -1; }

		gender dogGender = female;

		if (*genderValueString == 'F') { dogGender = female; }
		else if (*genderValueString == 'M') { dogGender = male; }

		strcpy(insertDog->name, name); insertDog->genderValue = dogGender; strcpy(insertDog->breed, breed); insertDog->age = age; insertDog->weight = weight;
        if (list == NULL) {
			list = insertDog;
			list->next = NULL;
			return 1;
		} else {
			if (list->next == NULL){
				if (strcmp(list->name, insertDog->name) < 0){
					list->next = insertDog;
					insertDog->next = NULL;
				} else {
					insertDog->next = list;
					list = insertDog;
				} return 1;
			} else
			{
				if (strcmp(insertDog->name, list->name) < 0) {
					insertDog->next = list;
					list = insertDog;
					return 1;
				}
				struct dog *temp = list;
				while (temp->next != NULL) {
					if (strcmp(temp->next->name, insertDog->name) > 0 && strcmp(temp->name, insertDog->name) < 0) {
						insertDog->next = temp->next;
						temp->next = insertDog;
						return 1;
					} temp = temp->next;}
				temp->next = insertDog;
				insertDog->next = NULL;
				return 1;
			}
		}
	} return 0;
}

// Q2 : search (5 points)
// In this function, you are passed the name of a dog to find its breed.
// If the dog exists on the list, return a pointer to the requested dog. If not, return NULL.
// (You must return a pointer to a node in your list. Do not create a pointer that just includes the breed)
// (Remember that it is enough to search for a dog by only their name since no 2 dogs will have the same name)
struct dog* search(char* name)
{
	struct dog *insertDog = list, *second = list;

	if (insertDog != NULL) {
		if (strcmp(name, insertDog->name) == 0) { return insertDog; } 
		else {
			second = insertDog;
			insertDog = insertDog->next;
		}
	} return NULL;
}

// Q3: remove_one (10)
// In this function, you are passed the name of a dog to remove the corresponding dog from the list.
// The search function is called before this function so you can assume that the dog is on the list.
// You will need to find the dog and remove it using proper memory management to ensure no memory leaks.
// (Remember that it is enough search for a dog by their name since no 2 dogs will have the same name)
void remove_one(char* name)
{

	struct dog* current; struct dog* previous;

	if (strcmp(list->name, name) == 0) {
		previous = list;
		list = list->next;
		free(previous);
		return;
	} else {
		current = list->next;
		previous = list;
        while (current != NULL && previous != NULL) {

			if (strcmp(current->name, name) == 0) {
				struct dog* temp = current;
				previous->next = current->next;
				free(temp);
				return;
			} 
			previous = current; current = current->next;
		} return;
	}
}

// Q4: remove_all (5)
// Recursively all of the dogs from the list while using proper memory management to ensure no memory leaks.
// If memory leaks are detected, the _CrtDumpMemoryLeaks() call in main will notify you in the output window.
// This function is called in main before the program terminates, you only need to implement the code.
void remove_all(struct dog* dogs)
{
	if (dogs != NULL) {
		remove_all(dogs->next);
		dogs = NULL;
		free(dogs);
	}	return;
}

// Q5: create_list_by_age (15)
// In this function, you will read the existing linked list pointed to by head pointer "list". The function takes  
// a parameter age and will returning another list of dogs that are of at least a certain 'age'.
// The returned list should contain all dogs with an age that is greater than or equal (>=) to the parameter age.
// The returned list should still be in alphabetical order. You need to add to the returned list accordingly.
// NOTE: If you have implemented your add() function correctly, your list should already be in alphabetical order.
struct dog* create_list_by_age(int age)
{
	struct dog* head = list; struct dog* state = NULL; struct dog* place = state;

	while (head != NULL)
	{
		if (head->age >= age) {
			struct dog *insertDog;
			insertDog = (struct dog *) malloc(sizeof(struct dog));
			if (insertDog == 0) { return -1; }

			strcpy(insertDog->name, head->name); insertDog->genderValue = head->genderValue; strcpy(insertDog->breed, head->breed); insertDog->age = head->age; insertDog->weight = head->weight;

			if (state == NULL) { state = insertDog; state->next = NULL; }
			else {
				if (state->next == NULL){ state->next = insertDog; insertDog->next = NULL; }
				else {
					struct dog *temp = state;
					while (temp->next != NULL) { temp = temp->next; }
					temp->next = insertDog; insertDog->next = NULL;
				}
			}
		}
	  head = head->next;
	} return state;
}

// This function displays the list of dogs and the information for each one. It is already implemented for you.
// It may be helpful to trace through this function to help you complete other sections of this assignment.
void display(struct dog* dogs)
{
	struct dog* temp = dogs;
	char* genderValue;

	if (dogs == NULL)
		printf("\nThere are no dogs on this list!\n\n");
	else
	{
		while (temp != NULL)
		{
			printf("\nName: %s\n", temp->name);

			if (temp->genderValue == male)
				genderValue = "Male";
			else
				genderValue = "Female";

			printf("Gender: %s\n", genderValue);
			printf("Breed: %s\n", temp->breed);
			printf("Age: %d years old\n", temp->age);
			printf("Weight: %.2f lbs\n", temp->weight);

			temp = temp->next;
		}
		printf("\n");
	}
}