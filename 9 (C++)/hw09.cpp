// READ BEFORE YOU START:
// You are given a partially completed program that creates a list of pets with their list of checkups.
// Each pet has the corresponding information: name, breed, and a linked list of checkups.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, the return types, or the parameters, you risk failing the automated test cases.
//
// You are to assume that all input is valid:
// Valid name:	String containing alphabetical letters beginning with a capital letter
// Valid breed: String containing alphabetical letters beginning with a capital letter
// Valid date:	String in the following format: "MM/DD/YYYY" ex: "01/01/2010"
// All input will be a valid length and no more than the allowed amount of memory will be used
//
// Q1 : CLASS METHODS Part 1 : Constructor and Accessor Methods for Pet class in Pet.cpp file	( 5 points)
// Q2 : CLASS METHODS Part 2 : Class methods for Pet class in Pet.cpp file						(10 points)
// Q3 : Add Function in hw09.cpp file															( 5 points)
// Q4 : Search Function in hw09.cpp file														(10 points)
// Q5 : Remove One Function in hw09.cpp file													(15 points)
// Q6 : Implement cin / cout for the lines in main without modifying the functionality			( 5 points)

#include <iostream>
#include <fstream>
#include <string>

#include "Container.h"
#include "Pet.h"
#include "Checkup.h"

using namespace std;

// forward declarations
void flush();
void branching(char);
void helper(char);
void add_pet(string, string);
Pet* search_pet(string, string);
void remove_pet(string, string);

void clean_up(Pet*);
void print_all();
void remove_all();

Container* list = NULL; // global list

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Use to check for memory leaks in VS

	char ch = 'i';

	do {

		// Q6: Implement cin / cout for the lines below without modifying the functionality (5 points)
		// (change all printf statements to cout and read the next char using cin)
		cout << "Please enter your selection" << endl;
		cout << "\ta: add a new pet to the list" << endl;
		cout << "\tc: add a new checkup for a pet" << endl;
		cout << "\tr: remove a pet from the list" << endl;
		cout << "\tp: print all pets on the list" << endl;
		cout << "\tq: quit" << endl; cin >> ch; flush();
		branching(ch);
	} while (ch != 'q');

	remove_all();
	list = NULL;
	return 0;
}

void flush()
{
	int c;
	do c = getchar(); while (c != '\n' && c != EOF);
}

void branching(char c)
{
	switch (c) {
	case 'a':
	case 'c':
	case 'r':
	case 'p':
		helper(c);
		break;
	case 'q':
		break;
	default:
		printf("\nInvalid input!\n\n");
	}
}

// The helper function is used to determine how much data is needed and which function to send that data to.
// It uses pointers and values that are returned from some functions to produce the correct ouput.
// There is no implementation needed here, but you should study this function and know how it works.
// It is always helpful to understand how the code works before implementing new features.
// Do not change anything in this function or you risk failing the automated test cases.
void helper(char c)
{
	string name, breed;

	if (c == 'p')
		print_all();
	else
	{
		cout << endl << "Please enter the pet's name: " << endl;
		cin >> name;
		cout << "Please enter the pet's breed: " << endl;
		cin >> breed; flush();

		Pet* pet_result = search_pet(name, breed);

		if (c == 'a') // add pet
		{
			if (pet_result == NULL)
			{
				add_pet(name, breed);
				cout << endl << "Pet added." << endl << endl;
			}
			else
				cout << endl << "Pet already on list." << endl << endl;
		}
		else if (c == 'c') // add checkup
		{
			if (pet_result == NULL)
			{
				cout << endl << "Pet not found." << endl << endl;
				return;
			}

			string date;
			cout << "Please enter the date of the checkup: " << endl;
			cin >> date; flush();

			pet_result->addCheckup(date);
			cout << endl << "Checkup added." << endl << endl;
		}
		else if (c == 'r') // remove pet
		{
			if (pet_result == NULL)
			{
				cout << endl << "Pet not found." << endl << endl;
				return;
			}

			remove_pet(name, breed);
			cout << endl << "Pet removed from the list." << endl << endl;
		}
	}
}

// Q3: Add Pet (5 points)
// This function will be used to add a new pet to the head of you linked list of containers, no need for sorting.
// The search function is called before this function, therefore you can assume the pet is not already on the list.
// If the pet is added to the list, return 1. If the pet already exists on the list (not added), return 0.
void add_pet(string name, string breed)
{
	Container* cont = new Container();

	cont->pet = new Pet(name, breed);

	cont->next = list; list = cont;
}

// Q4: Search (10 points)
// This function will be used to search for a pet on the list. 
// Pets on the list may have the same name OR the same breed, but should not have the same name AND breed.
// Therefore, you must traverse the list and return a pointer to a 'Pet' with the desired name AND breed.
// If the pet does not exist on the list, return NULL. (See helper function for use of this function).
Pet* search_pet(string name, string breed)
{
	Container* cont = list;
	while (cont != NULL) {
		if (cont->pet->getName() == name && cont->pet->getBreed() == breed) {
			return cont->pet;
		}   cont = cont->next;
	}       return NULL;
}

// Q5: Remove Pet (15 points)
// This function will be used to remove a pet from the list. 
// Traverse the list and use the parameters to remove the pet.
// Use proper memory management to ensure no memory leaks..
void remove_pet(string name, string breed)
{
	Container *base = list; Container *beforeBase = list; Checkup *tempPlace;

	if (list->pet->getName() == name && list->pet->getBreed() == breed)
	{
		while (list->pet->checkups != NULL) { tempPlace = list->pet->checkups; list->pet->checkups = list->pet->checkups->next; delete(tempPlace); }

		list = list->next; delete(base->pet); delete(base);
	}
	else
	{
		base = list->next;
		while (beforeBase->next != NULL) {
			if (base->pet->getName().compare(name) == 0) {
				while (base->pet->checkups != NULL) { tempPlace = base->pet->checkups; base->pet->checkups = base->pet->checkups->next; delete(tempPlace); }
				beforeBase->next = base->next; delete(base->pet); delete(base);
				break;
			} beforeBase = base; base = base->next;
		}
	}
}

// This function is already implemented for you. It traverses the list and removes all pets to ensure no memory leaks.
void remove_all()
{
	while (list != NULL)
	{
		Container* container_to_be_removed = list;
		list = list->next;

		while (container_to_be_removed->pet->checkups != NULL)
		{
			Checkup *checkup_to_be_removed = container_to_be_removed->pet->checkups;
			container_to_be_removed->pet->checkups = container_to_be_removed->pet->checkups->next;
			delete checkup_to_be_removed;
		}

		delete container_to_be_removed->pet;
		delete container_to_be_removed;
	}
}

// This function is already implemented for you. It prints all of the pets in the list in an organized format.
void print_all()
{
	if (list == NULL) cout << endl << "List is empty!" << endl << endl;

	Container *container_traverser = list;

	while (container_traverser != NULL)
	{
		cout << endl <<
			"Name: " << container_traverser->pet->getName() << endl <<
			"Breed: " << container_traverser->pet->getBreed() << endl;

		string last_checkup = container_traverser->pet->lastCheckup();

		if (last_checkup.empty())
			cout << "Last Checkup: " << "N/A" << endl << endl;
		else
			cout << "Last Checkup: " << last_checkup << endl << endl;


		container_traverser = container_traverser->next;
	}
}