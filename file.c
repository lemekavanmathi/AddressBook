#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) //To reuse the contacts, we are saving inside the file
{
     FILE *fptr = fopen("contacts.csv", "w");
    if(fptr == NULL)
    {
        printf("The file is not opened.\n");
        return ;
    }
    printf("The file is opened.\n");

    fprintf(fptr,"#%d\n",addressBook->contactCount); //save the count value

    for(int i=0 ; i<addressBook->contactCount ; i++)
    {
     fprintf(fptr,"%s,%s,%s\n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    printf("Saved successfully\n");
}

void loadContactsFromFile(AddressBook *addressBook) //loading the contacts before executing the code
{
    FILE *fp = fopen("contacts.csv", "r");
    if(fp == NULL)
    {
        printf("The file is not opend.\n");
        return ;
    }
    
    fscanf(fp,"#%d\n",&addressBook->contactCount);

    for(int i=0 ; i<addressBook->contactCount ; i++)
    {
        fscanf(fp,"%[^,],%[^,],%s\n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    
}
