#ifndef FILE_H
#define FILE_H

#include "contact.h"
//Saves the current address book to the CSV file 
void saveContactsToFile(AddressBook *addressBook);
//Load all contacts from the CSV file into memory
void loadContactsFromFile(AddressBook *addressBook);

#endif
