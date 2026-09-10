#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"

// Displays all contacts in a clean sorted list.
void listContacts(AddressBook *addressBook) 
{
    if(addressBook->contactCount == 0){
        printf("Empty, no contacts were present\n");
        return;
    }
    
    // Sort the contacts by name using bubble sort
    for(int i = 0; i < addressBook->contactCount - 1; i++) {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) {
            if (strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0) {
                // Swap contacts[j] and contacts[j + 1]
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    //loop from 0 to addressBook->contactCount-1 and print the contacts
    for(int i=0; i<addressBook->contactCount ;i++){
        printf("%s, %s, %s\n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
}

// Initializes the address book and loads contacts from the file.
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

// Saves the current contact data to the CSV storage file.
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

// Validates names with only letters, spaces, and dots.
int validate_name(char *str)
{
    //loop 0 to str[i]
    for(int i=0;str[i]!=0;i++)
    {
        if( ! ((str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z') || str[i]==' ' || str[i]=='.')) // not valid
        {
            return 0; // invalid
        }
    }

    return 1; 
}

// Validates a phone number with exactly 10 digits.
int validate_phone(char *str)
{   
    int length=0;

    for(int i=0;*(str+i)!=0;i++)
    {   
        char ch = *(str+i);
        if(ch<'0' || ch>'9') // not valid
        {
            return 0; // invalid
        }
        length++;
    }
    if(length==10){
        return 1; 
    }
    return 0;
}

// Validates that the email has a proper address format ending in .com.
int validate_email(char *str)
{
    if(*str < 'a' || *str > 'z'){
        return 0;
    }
    int i=0;
    int at=-1;
    int dot=-1;

    while(*(str+i)!=0){
        if(*(str+i)=='@'){
            at=i;
        }
        else if (*(str+i)=='.'){
            dot=i;
        }
        i++;
    }
    if(i>=4 && strcmp(str+i-4, ".com")==0)   //check .com
    {
        if(at>0 && dot>=at+2)//between @ and .com check weather something is present or not
        {
            return 1;
        }
    }
    return 0;
}

// Checks whether a phone number is already used by another contact.
static int is_duplicate_phone(AddressBook *addressBook, const char *phone, int ignored_index)
{
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (i != ignored_index && strcmp(addressBook->contacts[i].phone, phone) == 0) {
            return 1;
        }
    }
    return 0;
}

// Checks whether an email address is already used by another contact.
static int is_duplicate_email(AddressBook *addressBook, const char *email, int ignored_index)
{
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (i != ignored_index && strcmp(addressBook->contacts[i].email, email) == 0) {
            return 1;
        }
    }
    return 0;
}

// Collects a valid name, phone number, and email before adding a new contact.
void createContact(AddressBook *addressBook)
{
	// Define the logic to create a Contacts
    char str1[30], str2[20], str3[30];
    int ind;
    do
    {
        printf("Enter the name :");
        scanf(" %[^\n]",str1);

        ind = validate_name(str1);
        if(ind==0){
            printf("Your entered wrong input. Please provide a valid input.\n");
        }
    }while(ind == 0); // 0 means invalid

    do
    {
        printf("Enter the phone :");
        scanf(" %[^\n]",str2);

        ind = validate_phone(str2);
        if (ind && is_duplicate_phone(addressBook, str2, -1)) {
            ind = 0;
            printf("This phone number already exists. Please provide a different phone number.\n");
        }
        if(ind==0){
            printf("Your entered wrong input. Please provide a valid input.\n");
        }
    }while(ind == 0); // 0 means invalid

    do
    {
        printf("Enter the email id:");
        scanf(" %[^\n]",str3);

        ind = validate_email(str3);
        if (ind && is_duplicate_email(addressBook, str3, -1)) {
            ind = 0;
            printf("This email already exists. Please provide a different email.\n");
        }
        if(ind==0){
            printf("Your entered wrong input. Please provide a valid input.\n");
        }
    }while(ind == 0); // 0 means invalid

    int pos = addressBook->contactCount;
    strcpy(addressBook->contacts[pos].name, str1);
    strcpy(addressBook->contacts[pos].phone, str2);
    strcpy(addressBook->contacts[pos].email, str3);

    addressBook->contactCount++;

}

// Looks up a contact by name and prints the matching details
int search_by_name(AddressBook *addressBook){
    char new_name[20];
    int count=0;
    int index; 
    printf("Enter the name to search : ");
    scanf(" %[^\n]",new_name);

    for(int i=0;i<addressBook->contactCount ; i++){
        if(strcmp(addressBook->contacts[i].name,new_name)==0){
            count++;
        }
    }
    if(count==0){
        printf("The entered name is not found in the contact\n");
        return -1;
    }
    if(count>1){
        printf("More than 1 contact is repeated with this name. Please provide the phone number\n");
        printf("Here is the matching contacts\n");
        for(int i=0;i<addressBook->contactCount ; i++){
            if(strcmp(addressBook->contacts[i].name,new_name)==0){
                printf("Name : %s\n",addressBook->contacts[i].name);
                printf("Phone : %s\n",addressBook->contacts[i].phone);
                printf("Email : %s\n",addressBook->contacts[i].email);
            }
        }
        return search_by_phone(addressBook);
    }
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].name,new_name)==0){
            index=i;
            break;
        }
    }

    printf("\nThe contact found\n");
    printf("Name : %s\n",addressBook->contacts[index].name);
    printf("Phone : %s\n",addressBook->contacts[index].phone);
    printf("Email : %s\n",addressBook->contacts[index].email);

    return index;
}

// Searches the list by phone number and returns the matching index.
int search_by_phone(AddressBook *addressBook){
    char phone_no[20];
    printf("Enter the phone number to search : ");
    scanf(" %s",phone_no);

    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].phone,phone_no)==0){
            printf("\nContact found\n");
            printf("Name : %s\n",addressBook->contacts[i].name);
            printf("Phone : %s\n",addressBook->contacts[i].phone);
            printf("Email : %s\n",addressBook->contacts[i].email);
            return i;
        }
    }

    printf("Contact with this phone number is not found\n");
    return -1;
}

// Finds a contact using its email address and prints the result.
int search_by_email(AddressBook *addressBook){
    char email_id[20];
    printf("Enter the email id to search : ");
    scanf(" %s",email_id);

    int n =addressBook->contactCount;
    for(int i=0;i<n;i++){
        if(strcmp(addressBook->contacts[i].email,email_id)==0){
            printf("\nContact found\n");
            printf("Name : %s\n",addressBook->contacts[i].name);
            printf("Phone : %s\n",addressBook->contacts[i].phone);
            printf("Email : %s\n",addressBook->contacts[i].email);
            return i;
        }
    }
    printf("Contact with this email id is not found\n");
    return -1;
}

// Lets the user choose the search type and shows the contact details.
void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    printf("Select any one option to search the contact\n");
    printf("1.Name\n2.Phone\n3.Email\n4.Exit\n");
    int choice;
     
    printf("Enter the choice : ");
    scanf("%d",&choice);
    // print promt

    switch(choice)
    {
        case 1:
            search_by_name(addressBook);
            break;
        case 2:
            search_by_phone(addressBook);
            break;
        case 3:
            search_by_email(addressBook);
            break;
        case 4:
            return ;
        default:
            printf("Invalid choice selected\n");
            break;
    }

}

// Updates the selected contact field after validating the new value.
void editContact(AddressBook *addressBook)
{
	// Define the logic for Editcontact
    printf("Select any one option to edit the contact\n");
    printf("1.Name\n2.Phone\n3.Email\n4.Exit\n");
    int ind;
    int res;
    int choice;
    printf("Enter the choice : ");
    scanf("%d", &choice);

    switch(choice){
        case 1:
        {
            ind = search_by_name(addressBook);
            if(ind==-1){
                return ;
            }

            char edit_name[50];
            do{
                printf("Enter the name to edit : ");
                scanf(" %[^\n]",edit_name);

                res=validate_name(edit_name);
                if(res==0){
                    printf("Invalid name, give the proper name\n");
                }
            }
            while(res==0);

            strcpy(addressBook->contacts[ind].name,edit_name);
            printf("The name successfully edited\n");
            break;
        }

        case 2:
        {
            ind=search_by_phone(addressBook);
            if(ind==-1){
                return ;
            }

            char edit_phone[20];
            do{
                printf("Enter the phone number to edit : ");
                scanf(" %[^\n]",edit_phone);

                res=validate_phone(edit_phone);
                if(res==0){
                    printf("Invalid phone number, give the proper phone number\n");
                }
                else if (is_duplicate_phone(addressBook, edit_phone, ind)) {
                    res = 0;
                    printf("This phone number already exists, give a different phone number\n");
                }
            }while(res==0);//invalid

            strcpy(addressBook->contacts[ind].phone,edit_phone);
            printf("The phone number successfully edited\n");
            break;
        }

        case 3:
        {
            ind=search_by_email(addressBook);
            if(ind==-1){
                return ;
            }

            char edit_email[50];
            do{
                printf("Enter the emailid to edit : ");
                scanf(" %[^\n]",edit_email);

                res=validate_email(edit_email);
                if(res==0){
                    printf("Invalid email id, give the proper email id\n");
                }
                else if (is_duplicate_email(addressBook, edit_email, ind)) {
                    res = 0;
                    printf("This email already exists, give a different email id\n");
                }
            }while(res==0);//invalid

            strcpy(addressBook->contacts[ind].email,edit_email);
            printf("The email successfully edited\n");
            break;
        }

        case 4:
            return;
        default:
            printf("Invalid choice selected\n");
            break;
    }
}

// Deletes one contact from the list and shifts the remaining entries up.
void deleteContact(AddressBook *addressBook)
{
	// Define the logic for deletecontact 
    printf("Select any one option to delete the contact\n");
    printf("1.Name\n2.Phone\n3.Email\n4.Exit\n");

    int ind=-1;
    int choice;
    printf("Enter the choice : ");
    scanf("%d",&choice);
   
    switch(choice){
        case 1:
               ind=search_by_name(addressBook);
               break;
        case 2:
               ind=search_by_phone(addressBook);
               break;
        case 3:
               ind=search_by_email(addressBook);
               break;
        case 4:
               return; 
        default:
               printf("Invalid choice selected\n");
               return;
    }
    if(ind==-1){
        printf("It is not found in the contact\n");
        return;
    }
    for(int i=ind;i<addressBook->contactCount-1;i++){
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    printf("Contacts deleted successfully\n");
}