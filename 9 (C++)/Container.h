#ifndef _CONTAINER_H_
#define _CONTAINER_H_
// These two lines of preprocessor directives, and the one at the end #endif,  
// prevent the header file from being included (linked in) multiple times, 
// when it is used multiple times by the user.

#include "Pet.h"

class Container {
public:
	Pet *pet;
	Container *next;
	Container(); // constructor
};

#endif // _CONTAINER_H_