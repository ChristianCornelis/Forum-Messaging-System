#include <stdio.h>
#include <stdlib.h>
#include "helperFunctions.h"
#include "stream.h"

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Incorrect number of arguments.\nExitting\n");
        return 1;
    }
    else if (argc == 2 && strcmp(argv[1], "-r") == 0)
    {
        printf("Error: An author ID must be inputted to be removed.\nExitting\n");
        return 1;
    }
    else if (argc > 3)
    {
        printf("Error: Too many arguments present.\nExitting\n");
        return 1;
    }

    int a;
    char* author = malloc(sizeof(char)*300);
    for (a = 0; a < 300; a++)
        author[a] = '\0';
    int i = 1;
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
        i++;
    }

    /*mallocing a string to hold user input and initializing all characters to NULL*/
    char * streams = malloc(sizeof(char)*1000);
    for (a = 0; a < 1000; a++)
        streams[a] = '\0';

    printf("list streams: ");
    /*getting user-inputted streams*/
    fgets(streams, 1000, stdin);
    addUser(author, streams, isRemovable);

    return 0;
}

