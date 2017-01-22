// Q1b: Create Cat Class
// Part 1: Create a child class of the Pet class named 'Cat'
// See the add function in hw10.cpp for proper use of this function.
// Part2: Declare constructor which accepts the same 3 parameters as the parent class Pet.
// Pass the 3 parameters to the super constructor in the Pet class.
// Part 3: Re-declare the method display (virtual method found inside of parent class Pet)

#include "Pet.h"

class Cat : public Pet { public: Cat(string pet_name, string pet_breed, Type pet_type) : Pet(pet_name, pet_breed, pet_type) {}; void display(); };