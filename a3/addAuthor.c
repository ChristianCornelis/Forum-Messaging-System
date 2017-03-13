/***************************************************
Christian Cornelis        ccorneli@mail.uoguelph.ca
CIS*2750                  ID# 0939357
March 17th, 2017          Assignment 2
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "helperFunctions.h"
#include "stream.h"

int main(int argc, char const *argv[])
{

    int a;
    char* author = malloc(sizeof(char)*300);
    for (a = 0; a < 300; a++)
        author[a] = '\0';
    int i = 2;
    int isRemovable = 0;

    /*adding all parts of the userName to a string*/
    while (i < argc)
    {
        if (strcmp(argv[i], "-r") == 0)
        {
            /*set the isRemovable flag to 1*/
            isRemovable = 1;
        }
        else
            strcat(author, argv[i]);

        if (argc > 2 && i + 1 != argc)
        {
            if (strcmp(argv[i+1], "-r") != 0 && strcmp(argv[i], "-r") != 0)
                strcat(author, " ");
        }
        i++;
    }

    /*mallocing a string to hold user input and initializing all characters to NULL*/
    char * streams = malloc(sizeof(char)*1000);
    for (a = 0; a < 1000; a++)
        streams[a] = '\0';

    strcpy(streams, argv[1]);
	strcat(streams, "\n");
    /*getting user-inputted streams*/
    if (strcmp(streams, "\n") == 0)
    {
        printf("Error: Invalid stream name.<BR>Exitting");
        free(streams);
        free(author);
        return 1;
    }
    else if (strstr(streams, " ") != NULL)
    {
        printf("Error: Stream names cannot contain spaces.<BR>Exitting.");
        free(streams);
        free(author);
        return 1;
    }
    addUser(author, streams, isRemovable);

    return 0;
}
