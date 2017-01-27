#ifndef __CCORNELI_HELPER_FUNCTIONS_H__
#define __CCORNELI_HELPER_FUNCTIONS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*function to initialize a dynamically-allocated array based on size parameters */
char ** initArray(int rows, int columns);

/*function to destroy a dynamically-allocated array*/
int destroyArray(char ** toDestroy, int rows);

/*function to resize the array to twice the number of rows of the old size*/
char ** resizeArray (char ** oldArray, int rows, int columns);

/*function to check if the array needs to be resized*/
int checkSize (int rowCnt, int rows);

/*function to check if a word is a type keyword*/
int isKeyword (char * word);

/*function to print to a .c file*/
int printToFile (char* fileName, char** spacing, char** strings, int rowCnt);

/*function to rename functions inside classes*/
char* renameFuncs(char** strings, char** spacing, int count, FILE* toWrite, int funcStart, char className[]);
#endif