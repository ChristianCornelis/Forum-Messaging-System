#include <stdio.h>
#include <stdlib.h>
#include "helperFunctions.h"

/*function to check if an author is already present in a stream's file*/
int checkAuthorExists(char* author, char* fileName);

/*function to collect all authors inside a file, except for the targetted author to be removed*/
void removeAuthor(char* toRemove, char* fileName);

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

    char * indivStream = malloc(sizeof(char) *300);
    for (a = 0; a < 300; a++)
        indivStream[a] = '\0';
    char** streamList = initArray(50, 500);
    int streamListCnt = 0;
    int j = 0;
    int k = 0;

    /*iterate through user input and break it up into the separate streams*/
    while (streams[j] != '\0')
    {
        /*if comma or null terminator is reached, then add the stream name to the list*/
        if (streams[j] == ',' || streams[j] == '\n')
        {
            strcpy(streamList[streamListCnt], indivStream);
            streamListCnt++;
            indivStream = clearString(indivStream, 300);
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

    /*freeing unneeded variables*/
    free(indivStream);
    free(streams);

    char* fileName = initString(255);
    strcpy(fileName, "messages/");
    /*iterating through the list of streams and adding or removing the author accordingly*/
    for (i = 0; i < streamListCnt; i++)
    {
        strcat(fileName, streamList[i]);
        strcat(fileName, "StreamUsers");

        /*if the author is not in the streams user file already, then add the author name to it*/
        if ((checkAuthorExists(author, fileName) == 0 || checkAuthorExists(author, fileName) == -1) && isRemovable == 0)
        {
            FILE* fptr = fopen(fileName, "a");
            fprintf(fptr, "%s 0\n", author);
            fclose(fptr);

            char* fileName2 = initString(255);
            char* fileName3 = initString(255);

            strcpy(fileName2, "messages/");
            strcat(fileName2, streamList[i]);
            strcat(fileName2, "StreamData");

            strcpy(fileName3, "messages/");
            strcat(fileName3, streamList[i]);
            strcat(fileName3, "Stream");
            FILE* streamData = fopen(fileName2, "w");
            FILE* stream = fopen(fileName3, "w");

            fclose(streamData);
            fclose(stream);
            printf("%s was successfully added to the %s stream.\n", author, streamList[i]);
        }
        /*else if the author IS in the streams user file already and the author is to be removed*/
        else if (checkAuthorExists(author, fileName) == 1 && isRemovable == 1)
        {
            char** fileAuthors = initArray(100, 300);
            removeAuthor(author, fileName);
            printf("%s was successfully removed from the %s stream.\n", author, streamList[i]);
        }
        else if (checkAuthorExists(author, fileName) == -1 && isRemovable == 1)
            printf("%s is not currently in the %s stream and cannot be removed from it.\n", author, streamList[i]);
        else
            printf("%s is already in the %s stream.\n", author, streamList[i]);

        /*clearing the fileName string to avoid issues with strcat*/
        fileName = clearString(fileName, 255);
    }

    /*freeing all malloc'd memory*/
    destroyArray(streamList, 50);
    free(author);
    free(fileName);    
    return 0;
}

/*function to check if an author is already present in a stream's file*/
int checkAuthorExists(char* author, char* fileName)
{
    char line[255];
    FILE* fptr;

    /*if the file doesn't exist, then the author's name cannot be present already*/
    if ((fptr = fopen(fileName, "r")) == NULL)
    {
        return -1;
    }

    /*go through the file and check if any of the user's names are the same as the author in question*/
    while (fgets(line, 255, fptr) != NULL)
    {
        char* name = strtok(line, " ");
        /*if the authors name IS in the file already, return 1*/
        if (strcmp(author, name) == 0)
        {
            fclose(fptr);
            return 1;
        }
    }

    fclose(fptr);
    return 0;
}

/*function to collect all authors inside a file, except for the targetted author to be removed*/
void removeAuthor(char* author, char* fileName)
{
    FILE* fptr = fopen(fileName, "r");
    char** authors = initArray(100, 300);
    int authorsCnt = 0;
    char line[255] = "";
    char temp[255] = "";

    /*parse the file and compare all author names in it to the removeable author's name*/
    while (fgets(line, 255, fptr) != NULL)
    {
        strcpy(temp, line);
        char* name = strtok(temp, " ");

        /*if the name on the line is not the authors, add it to the array*/
        if (strcmp(name, author) != 0 && strcmp(name, "\n") != 0)
        {
            strcpy(authors[authorsCnt], line);
            authorsCnt++;
        }
    }

    fclose(fptr);

    /*reopening file and writing users back to the file before returning*/
    fptr = fopen(fileName, "w");
    int i;
    for (i = 0; i < authorsCnt; i++)
    {
        if (strcmp(authors[i], "") != 0)
            fprintf(fptr, "%s", authors[i]);
    }

    fclose(fptr);
    destroyArray(authors, 100);

    return;
}