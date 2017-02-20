/***************************************************
Christian Cornelis        ccorneli@mail.uoguelph.ca
CIS*2750                  ID# 0939357
February 19th, 2017       Assignment 2
***************************************************/

#ifndef __CCORNELI_HELPER_FUNCTIONS_H__
#define __CCORNELI_HELPER_FUNCTIONS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*function to initialize a dynamically-allocated array based on size parameters */
char ** initArray(int rows, int columns);

/*function to initialize a string*/
char* initString (int size);

/*function to reset all characters in a string to '\0'*/
char * clearString (char* toClear, int size);

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
char* renameFuncs(char** strings, char** spacing, int count, FILE* toWrite, int funcStart, char* className);

/*function to check if a string is a class variable*/
int isClassVar (char** classVars, char* string, int classVarsCnt);

/*function to check if a string is a local class variable*/
int isLocalClassVar (char** localClassVars, int localClassVarsCnt, char* string, char* className);

/*function to copy all local class variables for a specific class to a new list*/
char** createTempClassVarsList(char** localClassVars, int localClassVarsCnt, char* className);
#endif