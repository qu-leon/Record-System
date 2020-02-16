/*
* Leon Qu
* Project 1 
* ICS 212
* Instructor: Ravi Narayan
* Date: February 29, 2016 
* File: io.c
* Description: file containing the functions to read and write an array of 
*              records to and from a file.
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "recfunctions.h"

extern int debugmode;

/*
* Function name: readfile
* Description: function the read an array of records from a file
* Parameters: (struct account) accarray[]: struct datatype to contain the 
*              user data
*              (int *) numcust: pointer to the number of custombers in file
*              (char *) filename: the filename to read
* Return values: 0 if successful
*               -1 if not 
*/
int readfile(struct record** start, char filename[])
{
    FILE *file;
    char buffer[200];
    int account;
    char name[25] = "";
    char addr[80] = "";
    int yob;

    int counter = 0;
    int end = 0;

    if(debugmode == 1)
    {
	printf("*******Debug mode*******\n");
	printf("Parameters of readfile passed.\n");
        printf("%s file has been read.\n", filename);
    }

    file = fopen(filename, "r");
 
    if(file != NULL)
    {
	while(fgets(buffer, sizeof(buffer), file) != NULL)
        {
 	    if(counter == 0)
	    {
	        account = atoi(buffer);
		counter++;
	    }
	    else if(counter == 1)
	    {
	        if(buffer != '\0')
	        {
	            strcpy(name, buffer);
		    name[strcspn(name, "\n")] = '\0';
		    counter++;
	        }
		else
		{
		    end = -1;
		}
	    }
	    else if(counter == 2)
	    { 
		if(buffer[strlen(buffer) - 2] == '\t')
		{
		    buffer[strlen(buffer) - 2] == '\0';
		    strcat(addr, buffer);
		    counter++;
		}
		else
		{
		    strcat(addr, buffer);
		    counter = 2;
                }
	    }
	    else if(counter == 3) 
 	    {
		yob = atoi(buffer);
                addRecord(start, account, name, addr, yob);
	        strcpy(addr,"");
	        counter = 0;
	    } 

	}
 	fclose(file);
    }
    else
    {
	end = -1;
    }

    return end;
}

/*
* Function name: writefile
* Description: function to write data record onto a file
* Parameters: (struct account) accarray[]: struct datatype containing the
*             user data
*             (int) the number of customers
*             (char *) filename: the filename to write to
* Return values: void 
*/
void writefile(struct record * start, char filename[])
{
    FILE *file;
    struct record * ptr;

    if(debugmode == 1)
    {
	printf("*******Debug mode*******\n");
	printf("Parameters of writefile passed.\n");
        printf("%s file has been written into.\n", filename);
    }

    file = fopen(filename, "w");
    ptr = start;

    while(ptr != NULL) 
    {
	fprintf(file, "%d\n", ptr->accountno);
	fprintf(file, "%s\n", ptr->name);
	fprintf(file, "%s\t\n", ptr->address);
	fprintf(file, "%d\n", ptr->yearofbirth);
	ptr = ptr->next;
    
    }      
    
    fclose(file);
}
 
