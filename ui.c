/*
* Name: Leon Qu
* Project 1  
* ICS 212
* Instructor: Ravi Narayan
* Date: February 29, 2016 
* File: ui.c
* Description: This file contains the user interface
*              allowing the user a menu of choices for a personal address book.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recfunctions.h"

int debugmode;

/*
* Function name: main
* Description: user interface to allow the user to make a menu of choices
*              ,being able to add, modify, print, delete, and quit. 
* Parameters: (int) argc: number of inputs to run 
*             (char**) argv: the types of input
* Return values: 0: successful
*                -1: failed
*/
int main(int argc, char *argv[])
{
    char input;
    char filename[50];
    int reading;
    struct record *start = NULL;
    debugmode = 0;
 
    if(argc == 1)
    {
        debugmode = 0;
    }
    else if(argc == 2 && strcmp(argv[1], "debug") == 0)
    {
        debugmode = 1;
	printf("Program is now running in debug mode.\n\n");
    }
    else if(argc > 2 || strcmp(argv[1], "debug") != 0) 
    {
        printf("Error: Run program only using proj1 or proj1 debug.\n");
        return -1;
    }

    printf("This is a database of account numbers, names, addresses, and year of births.\n");
  
    printf("Enter the filename following .txt to read and write to.\n");
    scanf("%s", filename);
    reading = readfile(&start, filename);
    if(reading == -1)
    {
	printf("No file opened to read. New file %s will be created.\n", filename);
    }

    do
    {
	printf("\n");
	Menu();
        scanf(" %c",&input); 
        if(input == 'Q' || input == 'q')
        {
	    writefile(start, filename);
	    printf("The program will end.\n");
	    return 0;
	}
       
        getInfo(&start, input);

    }while(input != '\0');
 
    return 0;
}

/*
* Function name: Menu
* Description: function to show the the menu choices available
* Parameters: none
* Return values: none
*/
void Menu()
{
    if(debugmode == 1)
    {
	printf("The menu has been printed.\n");
    }

    printf("Available menu choices:\n\n");
    printf("Add a new record to database: enter A\n");
    printf("Modify a record in database: enter M\n");
    printf("Print information of a record: enter P\n");
    printf("Print all information in database: enter R\n");
    printf("Delete an existing record: enter D\n");
    printf("Quit the program: enter Q\n");
    printf("\n");
}

/*
* Function name: getInfo
* Description: function to scan the user input after menu is shown to see 
*              what option was selected and therefore making the appropriate
*              prompts to come up.
* Parameters: (char) input: the input of the user
* Return value: none  
*/
void getInfo(struct record **rec, char input)
{
    int accountno;
    char name[25]; 
    char address[80];
    int year;
    int check;

    int print, mod, del;
 
    if(debugmode == 1)
    {
	printf("You have entered: %c.\n", input);
    }

    if(input == 'A' || input == 'a')
    {
        printf("Please enter an account number:\n");
	scanf("%d", &accountno);

        printf("Please enter a name:\n");
	/*double fgets to take out the newline.*/
        fgets(name, 25, stdin);
	fgets(name, 25, stdin);
	/*removes the newline from the name*/
        name[strcspn(name, "\n")] = 0;
 
        printf("Please enter an address(tab + enter to finish):\n");
        getfield(address, 80);

        printf("Please enter the year of birth:\n");
	scanf("%d", &year);
 
        addRecord(rec, accountno, name, address, year);  
	insertSort(*rec);
	printf("The record %d has been added.\n", accountno);
    }
        
    if(input == 'M' || input == 'm')
    {
        printf("Please enter the account number to modify.\n");
	scanf("%d", &accountno);

        printf("Please enter the address to modify the record.(tab + enter to finish)\n");
	getfield(address,80);

        mod = modifyRecord(*rec, accountno, address);
	if(mod == -1)
	{
	    printf("Record not found. Please check account number.\n");
	}
    }
        
    if(input == 'P' || input == 'p')
    {
        printf("Please enter the account number to print its record.\n");
	scanf("%d", &accountno);

        print = printRecord(*rec, accountno);
	if(print == -1)
	{
	    printf("Record not found. Please check account number.\n");
	}
    }
        
    if(input == 'R' || input == 'r')
    {
        printf("All records will be printed\n");
        printAllRecords(*rec);
	if(*rec == NULL)
	{
	    printf("No records in database.\n");
	}
    }
        
    if(input == 'D' || input == 'd')
    {
        printf("Please enter the account number to delete from the database.\n");
	scanf("%d", &accountno);

        del = deleteRecord(rec, accountno);
	if(del == -1)
	{
	    printf("Record not found. Please check account number.\n");
	}
    }

}

/*
* Function name: getfield
* Description: Function to get the address for the user input
* Parameters: (char []) input: the input of the address.
*             (int) size: the number of characters in the address
* Return values: NIL 
*/ 
void getfield(char input[], int size)
{
    char * temp;
    int ch;
    int length = 0;

    if(debugmode == 1)
    {
	printf("*******Debug mode*******\n");
	printf("Input of address passing into getfield function.\n");
    }

    temp = realloc(NULL, sizeof(char)*size);    
    
    while(EOF != (ch = fgetc(stdin)) && ch != '\t')
    {
	temp[length++] = ch;
	if(length == size)
	{
	    temp = realloc(temp, sizeof(char)*(size += 1));
	}
    }

    temp[length++] = '\0';
    strcpy(input, temp); 
    free(temp);
}     

/*
* Function name: insertSort
* Description: function to sort the data by account number in ascending order
* Parameters: (struct record*) start: the list to sort
* Return: void 
*/
void insertSort(struct record * start)
{
    struct record* temp;
    struct record* pnext;
    int val;
    char hold[25];
    char space[80];
    int year;

    temp = start;
    pnext = start->next;

    while(pnext != NULL)
    {
	while(pnext != temp)
	{
	    if(pnext->accountno < temp->accountno)
	    {
		val = temp->accountno;
		temp->accountno = pnext->accountno;
		pnext->accountno = val;

	        strcpy(hold, temp->name);
	        strcpy(temp->name, pnext->name);
		strcpy(pnext->name, hold);

	        strcpy(space, temp->address);
	        strcpy(temp->address, pnext->address);
		strcpy(pnext->address, space);

		year = temp->yearofbirth;
		temp->yearofbirth = pnext->yearofbirth;
		pnext->yearofbirth = year;
	    }
	    temp = temp->next;
        }
	temp = start;
	pnext = pnext->next;
    }

}

