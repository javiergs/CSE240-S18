#ifndef _PET_H_
#define _PET_H_
// These two lines of preprocessor directives, and the one at the end #endif,  
// prevent the header file from being included (linked in) multiple times, 
// when it is used multiple times by the user.

#include "Checkup.h"

#include <string>
using namespace std;

class Pet {
private:
	string name, breed; // private local variables

public:
	Pet(string pet_name, string pet_breed); // constructor

	Checkup *checkups; // linked list of checkups

	// accessor methods
	string getName();
	string getBreed();

	// class methods
	void addCheckup(string date);
	string lastCheckup();
};

#endif // _PET_H_