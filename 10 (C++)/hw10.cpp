// READ BEFORE YOU START:
// You are given a partially completed program that creates a list of pets.
// Each pet has the corresponding information: name, breed, and type.
// In the Pet.h file, you will find the definition for this enum 'type'.
// Pets on the list can be 2 different 'types' : either a dog or a cat.
// The classes Dog and Cat are subclasses of the Pet class (found in Pet.h).
// Both of these classes will have their own use of the virtual display method.
//
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, the return types, or the parameters, you risk failing the automated test cases.
//
// You are to assume that all input is valid:
// Valid name:	String containing alphabetical letters beginning with a capital letter
// Valid breed: String containing alphabetical letters beginning with a capital letter
// All input will be a valid length and no more than the allowed amount of memory will be used

#include "Container.h"
#include "Pet.h"
#include "Dog.h"
#include "Cat.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// forward declarations
void flush();
void branching(char);
void helper(char);
void add_pet(string, string, Type);
Pet* search_pet(string, string, Type);
void remove_pet(string, string, Type);
void remove_all();
void print_all();

void save(string); // 10 points
void load(string); // 10 points

Container* list = NULL; // global list

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Use to check for memory leaks in VS

	load("Pets.txt");

	char ch = 'i';

	do {
		cout << "Please enter your selection" << endl;
		cout << "\ta: add a new pet to the list" << endl;
		cout << "\tc: change the breed of a pet" << endl;
		cout << "\tr: remove a pet from the list" << endl;
		cout << "\tp: print all pets on the list" << endl;
		cout << "\tq: quit and save list of pets" << endl;
		cin >> ch;
		flush();
		branching(ch);
	} while (ch != 'q');

	save("Pets.txt");
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
	Type type;
	int type_check = -1;

	if (c == 'p')
		print_all();
	else
	{
		cout << endl << "Please enter the pet's name: " << endl;
		cin >> name;
		cout << "Please enter the pet's breed: " << endl;
		cin >> breed;

		while (!(type_check == 0 || type_check == 1))
		{
			cout << endl << "Please select one of the following: " << endl;
			cout << "0. Dog " << endl;
			cout << "1. Cat" << endl;
			cin >> type_check;
		}

		type = (Type)type_check;

		Pet* pet_result = search_pet(name, breed, type);

		if (c == 'a') // add pet
		{
			if (pet_result == NULL)
			{
				add_pet(name, breed, type);
				cout << endl << "Pet added." << endl << endl;
			}
			else
				cout << endl << "Pet already on list." << endl << endl;
		}
		else if (c == 'c') // change pet breed
		{
			if (pet_result == NULL)
			{
				cout << endl << "Pet not found." << endl << endl;
				return;
			}

			cout << endl << "Please enter the new breed for this pet: " << endl;
			cin >> breed; flush();

			// Q3c: Call Change Breed Function
			changeBreed(pet_result, breed);

			cout << endl << "Pet's breed changed." << endl << endl;
		}
		else if (c == 'r') // remove pet
		{
			if (pet_result == NULL)
			{
				cout << endl << "Pet not found." << endl << endl;
				return;
			}

			remove_pet(name, breed, type);
			cout << endl << "Pet removed from the list." << endl << endl;
		}
	}
}

// Q3b: Define Friend Function Change Breed
// Define the function changeBreed that is declared within the Pet.h file.
// This function sets the breed value of the Pet pointer to the value of the string parameter.

void changeBreed(Pet* pet, string breed) { 
	pet->breed = breed; 
}

// Q4: Add Pet
// This function will be used to add a new pet to the tail of the global linked list.
// You will need to use the enum ‘type’ variable to determine which constructor to use.
// Remember that search is called before this function, therefore, the new pet is not on the list.
void add_pet(string name, string breed, Type type)
{
	Container *newContainer = new Container();
	Pet *newPet;
	if (type == dog) {
		newPet = new Dog(name, breed, type);
	}
	else {
		newPet = new Cat(name, breed, type);
	}

	newContainer->pet = newPet;
	newContainer->next = NULL;

	if (list == NULL) {
		list = newContainer;
	}
	else
	{
		Container* temp = list;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newContainer;
	}
}

// No implementation needed here, however it may be helpful to review this function
Pet* search_pet(string name, string breed, Type type)
{
	Container* container_traverser = list;

	while (container_traverser != NULL)
	{
		if (container_traverser->pet->getName() == name
			&& container_traverser->pet->getBreed() == breed
			&& container_traverser->pet->getType() == type)
			return container_traverser->pet;

		container_traverser = container_traverser->next;
	}

	return NULL;
}

// No implementation needed here, however it may be helpful to review this function
void remove_pet(string name, string breed, Type type)
{
	Container* to_be_removed;

	if (list->pet->getName() == name
		&& list->pet->getBreed() == breed
		&& list->pet->getType() == type)
	{
		to_be_removed = list;
		list = list->next;
		delete to_be_removed->pet;
		delete to_be_removed;
		return;
	}

	Container* container_traverser = list->next;
	Container* container_follower = list;

	while (container_traverser != NULL)
	{
		if (container_traverser->pet->getName() == name
			&& container_traverser->pet->getBreed() == breed
			&& container_traverser->pet->getType() == type)
		{
			to_be_removed = container_traverser;
			container_traverser = container_traverser->next;
			container_follower->next = container_traverser;
			delete to_be_removed->pet;
			delete to_be_removed;
			return;
		}
		container_follower = container_traverser;
		container_traverser = container_traverser->next;
	}
}

// No implementation needed here, however it may be helpful to review this function
void remove_all()
{
	while (list != NULL)
	{
		Container* temp = list;
		list = list->next;
		delete temp->pet;
		delete temp;
	}
}

// This function uses the virtual display() method of the Dog and Cat classes to print all Pets in an oragnized format.
void print_all()
{
	Container *container_traverser = list;

	if (list == NULL)
		cout << endl << "List is empty!" << endl << endl;

	while (container_traverser != NULL)
	{
		container_traverser->pet->display();
		container_traverser = container_traverser->next;
	}
}

// Q5a: Save (5 points)
// Save the linked list of 
//pets to a file using ofstream.
// You will need to come up with a way to store the amount of Containers in linked list.
// Hint: You may want to cast the enum 'type' to an int before writing it to the file.
void save(string fileName)
{ 
	int count = 0;
	Container *temp = list;
	ofstream myFileVar;
	while (temp != NULL) { temp = temp->next; count++; }
	myFileVar.open(fileName); if (myFileVar.is_open()) { myFileVar << count<<endl; } temp = list;
	while (temp != NULL) {
		myFileVar << temp->pet->getName() << endl; myFileVar << temp->pet->getBreed() << endl; int typeInt = int(temp->pet->getType()); myFileVar <<typeInt << endl; temp = temp->next;
	} myFileVar.close();
}

// Q5b: Load (5 points)
// Load the linked list of pets from a file using ifstream.
// You will need to create the linked list in the same order that is was saved to a file.
// You will need to create a new node for the linked list, then add it to the tail of the list. 
// Hint: If you casted the enum 'type' to an int, you will need to cast it back to a 'Type'.
// You will use the 'type' variable read from the file to determine which constructor to use.
void load(string fileName)
{
	int count = 0; Container * temp = list; ifstream myFileVar; myFileVar.open (fileName);
		if(myFileVar.is_open())  { myFileVar >> count; 
		for (int i = 0; i < count; i++) {
			string name; string breed; int typePet; myFileVar >> name; myFileVar >> breed; myFileVar >> typePet; Type type = Type(typePet); add_pet(name, breed, type);
		}myFileVar.close();
	}
}