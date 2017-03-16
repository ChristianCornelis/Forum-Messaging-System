/***************************************************
Christian Cornelis        ccorneli@mail.uoguelph.ca
CIS*2750                  ID# 0939357
February 19th, 2017       Assignment 2
***************************************************/

#include "stream.h"
#include "helperFunctions.h"

/*function to add a new posting to a specific stream*/
void updateStream (struct userPost * st)
{
    DIR* dirPtr;
    /*if messages folder does not exist, then create it*/
    if (!(dirPtr=opendir("messages")))
    {
        mkdir("messages/", 0777);
    }
    free(dirPtr);

    /*creating fileNames for opening*/
    char* fileName = initString(255);
    strcpy(fileName, "messages/");
    strcat(fileName, st->streamname);
    strcat(fileName, "StreamUsers");

    char* fileName2 = initString(255);
    strcpy(fileName2, "messages/");
    strcat(fileName2, st->streamname);
    strcat(fileName2, "StreamData");

    char* fileName3 = initString(255);
    strcpy(fileName3, "messages/");
    strcat(fileName3, st->streamname);
    strcat(fileName3, "Stream");

    /*if the stream does not exist, make the files but do not add anything to them*/
    if (checkAuthorExists(st->username, fileName) == -1)
    {
        printf("Error: Invalid stream name: Stream does not exist.<BR>Stream files created.<BR>To post to this stream, please use the addauthor program to gain permission to post to this stream\n");

        /*creating files and closing immediately*/
        FILE* streamsUsers = fopen(fileName, "w");
        FILE* streamData = fopen(fileName2, "w");
        FILE* stream = fopen(fileName3, "w");
        fclose(streamsUsers);
        fclose(streamData);
        fclose(stream);

        updateMasterList(st->streamname);
    }
    /*else if user does not have permission to post in the stream*/
    else if (checkAuthorExists(st->username, fileName) == 0)
        printf("Error: This user does not have permission to post in this stream.<BR>Use the addauthor program to gain permission to post to this stream.<BR>");

    /*else if the user does have permission to post in the stream*/
    else if (checkAuthorExists(st->username, fileName) == 1)
    {
        FILE* dataStream = fopen(fileName2, "r");
        char line[255];
        int totalChars = 0;
        while (fgets(line, 255, dataStream) != NULL)
        {
            char* toAdd = strtok(line, "\n");
            totalChars = atoi(toAdd);
            printf("ADDING %d\n", atoi(toAdd));
        }
        fclose(dataStream);
        printf("SUM SO FAR: %d\n", totalChars);
        /*adding user post to the stream file*/
        FILE* stream = fopen(fileName3, "a");
        fprintf(stream, "Sender: %s\n", st->username);
        fprintf(stream, "Data: %s\n", st->date);
        fprintf(stream, "%s", st->text);
        fclose(stream);

        /*adding the size of the text post to the streamdata file*/
        FILE* streamData = fopen(fileName2, "a");
        fprintf(streamData, "%d\n", (totalChars + ((int) (strlen(st->text) + strlen(st->date) + strlen(st->username)) + 16)));
        printf("%d\n", (totalChars + ((int) (strlen(st->text) + strlen(st->date) + strlen(st->username)) + 16)));
        fclose(streamData);

        printf("Post successfully added to the stream.<BR>");

    }
    free(fileName);
    free(fileName2);
    free(fileName3);

    return;
}

/*function to add a user to a list of streams*/
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

    DIR* dirPtr;
    /*if messages folder does not exist, then create it*/
    if (!(dirPtr=opendir("messages")))
    {
        mkdir("messages/", 0777);
    }
    free(dirPtr);
    int i = 0;
    /*iterating through the list of streams and adding or removing the author accordingly*/
    for (i = 0; i < streamListCnt; i++)
    {
        char* fileName = initString(255);
        strcpy(fileName, "messages/");
        strcat(fileName, streamList[i]);
        strcat(fileName, "StreamUsers");
        /*if the author is not in the streams user file already, then add the author name to it*/
        if ((checkAuthorExists(username, fileName) == 0 || checkAuthorExists(username, fileName) == -1) && isRemovable == 0)
        {
            if (checkAuthorExists(username, fileName) == -1)
            {
                updateMasterList(streamList[i]);
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
                printf("%s was successfully added to the %s stream.<BR>", username, streamList[i]);

                free(fileName2);
                free(fileName3);
            }
			else
				printf("%s was successfully added to the %s stream.<BR>", username, streamList[i]);
            FILE* fptr = fopen(fileName, "a");
            fprintf(fptr, "%s 0\n", username);
            fclose(fptr);


        }
        /*else if the author IS in the streams user file already and the author is to be removed*/
        else if (checkAuthorExists(username, fileName) == 1 && isRemovable == 1)
        {
            removeUser(username, streamList[i]);
            printf("%s was successfully removed from the %s stream.<BR>", username, streamList[i]);
        }
        else if (checkAuthorExists(username, fileName) == 0 && isRemovable == 1)
            printf("%s is not currently in the %s stream and cannot be removed from it.<BR>", username, streamList[i]);
        else if (checkAuthorExists(username, fileName) == -1 && isRemovable == 1)
            printf("%s cannot be removed from the %s stream because it does not exist.<BR>", username, streamList[i]);
        else
            printf("%s is already in the %s stream.<BR>", username, streamList[i]);

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

/*function to remove a user from a stream*/
void removeUser(char * username, char * stream)
{
    DIR* dirPtr;
    /*if messages folder does not exist, then create it*/
    if (!(dirPtr=opendir("messages")))
    {
        mkdir("messages/", 0777);
    }
    free(dirPtr);

    char* fileName = initString(255);
    strcpy(fileName, "messages/");
    strcat(fileName, stream);
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

        int index = strlen(temp) -1;
        while (temp[index] != ' ')
            index--;
        temp[index] = '\0';
        char name[255] = "";
        strcpy(name, temp);

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

    int index;
    /*go through the file and check if any of the user's names are the same as the author in question*/
    while (fgets(line, 255, fptr) != NULL)
    {
        index = strlen(line) -1;
        while (line[index] != ' ')
            index--;
        line[index] = '\0';
        char name[255];
        strcpy(name, line);

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

/*function to free all memory for a user post struct*/
void destroyStruct(userPost* toDestroy)
{
    if (!toDestroy)
        return;

    free(toDestroy->username);
    free(toDestroy->streamname);
    free(toDestroy->date);
    free(toDestroy->text);
    free(toDestroy);

    return;
}

/*function to update the master stream list if a new stream is created*/
void updateMasterList(char* stream)
{
    DIR* dirPtr;
    /*if messages folder does not exist, then create it*/
    if (!(dirPtr=opendir("messages")))
    {
        mkdir("messages/", 0777);
    }
    free(dirPtr);

    FILE* fptr;

    if (!(fptr = fopen("messages/streamList", "r")))
    {
        fptr = fopen("messages/streamList", "w");
    }
    else
        fptr = fopen("messages/streamList", "a");

    fprintf(fptr, "%s\n", stream);

    fclose(fptr);
    return;
}
