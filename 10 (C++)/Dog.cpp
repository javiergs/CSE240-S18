// Q2a: Define Display for Dog class
// Define the method display that you declared within the Dog class in the header file
// Information should be printed in the following format:
// Name: <name>
// Breed: <breed>
// Type: Dog
// (See the print_all function in hw10.cpp for proper use of this function.)

#include "Dog.h"

#include <iostream>
#include <fstream>
#include <string>

void Dog::display() { cout << endl << "Name:" << getName(); cout << endl << "Breed:" << getBreed(); cout << endl << "Type: Dog" << endl; }