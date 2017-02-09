#include <stdio.h>
#include <stdlib.h>
#include "helperFunctions.h"
int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Incorrect number of arguments.\nExitting");
        return 1;
    }

    char* author = malloc(sizeof(char)*300);

    int i = 0;
    int isRemovable = 0;

    /*adding all parts of the userName to a string*/
    while (i < argc && strcmp(argv[i], "-r") != 0)
    {
        strcat(author, argv[i]);
        strcat(author, " ");
        i++;
    }

    if (strcmp(argv[i], "-r") == 0)
    {
        /*set the isRemovable flag to 1*/
        isRemovable = 1;
    }

    char * streams = malloc(sizeof(char)*1000);
    printf("\nlist streams: ");
    scanf(stdin,"%s", streams);

    int character = 0;
    char * indivStream = malloc(sizeof(char) *300);
    char** streamList = initArray(50, 500);
    int streamListCnt = 0;
    int j = 0;
    int k = 0;
    while ((character = streams[j]) != '\0')
    {
        /*if comma or null terminator is reached, then add the stream name to the list*/
        if (streams[j] == ',' || streams[j] == '\0')
        {
            strcpy(streamList[streamListCnt], indivStream);
            streamListCnt++;
            k = 0;
        }
        indivStream[k] = streams[j];
        j++;
        k++;
    }

    /*freeing unneeded variables*/
    free(indivStream);
    free(streams);

    FILE* fptr = fopen("")
    return 0;
}