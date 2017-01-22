// READ BEFORE YOU START:
// You are given a partially completed program that creates a list of dogs for an adoption shelter.
// Each dog has the corresponding information: name, gender, breed, age, and weight.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, the return types, or the parameters, you risk failing the automated test cases.
//
// The following will be accepted as input in the following format: "name:gender:breed:age:weight"
// Example Input: "Spot:M:Terrier:5:15.45" or "Daisy:Poodle:F:3:15"
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

#pragma warning(disable: 4996)

typedef enum { male = 0, female } gender; // enumeration type gender

struct dog {
	char name[30];
	gender genderValue;
	char breed[30];
	int age;
	float weight;
};

int count = 0; // the amount of dogs currently stored in the list (initialized at 0)

struct dog list[30]; // initialize list of dogs

					 // forward declaration of functions
void flush();
void branching(char);
void helper(char);
int add(char*, char*, char*, int, float, struct dog*); // 30 points
char* search(char*, int, struct dog*); // 10 points
void display();
void save(char* fileName);
void load(char* fileName); // 10 points

int main()
{
	load("Dog_List.txt"); // load list of dogs from file (if it exists)

	char ch = 'i';
	printf("Assignment 5: Array of Structs and Enum Types\n\n");
	printf("Dog Adoption Center\n\n");

	do
	{
		printf("Please enter your selection:\n");
		printf("\ta: add a new dog to the list\n");
		printf("\ts: search for a dog on the list\n");
		printf("\td: display list of dogs\n");
		printf("\tq: quit and save your list\n");
		ch = tolower(getchar());
		flush();
		branching(ch);
	} while (ch != 'q');

	save("Dog_List.txt"); // save list of dogs to file (overwrite if it exists)
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
	case 's': helper(c); break;
	case 'd': display(); break;
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

		int result = add(name, genderValueString, breed, age, weight, list);

		if (result == 0)
			printf("\nThat dog is already on the list\n\n");
		else
			printf("\nDog added to list successfully\n\n");
	}
	else // c = 's'
	{
		printf("\nPlease enter the dog's information in the following format:\n");
		printf("\tname:age\n");
		fgets(input, sizeof(input), stdin);

		char* name = strtok(input, ":"); // strtok used to parse string
		int age = atoi(strtok(NULL, ":")); // atoi used to convert string to int

		char* result = search(name, age, list);

		if (result == NULL)
			printf("\nThat dog is not on the list\n\n");
		else
			printf("\nBreed: %s\n\n", result);
	}
}

// Q1 : add (30 points)
// This function is used to insert a new dog into the list.
// Your list should be sorted alphabetically by name, so you need to search for the correct index to add into your list.
// If a dog already exists with the same name, then those dogs should be sorted by age.
// Do not allow for the same dog to be added to the list multiple times. (same name and same age).
// If the dog already exists on the list, return 0. If the dog is added to the list, return 1.
//
// NOTE: You must convert the string "genderValueString to an enum type and store it in the list. This will be tested.
// (You must store all of the required information correctly to pass all of the test cases)
// NOTE: You should not allow for the same dog to be added twice, you will lose points if you do not account for this.
// (That means that dogs on the list are allowed to have the same name OR the same age, but not both).
//
// You are not required to use pointer operations for your list but you may do so if you'd like. 
// 'list' is passed to this function for automated testing purposes only, it is global.
int add(char* name, char* genderValueString, char* breed, int age, float weight, struct dog* list)
{
	int genderValue = 0;

	if (genderValueString == 'm') {
		genderValue = 0;
	}
	else if (genderValueString == 'f') {
		genderValue = 1;
	}

	gender dogGender = genderValue;

	if (count == 0) {
		list[count].age = age; strcpy(list[count].name, name); list[count].genderValue = dogGender; strcpy(list[count].breed, breed); list[count].weight = weight;
		count++;
		return 1;

	} else {
		for (int i = 0; i < count; i++) {
			if (stricmp(name, list[i].name) == 0 && age == list[i].age) {
				return 0;
			}
		}

		list[count].age = age; strcpy(list[count].name, name); list[count].genderValue = dogGender; strcpy(list[count].breed, breed); list[count].weight = weight;
		count++;

		for (int j = 0; j < count; j++){
			
			int minElement = j;

			for (int k = j + 1; k < count; k++) {
				if (strcmp(list[k].name, list[minElement].name) < 0) {
					minElement = k;
				} else if (strcmp(list[k].name, list[minElement].name) == 0) {
					if (list[k].age < list[minElement].age) {
						minElement = k;
					}
				}
			} if (minElement != j) {
				struct dog switching; 
				switching = list[j]; 
				list[j] = list[minElement];
				list[minElement] = switching;
			}
		} return 1;
	} return 0;
}

// Q2 : search (10 points)
// This function is used to search for a dog on the list and returns the breed of that dog
// You will need to compare the search keys: name and age, with the stored name and age.
// If the dog exists in the list, return a String containing the breed of the requested dog.
// If the dog does not exist on the list, return NULL
char* search(char* name, int age, struct dog* list)
{
	if (count != 0) {
		for (int i = 0; i < count; i++){
			if (stricmp(name, list[i].name) == 0 && age == list[i].age) {
				return list[i].breed;
			}
		}
	} return NULL;
}

// This function displays the list of dogs and the information for each one. It is already implemented for you.
// It may be helpful to trace through this function to help you complete other sections of this assignment.
void display()
{
	char* genderValue = "Male";

	if (count == 0)
		printf("\nThere are no dogs on this list!\n\n");
	else {
		for (int i = 0; i < count; i++)
		{
			printf("\nName: %s\n", list[i].name);

			if (list[i].genderValue == male)
				genderValue = "Male";
			else if (list[i].genderValue == female)
				genderValue = "Female";

			printf("Breed: %s\n", list[i].breed);
			printf("Gender: %s\n", genderValue);
			printf("Age: %d years old\n", list[i].age);
			printf("Weight: %.2f lbs\n", list[i].weight);
		}
		printf("\n");
	}
}

// This function saves the array of structures to file. It is already implemented for you.
// You should understand how this code works so that you know how to use it for future assignments.
void save(char* fileName)
{
	FILE* file;

	file = fopen(fileName, "rb");

	fread(&count, sizeof(count), 1, file);
	for (int i = 0; i < count; i++)
	{
		fread(list[i].name, sizeof(list[i].name), 1, file);
		fread(list[i].breed, sizeof(list[i].breed), 1, file);
		fread(&list[i].genderValue, sizeof(list[i].genderValue), 1, file);
		fread(&list[i].age, sizeof(list[i].age), 1, file);
		fread(&list[i].weight, sizeof(list[i].weight), 1, file);
	}
	fclose(file);
}

// Q3:  Load file (10 points)
// This function loads data from file and build the the array of structures. 
// Use the save function given above as an example on how to write this function.
void load(char* fileName)
{
	FILE *fileBuffer;
	fileBuffer = fopen(fileName, "wb");
	if (fileBuffer != NULL) {
		fwrite(&count, sizeof(count), 1, fileBuffer);
		for (int i = 0; i < count; i++) {
			fwrite(list[i].name, sizeof(list[i].name), 1, fileBuffer);
			fwrite(list[i].breed, sizeof(list[i].breed), 1, fileBuffer);
			fwrite(&list[i].genderValue, sizeof(list[i].genderValue), 1, fileBuffer);
			fwrite(&list[i].age, sizeof(list[i].age), 1, fileBuffer);
			fwrite(&list[i].weight, sizeof(list[i].weight), 1, fileBuffer);
		}fclose(fileBuffer);
	}return NULL;
}