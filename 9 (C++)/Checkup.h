#ifndef _CHECKUP_H_
#define _CHECKUP_H_
// These two lines of preprocessor directives, and the one at the end: #endif,  
// prevent the header file from being included (linked in) multiple times, 
// when it is used multiple times by the user.

#include <string>
using namespace std;

class Checkup {
private:
	// private local variables
	string date;

public:
	Checkup *next;
	Checkup(string date); // constructor
	string getDate(); // accessor
};

#endif // _CHECKUP_H_