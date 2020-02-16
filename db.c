/*
* Name: Leon Qu
* Project 1 
* ICS 212
* Instructor: Ravi Narayan
* Date: February 29, 2016 
* File: db.c
* Description: The file to contain the functions for the use of record keeping. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recfunctions.h"

extern int debugmode;
 
/*
* Function name: addRecord
* Description: function to add a record of account number, name, address, year  
*              number into the heap as a linked list.
* Parameters: struct record ** start: the pointer to the start of the list
*             (int) accountno: account number of the user
*             (char []) name: name of the user input
*             (char []) address: address of user
*             (int) year: year of user
* Return values: 0 if successful
*/
int addRecord(struct record** start, int accountno, char name[], char address[], int year)
{
    struct record * pstart;
    /*another pointer to keep track of where to add next.*/
    struct record * ptr;

    if(debugmode == 1)
    {
        printf("*******Debug mode*******\n");
        printf("Parameters of addRecord passed\n");
        printf("account number: %d\nname: %s\naddress: %s\nyear: %d\n", accountno, name, address, year);
    }

    pstart = (struct record*)malloc(sizeof(struct record));   
    pstart->accountno = accountno;
    strcpy(pstart->name, name);
    strcpy(pstart->address, address);
    pstart->yearofbirth = year;
    pstart->next = NULL;

    if(*start == NULL)
    {
	*start = pstart;
    }
    else
    {
	ptr = *start;
	while(ptr->next != NULL)
	{
	    ptr = ptr->next;
	}
	ptr->next = pstart;	
    }
    
    return 0;
}

/*
* Function name: printRecord
* Description: prints a record in the list, if there are copies then prints all
* Parameters: the list to print, record to print
* Return values: 0 if successful
*               -1 if not 
*/
int printRecord(struct record * start, int accountno)
{
     struct record * temp;
     int end = 0;

     if(debugmode == 1)
     {
         printf("*******Debug mode*******\n");
         printf("Parameters of printRecord passed\n");
         printf("record: %d\n", accountno);
     } 
 
     temp = start;
     if(temp == NULL)
     {
	end = -1;
     }

     while(temp != NULL)
     {
         if(temp->accountno == accountno)
         {
	     printf("Name: %s\n", temp->name);
	     printf("Address: %s\n", temp->address);
	     printf("Birthyear: %d\n", temp->yearofbirth);
	     printf("\n");
	     temp = temp->next;
         }
         else
         {
	     temp = temp->next; 
         }
     }

     return end; 
}

/*
* Function name: modifyRecord
* Description: function to be able to be able to modify a record in the list
* Parameters: start list, account number and address to modify
* Return values: 0 if successful
*                -1 if unsuccesful
*/
int modifyRecord(struct record* start, int accountno, char address[])
{
     struct record * ptr;
     int end = 0;

     if(debugmode == 1)
     { 
         printf("*******Debug mode*******\n");
         printf("Parameters of modifyRecord passed\n");
         printf("account number: %d\naddress: %s\n", accountno, address);
     } 
    
     ptr = start;
     if(ptr == NULL)
     {
	end = -1;
     }

     while(ptr != NULL)
     {
	if(ptr->accountno == accountno)
	{
	    strcpy(ptr->address, address);
	    ptr = ptr->next; 
	}
	else
	{
	    ptr = ptr->next;
	}
     }

     return end;
}

/*
* Function name: printAllRecords
* Description: prints all current records in the database
* Parameters: the list of records
* Return values: none
*/
void printAllRecords(struct record* start)
{
    struct record * temp;
    int recordNumber = 1;

    if(debugmode == 1)
    { 
        printf("*******Debug mode*******\n");
        printf("Printing all records available in the database.\n");
    }

    temp = start;

    while(temp != NULL)
    {
	printf("Record #%d\n", recordNumber);
	printf("Account Number: %d\n", temp->accountno);
	printf("Name: %s\n", temp->name);
	printf("Address: %s\n", temp->address);
	printf("Birthyear: %d\n", temp->yearofbirth);
	printf("\n");
	temp = temp->next;
	recordNumber++;
    } 
}

/*
* Function name: deleteRecord
* Description: function deletes a selected account # in the list, or all copy
* Parameters: struct record ** start
*             (int) accountno: the account to delete 
* Return values: 0 if successful
*               -1 if not
*/
int deleteRecord(struct record** start, int accountno)
{
    struct record * pstart;
    /*temporary struct pointer key to hold the address of the deleted record.*/
    struct record * key;
    int end = 0;

    if(debugmode == 1)
    { 
        printf("*******Debug mode*******\n");
        printf("Parameters of deleteRecord passed\n");
        printf("account number: %d\n", accountno); 
    }

    pstart = *start;
    key = NULL; 
    if(pstart == NULL)
    {
	end = -1;
    }

    while(pstart != NULL)
    {
	if(pstart->accountno == accountno)
        {
	    if(key == NULL|| key->accountno == accountno)
	    {
		*start = pstart->next;
		key = *start;
		free(pstart);
		pstart = key;
	    }
	    else
 	    {
		key->next = pstart->next;
		free(pstart);
		pstart = key;
	    }
	}
        else
        {
       	    key = pstart;
	    pstart = pstart->next;
	}    
	
    }
    return end;
}
