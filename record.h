/*
* Leon Qu
* ICS 212
* Instructor: Ravi Narayan
* Date: February 29, 2016 
* File: record.h 
* Description: file containing the struct for the record database
*/

struct record
{
    int 	    accountno;
    char            name[25];
    char            address[80];
    int             yearofbirth;
    struct record * next;
};

