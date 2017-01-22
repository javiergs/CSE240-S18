// Q2b: Define Display for Cat class
// Define the method display that you declared within the Cat class in the header file
// Information should be printed in the following format:
// Name: <name>
// Breed: <breed>
// Type: Cat
// (See the print_all function in hw10.cpp for proper use of this function.)

#include "Cat.h"

#include <iostream>
#include <fstream>
#include <string>

void Cat::display() { cout << endl << "Name:" << getName(); cout << endl << "Breed:" << getBreed(); cout << endl << "Type: Cat" << endl; }