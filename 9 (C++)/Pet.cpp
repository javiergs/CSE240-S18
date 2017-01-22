#include "Pet.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

// Q1 : CLASS METHODS Part 1 : Constructor and Accessor Methods for Pet (5 points)

// Constructor
// Create a constructor for the class Pet which takes 2 string parameters (see helper function for use of constructor).
// Use the 2 string parameters to initialize the 2 private local variables name and breed.
// HINT: Don't forget to initialize your linked list of checkups to NULL.
Pet::Pet(string petName, string petBreed) { name = petName; breed = petBreed; checkups = NULL; }

// Accessor Methods
// Create accessor methods for both private local strings name and breed (see print_all function for use of these methods).

string Pet::getName() { return name; }

string Pet::getBreed() { return breed; }

// Q2 : CLASS METHODS Part 2 : Class Methods for Pet (10 points)

// Create a method named "addCheckup" which has one string parameter and no return type (see helper function for use).
// This method is used to add a new date to the pet's linked list of checkups. The string parameter is the date of checkup.
// You should add the date to the tail of the linked list "checkups". Checkups will be added in chronological order.

void Pet::addCheckup(string checkupDate)
{
	Checkup *newCheck = new Checkup(checkupDate); Checkup *tempL = checkups; Checkup *movingList = tempL;

	if (tempL == NULL) { tempL = newCheck; }
	else {
		while (movingList->next != NULL) { movingList = movingList->next; }

		movingList->next = newCheck; newCheck->next = NULL;
	}   checkups = tempL;
}

// Create a method named "lastCheckup" which has no parameters and returns a string (see print_all function for use).
// This method will be used to return a string for the date of the last checkup for this pet.
// If the pet has not yet had a checkups, return an empty string.

string Pet::lastCheckup()
{
	Checkup *movingList = checkups;

	if (movingList != NULL) { while (movingList->next != NULL) { movingList = movingList->next; } return movingList->getDate(); }
	
	else { return ""; }
}