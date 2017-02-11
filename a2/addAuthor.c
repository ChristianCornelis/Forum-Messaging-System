#include <stdio.h>
#include <stdlib.h>
#include "helperFunctions.h"

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
    int a;
    char* author = malloc(sizeof(char)*300);
    for (a = 0; a < 300; a++)
        author[a] = '\0';
    int i = 1;
    int isRemovable = 0;

    /*adding all parts of the userName to a string*/
    while (i < argc)
    {
        strcat(author, argv[i]);
        strcat(author, " ");
    
        if (strcmp(argv[i], "-r") == 0)
        {
            /*set the isRemovable flag to 1*/
            isRemovable = 1;
        }

        i++;
    }

    /*mallocing a string to hold user input and initializing all characters to NULL*/
    char * streams = malloc(sizeof(char)*1000);
    for (a = 0; a < 1000; a++)
        streams[a] = '\0';

    printf("list streams: ");
    /*getting user-inputted streams*/
    fgets(streams, 1000, stdin);

    char * indivStream = malloc(sizeof(char) *300);
    for (a = 0; a < 300; a++)
        indivStream[a] = '\0';
    char** streamList = initArray(50, 500);
    int streamListCnt = 0;
    int j = 0;
    int k = 0;

    while (streams[j] != '\0')
    {
        /*if comma or null terminator is reached, then add the stream name to the list*/
        if (streams[j] == ',' || streams[j] == '\n')
        {
            strcpy(streamList[streamListCnt], indivStream);
            streamListCnt++;
            k = 0;
            j++;

            if (streams[j] == '\n')
                j++;
        }
        else if (streams[j] != ' ')
        {
            indivStream[k] = streams[j];
            k++;
        }
        j++;
    }

    int b = 0;

    for (b = 0; b < streamListCnt; b++)
        printf("Stream: %s\n", streamList[b]);

    /*freeing unneeded variables*/
    free(indivStream);
    free(streams);
    free(author);

    /*FILE* fptr = fopen("");*/

    destroyArray(streamList, 50);    
    return 0;
}