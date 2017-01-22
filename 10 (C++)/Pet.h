#ifndef _PET_H_
#define _PET_H_

#include <string>
using namespace std;

enum Type { dog = 0, cat };

class Pet {
private:
	string name, breed; // private local variables
	Type type;

public:
	Pet(string pet_name, string pet_breed, Type pet_type); // constructor

	// accessor methods
	string getName();
	string getBreed();
	Type getType();

	// Q3a: Declare Friend Function Change Breed
	// Declare a “friend function” named changeBreed which has 2 parameters and no return value.
	// The first parameter is a pointer to a Pet, and the second is a string.
	// See the helper function in hw10.cpp for proper use of this function.

	friend void changeBreed(Pet* pet, string breed);
		virtual void display(){ }
};

#endif // _PET_H_