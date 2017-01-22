#include "Checkup.h"

Checkup::Checkup(string new_date) {
	date = new_date;
	//next = NULL;
}

string Checkup::getDate() {
	return date;
}