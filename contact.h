#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

//Each contact
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;
//Database
typedef struct {
    Contact contacts[100];
    int contactCount; 
} AddressBook;

//creates a new contact after checking all fields for valid input
void createContact(AddressBook *addressBook);
//Let the user choose how to search and display the matching results
void searchContact(AddressBook *addressBook);
//Update one field on existing contact after verification
void editContact(AddressBook *addressBook);
//Delete or remove the selected contact from the list
void deleteContact(AddressBook *addressBook);
//print all the contacts available in the file in assending order
void listContacts(AddressBook *addressBook);
//Load all the saved details from the file before executing
void initialize(AddressBook *addressBook);
//Save the current contacts to the file and exit
void saveAndExit(AddressBook *addressBook);

//validating the name with only alphabets,spaces and dot
int validate_name(char *str);
//validating the phone number, exactly it contains 10 digits or not
int validate_phone(char *str);
//validating email id in the proper format and ending with .com
int validate_email(char *str);
//Serach the contact in the list by using name and return the index
int search_by_name(AddressBook *addressBook);
//search the contact in the list by using phone number and return the index
int search_by_phone(AddressBook *addressBook);
//search the contact in the list by using email id and return the index
int search_by_email(AddressBook *addressBook);

#endif
