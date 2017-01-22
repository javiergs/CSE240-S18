// READ BEFORE YOU START:
// Please read the given Word document for the project description with an illustrartive diagram.
// You are given a partially completed program that creates a list of dogs for an adoption shelter.
// Each dog has the corresponding information: name, breed, and a linked list of checkups.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, return types, or parameters, you risk failing test cases.
//
// Note, Textbook Section 2.10 gives a case study on complex linked list operations. 
// This project is based on that case study. Make sure you read the code in section 2.10.

// The following will be accepted as input in the following format: "name:breed"
// Example Input:	"Spot:Terrier" or "Daisy:Poodle"
// Valid name:		String containing alphabetical letters beginning with a capital letter
// Valid breed:		String containing alphabetical letters beginning with a capital letter
// Valid date:		String in the following format: "MM/DD/YYYY" ex: "01/01/2010"
// All input will be a valid length and no more than the allowed number of dogs will be added to the linked list.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// included to check for memory leaks
#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#pragma warning(disable: 4996)

// used to create a linked list of containers, each contaning a "dog"
struct container {
	struct dog *dog;
	struct container *next;
} *list = NULL;

// used to hold dog information and linked list of "checkups"
struct dog {
	char name[30];
	char breed[30];
	struct checkup *checkups;
};

// used to create a linked list of checkups containing "dates"
struct checkup {
	char date[30];
	struct checkup *next;
};

// forward declaration of functions that have already been implemented
void flush();
void branching(char);
void helper(char);
void remove_all(struct container*);
void display(struct container*);

// the following forward declarations are for functions that require implementation

// return type		// name and parameters				// points
void				add_dog(char*, char*);				//  5
struct dog*			search_dog(char*);					//  5
void				add_checkup(char*, char*);			// 10
char*				last_checkup(char*);				// 15
void				remove_one(char*);					// 15
														//													Total: 50 points for hw07

struct container*	list_of_breed(char*);				// 25
struct container*	list_by_name();						// 25
														//													Total: 50 points for hw08

int main()
{
	char ch = 'i';

	printf("Dog Adoption Center\n\n");

	do
	{
		printf("Please enter your selection:\n");
		printf("\ta: add a new dog to the list\n");
		printf("\ts: search for a dog on the list\n");
		printf("\tr: remove a dog from the list\n");
		printf("\tc: add a checkup date for dog\n");
		printf("\tl: display last checkup for a dog\n");
		printf("\tn: display list of dogs by name\n");
		printf("\tb: display list of dogs of breed\n");
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
	case 'c':
	case 'l':
	case 'b':
	case 'n': helper(c); break;
	case 'q': break;
	default: printf("Invalid input!\n");
	}
}

// This function will determine what info is needed and which function to send that info to.
// It uses values that are returned from some functions to produce the correct ouput.
// There is no implementation needed here, but you should trace the code and know how it works.
// It is always helpful to understand how the code works before implementing new features.
// Do not change anything in this function or you risk failing the automated test cases.
void helper(char c)
{
	if (c == 'a')
	{
		char input[100];

		printf("\nPlease enter the dog's info in the following format:\n");
		printf("name:breed\n");
		fgets(input, sizeof(input), stdin);

		// discard '\n' chars attached to input
		input[strlen(input) - 1] = '\0';

		char* name = strtok(input, ":"); // strtok used to parse string
		char* breed = strtok(NULL, ":");

		struct dog* result = search_dog(name);

		if (result == NULL)
		{
			add_dog(name, breed);
			printf("\nDog added to list successfully\n\n");
		}
		else
			printf("\nThat dog is already on the list\n\n");
	}
	else if (c == 's' || c == 'r' || c == 'c' || c == 'l')
	{
		char name[30];

		printf("\nPlease enter the dog's name:\n");
		fgets(name, sizeof(name), stdin);

		// discard '\n' chars attached to input
		name[strlen(name) - 1] = '\0';

		struct dog* result = search_dog(name);

		if (result == NULL)
			printf("\nThat dog is not on the list\n\n");
		else if (c == 's')
			printf("\nBreed: %s\n\n", result->breed);
		else if (c == 'r')
		{
			remove_one(name);
			printf("\nDog removed from the list\n\n");
		}
		else if (c == 'c')
		{
			char date[30];

			printf("\nPlease enter the date of the checkup:\n");
			fgets(date, sizeof(date), stdin);

			// discard '\n' chars attached to input
			date[strlen(date) - 1] = '\0';

			add_checkup(name, date);
			printf("\nCheckup added\n\n");
		}
		else if (c == 'l')
		{
			char* result = last_checkup(name);
			if (result == NULL)
				printf("\nNo checkups documented.\n\n");
			else
				printf("\nLast checkup: %s\n\n", result);
		}
	}
	else if (c == 'b')
	{
		char breed[30];

		printf("\nPlease enter the breed:\n");
		fgets(breed, sizeof(breed), stdin);

		// discard '\n' chars attached to input
		breed[strlen(breed) - 1] = '\0';

		struct container* result = list_of_breed(breed);

		printf("\nList of dogs with breed type %s:\n\n", breed);

		display(result);
		remove_all(result);
		result = NULL;
	}
	else // c = 'n'
	{
		struct container* result = list_by_name();

		printf("\nList of dogs sorted by name:\n\n");

		display(result);
		remove_all(result);
		result = NULL;
	}
}

// This function recursively removes all dogs from the linked list of containers
// Notice that all of the checkups for all of the dogs must be removed as well
void remove_all(struct container* dogs)
{
	struct checkup* temp;
	if (dogs != NULL)
	{
		remove_all(dogs->next);
		while (dogs->dog->checkups != NULL)
		{
			temp = dogs->dog->checkups;
			dogs->dog->checkups = dogs->dog->checkups->next;
			free(temp);
		}
		free(dogs->dog);
		free(dogs);
	}
}

// This function prints the list of dogs in an organized format
// It may be useful to trace this code before you get started
void display(struct container* dogs)
{
	struct container* container_traverser = dogs;

	if (container_traverser == NULL)
	{
		printf("\nThere are no dogs on this list!\n\n");
		return;
	}

	while (container_traverser != NULL) // traverse list of dogs
	{
		printf("Name: %s\n", container_traverser->dog->name);
		printf("Breed: %s\n", container_traverser->dog->breed);
		printf("Checkups on file: ");

		struct checkup* ptr = container_traverser->dog->checkups;
		if (ptr == NULL)
		{
			printf("No checkups documented.");
		}
		else
		{
			while (ptr != NULL) // traverse list of checkups
			{
				printf("\n%s", ptr->date);
				ptr = ptr->next;
			}
		}

		printf("\n\n"); // formatting
		container_traverser = container_traverser->next;
	}
}

// hw07 Q1 : add (5 points)
// This function should add dog to the head of the list of containers.
// The function search_dog() is called before calling this function, 
// therefore you can assume that the dog is not already on the list.
void add_dog(char* name, char* breed, int value)
{
	struct dog *insertDog; struct container *curConts;
	
	insertDog = (struct dog *) malloc(sizeof(struct dog)); curConts = (struct container *) malloc(sizeof(struct container));
	
	strcpy(insertDog->name, name); strcpy(insertDog->breed, breed);
	
	insertDog->checkups = NULL;
	
	curConts->dog = insertDog; curConts->next = list; list = curConts;
}

// hw07 Q2 : search (5 points)
// In this function, you are passed the name of a dog to find its breed.
// If the dog exists on the list, return a pointer to the requested dog. If not, return NULL.
// (You must return a pointer to a node in your list. Do not create a pointer that just includes the breed)
// (Remember that it is enough to search for a dog by only their name since no 2 dogs will have the same name)
struct dog* search_dog(char* name)
{
	struct container *insertCont = list;

	while (insertCont != NULL){
		if (strcmp(insertCont->dog->name, name) == 0) { return insertCont->dog; } insertCont = insertCont->next;
	} return NULL;
}

// hw07 Q3: add_checkup (10)
// In this function, you are passed the name of a dog and a date of a checkup.
// You should add the date to the tail of the linked list of the dogs "checkups".
// You can assume that all checkups will be added in chronological order.
// The function search_dog() is called before calling this function, 
// therefore you can assume that the dog is already on the dog list and 
// the new checkup date is not on the checkups list.
void add_checkup(char* name, char* date)
{
	struct dog *dogLocation;  struct checkup *nextCheckup;
	nextCheckup = (struct checkup *) malloc(sizeof(struct checkup));

	strcpy(nextCheckup->date, date);
	nextCheckup->next = NULL;

	dogLocation = search_dog(name);

	struct checkup *instList = dogLocation->checkups;  struct checkup *temp = instList;

	if (instList == NULL) { instList = nextCheckup; temp = nextCheckup;}
	
	else
	{
		while (temp->next != NULL) { temp = temp->next; }

		temp->next = nextCheckup; temp = temp->next;

	}   dogLocation->checkups = instList;
}

// hw07 Q4: last_checkup (15)
// In this function, you are passed the name of a dog to find the date of its last checkup.
// Remember that checkups are stored in chronological order,
// therefore the last checkup will be at the tail of the linked list of checkups.
// If the dog has not yet had a checkup added to its list of checkups, return NULL.
// The function search_dog() is called before calling this function, 
// therefore you can assume that the dog is not already on the list.
char* last_checkup(char* name)
{
	struct dog *dogLocation; struct dog *nextDog;

	dogLocation = search_dog(name); nextDog = dogLocation;

	if (dogLocation->checkups == NULL) { return NULL; }
	else {
		while (nextDog->checkups->next != NULL) { nextDog->checkups = nextDog->checkups->next; } return nextDog->checkups->date;
	}
}

// hw07 Q5: remove_one (15)
// In this function, you are passed the name of a dog to remove the corresponding dog from the list.
// The search function is called before this function so you can assume that the dog is on the list.
// You will need to find the dog and remove it using proper memory management to ensure no memory leaks.
void remove_one(char* name)
{
	struct container *prvCont = list; struct container *crntCont = list; struct checkup *tempCheckup;
	if (strcmp(list->dog->name, name) == 0){
		
		while (list->dog->checkups != NULL){ tempCheckup = list->dog->checkups; list->dog->checkups = list->dog->checkups->next; free(tempCheckup); }
		
		list = list->next; free(crntCont->dog); free(crntCont);

	} else

	{ crntCont = list->next;
		while (prvCont->next != NULL) {
			if (strcmp(crntCont->dog->name, name) == 0) {

				while (crntCont->dog->checkups != NULL) { tempCheckup = crntCont->dog->checkups; crntCont->dog->checkups = crntCont->dog->checkups->next; free(tempCheckup); }
				
				prvCont->next = crntCont->next; free(crntCont->dog); free(crntCont); break;

			}   prvCont = crntCont;
			    crntCont = crntCont->next;
		}
	}
}

// hw08 Q1: list_of_breed (25)
// This function is used to construct a new linked list of containers from the global list of containers.
// The returned list should only contain dogs which are of the breed type parameter (container->dog->breed).
// No sorting is required for this list.
// The list that you return will be cleaned up for you by the remove_all() function (see helper() function),
// however you will need to make sure that you leave no dangling references (those cause memory leaks too).
// Notice that the returned list will need to contain all dog and checkup information to be displayed.
// This function should NOT modify the global linked list.
struct container* list_of_breed(char* breed)
{
	struct container *dogBreed = NULL; struct container *curCont = list;
	while (curCont != NULL)
	{
		if (strcmp(curCont->dog->breed, breed) == 0) {
			struct dog *dogLocation; struct container *nextCont;

			dogLocation = (struct dog *) malloc(sizeof(struct dog)); nextCont = (struct container *) malloc(sizeof(struct container));

			strcpy(dogLocation->breed, curCont->dog->breed); strcpy(dogLocation->name, curCont->dog->name); dogLocation->checkups = NULL;

			struct checkup *nodeCheck = curCont->dog->checkups; struct checkup *curCheck = nodeCheck;
			struct checkup *dogCheck = NULL; struct checkup *nextDogCheck = dogCheck;

			if (nodeCheck == NULL) { dogLocation->checkups = NULL; }
			else {
				while (curCheck != NULL) {
					struct checkup *newCheck;
					newCheck = (struct checkup *) malloc(sizeof(struct checkup));
					strcpy(newCheck->date, curCheck->date);
					if (dogCheck == NULL) { newCheck->next = NULL; dogCheck = newCheck; nextDogCheck = dogCheck; }
					else {
						while (nextDogCheck->next != NULL) { nextDogCheck = nextDogCheck->next; }
						
						newCheck->next = nextDogCheck->next; nextDogCheck->next = newCheck;

					} curCheck = curCheck->next;
				}     dogLocation->checkups = dogCheck;
			}
			nextCont->dog = dogLocation; nextCont->next = dogBreed; dogBreed = nextCont;
		}   curCont = curCont->next;
	}       return dogBreed;
}

// hw08 Q2: list_by_name (25)
// This function is used to construct a new linked list of containers from the global list of containers.
// The returned list should be sorted alphabetically by each container's dog's name (container->dog->name).
// The list that you return will be cleaned up for you by the remove_all() function (see helper() function),
// however you will need to make sure that you leave no dangling references (those cause memory leaks too).
// Notice that the returned list will need to contain all dog and checkup information to be displayed.
// You can again assume that for this assignment, no 2 dogs on the list will have the same name.
// You may want to use the function that you have written above as a blueprint for this function.
// This function should NOT modify the global linked list.
struct container* list_by_name()
{
	struct container *curCont = list;  struct container *nameOrder = NULL; struct container *curName = nameOrder;
	while (curCont != NULL) {
		struct dog *newDog; struct container *newContainer;
		newDog = (struct dog *) malloc(sizeof(struct dog)); newContainer = (struct container *) malloc(sizeof(struct container));

		strcpy(newDog->name, curCont->dog->name); strcpy(newDog->breed, curCont->dog->breed);

		struct checkup *checkH = curCont->dog->checkups; struct checkup *contChecks = checkH;
		struct checkup *locDog = NULL; struct checkup *newDogCheckupMove = locDog;
		if (checkH == NULL) { newDog->checkups = NULL; }
		else {
			while (contChecks != NULL) {
				struct checkup *cuCheck;
				cuCheck = (struct checkup *) malloc(sizeof(struct checkup));
				strcpy(cuCheck->date, contChecks->date);
				if (locDog == NULL) {
					cuCheck->next = NULL; locDog = cuCheck; newDogCheckupMove = locDog;
				} 
				else
				{
					while (newDogCheckupMove->next != NULL){ newDogCheckupMove = newDogCheckupMove->next; }
					
					cuCheck->next = newDogCheckupMove->next; newDogCheckupMove->next = cuCheck;

				} contChecks = contChecks->next;
			}     newDog->checkups = locDog;
	   }newContainer->dog = newDog;
		curName = nameOrder;
		if (nameOrder == NULL) { newContainer->next = NULL; nameOrder = newContainer; }
		else if (strcmp(nameOrder->dog->name, newContainer->dog->name) > 0) { newContainer->next = nameOrder; nameOrder = newContainer; }
		else {	
			int x = 5; // Signal to enter the if statement
			while (curName->next != NULL) {
				if (strcmp(curName->next->dog->name, newContainer->dog->name) > 0 && strcmp(curName->dog->name, newContainer->dog->name) < 0) {
					
					newContainer->next = curName->next; curName->next = newContainer;
					
					x = 0;
					
					break;
				}   curName = curName->next;
			}       if (x == 5) { newContainer->next = NULL; curName->next = newContainer; }
		}           curCont = curCont->next;
	}               return nameOrder;
}