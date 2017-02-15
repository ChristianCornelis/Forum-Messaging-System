#include "stream.h"
#include "helperFunctions.h"
void updateStream (struct userPost * st)
{
    return;
}

void addUser(char * username, char * list, int isRemovable)
{
    int a = 0; 
   char * indivStream = malloc(sizeof(char) *300);
    for (a = 0; a < 300; a++)
        indivStream[a] = '\0';
    char** streamList = initArray(50, 500);
    int streamListCnt = 0;
    int j = 0;
    int k = 0;

    /*iterate through user input and break it up into the separate streams*/
    while (list[j] != '\0')
    {
        /*if comma or null terminator is reached, then add the stream name to the list*/
        if (list[j] == ',' || list[j] == '\n')
        {
            strcpy(streamList[streamListCnt], indivStream);
            streamListCnt++;
            indivStream = clearString(indivStream, 300);
            k = 0;
            j++;

            if (list[j] == '\n')
                j++;
        }
        else if (list[j] != ' ')
        {
            indivStream[k] = list[j];
            k++;
        }
        j++;
    }

    /*freeing unneeded variables*/
    free(indivStream);

    int i = 0;
    /*iterating through the list of streams and adding or removing the author accordingly*/
    for (i = 0; i < streamListCnt; i++)
    {
        char* fileName = initString(255);
        strcpy(fileName, "messages/");
        strcat(fileName, streamList[i]);
        strcat(fileName, "StreamUsers");
        printf("CHECK: %d\n", checkAuthorExists(username, fileName));
        /*if the author is not in the streams user file already, then add the author name to it*/
        if ((checkAuthorExists(username, fileName) == 0 || checkAuthorExists(username, fileName) == -1) && isRemovable == 0)
        {
            FILE* fptr = fopen(fileName, "a");
            fprintf(fptr, "%s 0\n", username);
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
            printf("%s was successfully added to the %s stream.\n", username, streamList[i]);

            free(fileName2);
            free(fileName3);
        }
        /*else if the author IS in the streams user file already and the author is to be removed*/
        else if (checkAuthorExists(username, fileName) == 1 && isRemovable == 1)
        {
            removeUser(username, list);
            printf("%s was successfully removed from the %s stream.\n", username, streamList[i]);
        }
        else if (checkAuthorExists(username, fileName) == 0 && isRemovable == 1)
            printf("%s is not currently in the %s stream and cannot be removed from it.\n", username, streamList[i]);
        else if (checkAuthorExists(username, fileName) == -1 && isRemovable == 1)
            printf("%s cannot be removed from the %s stream because it does not exist.\n", username, streamList[i]);
        else
            printf("%s is already in the %s stream.\n", username, streamList[i]);

        /*clearing the fileName string to avoid issues with strcat
        fileName = clearString(fileName, 255);*/
        free(fileName);
    }

    /*freeing all malloc'd memory*/
    destroyArray(streamList, 50);
    free(username);
    free(list);    
    return;
}

void removeUser(char * username, char * list)
{
    int a = 0;
    char * indivStream = malloc(sizeof(char) *300);
    for (a = 0; a < 300; a++)
        indivStream[a] = '\0';
    char** streamList = initArray(50, 500);
    int streamListCnt = 0;
    int j = 0;
    int k = 0;

    /*iterate through user input for stream list and break it up into the separate streams*/
    while (list[j] != '\0')
    {
        /*if comma or null terminator is reached, then add the stream name to the list*/
        if (list[j] == ',' || list[j] == '\n')
        {
            strcpy(streamList[streamListCnt], indivStream);
            streamListCnt++;
            indivStream = clearString(indivStream, 300);
            k = 0;
            j++;

            if (list[j] == '\n')
                j++;
        }
        else if (list[j] != ' ')
        {
            indivStream[k] = list[j];
            k++;
        }
        j++;
    }

    /*freeing unneeded variables*/
    free(indivStream);

    int g = 0;

    for (g = 0; g < streamListCnt; g++)
    {
        char* fileName = initString(255);
        strcpy(fileName, "messages/");
        strcat(fileName, streamList[g]);
        strcat(fileName, "StreamUsers");

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
            if (strcmp(name, username) != 0 && strcmp(name, "\n") != 0)
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
        free(fileName);
        destroyArray(authors, 100);
    }

    destroyArray(streamList, 50);
    return;
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