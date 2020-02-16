/*
* Leon Qu
* February 29, 2016
* Project 1 
* ICS 212
* Ravi Narayan
* Description: header file containing the functions for the database, ui, and read/write
* File: recfunctions.h
*/

#include "record.h"

int addRecord(struct record**, int, char [], char [], int);
int printRecord(struct record*, int);
int modifyRecord(struct record*, int, char []);
void printAllRecords(struct record*);
int deleteRecord(struct record**, int);

void Menu();
void getfield(char [], int);
void getInfo(struct record**, char);
void insertSort(struct record*);
int readfile(struct record**, char []);
void writefile(struct record *, char []);

