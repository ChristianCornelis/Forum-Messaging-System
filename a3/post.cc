/***************************************************
Christian Cornelis        ccorneli@mail.uoguelph.ca
CIS*2750                  ID# 0939357
February 19th, 2017       Assignment 2
***************************************************/

#include "stream.h"
#include "helperFunctions.h"

class PostEntry
{
    char* readInput(char* username)
    {
        /*getting user input for stream*/
        printf("\nstream: ");
        char * stream = initString(1000);
        fgets(stream, 1000, stdin);
        if (strcmp(stream, "\n") == 0)
            return stream;
        if (strstr(stream, " ") != NULL)
        {
            strcpy(stream, " ");
            return stream;
        }
        char* line = initString(500);
        char* text = initString(10000);
        strcpy(text, stream); 
        stream[strlen(stream)-1] = '\0';
        char* filename = initString(1000);

        /*if messages folder does not exist, then create it*/
        DIR* dirPtr;
        if (!(dirPtr=opendir("messages")))
        {
            mkdir("messages/", 0777);
        }
        free(dirPtr);
        strcpy(filename,"messages/");
        strcat(stream, "StreamUsers");
        strcat(filename, stream);

        /*if the user is not permitted to add to the stream, then print an error message and don't accept user input*/
        if (checkAuthorExists(username, filename) == 0)
        {
            printf("Error: This user does not have permission to post in this stream.\nUse the addauthor program to gain permission to post to this stream.\n");
            free(stream);
            free(filename);
            free(line);
            text = clearString(text, 10000);
            return text;
        }
        /*else if the user is not permitted to add to the stream, then print an error message and don't accept user input*/
        else if (checkAuthorExists(username, filename) == -1)
        {
            printf("Error: Invalid stream name: Stream does not exist.\nStream files created.\nTo post to this stream, please use the addauthor program to gain permission to post to this stream\nExitting.");
            free(stream);
            free(filename);
            free(line);
            text = clearString(text, 10000);
            return text;
        }
        /*prompting user for text and reading it in until CTRL + d is entered*/
        printf("enter text: ");
        while(fgets(line, 500, stdin) != NULL)
        {
            printf("-");
            strcat(text, line);
            clearString(line, 500);
        }
        free(stream);
        free(filename);
        free(line);
        return text;
    }
    userPost* formatEntry(char* username, char* streamname, char* date, char* text)
    {
        userPost * toReturn = malloc(sizeof(userPost));

        /*mallocing for strings inside struct*/
        toReturn->username      = initString(300);
        toReturn->streamname    = initString(300);
        toReturn->date          = initString(300);
        toReturn->text          = initString(10000);

        /*copying strings to struct*/
        strcpy(toReturn->username, username);
        strcpy(toReturn->streamname, streamname);
        strcpy(toReturn->date, date);
        strcpy(toReturn->text, text);

        if (toReturn)
            return toReturn;

        return NULL;
    }

    char* getDateTime()
    {
        /*getting time that post was completed at to be printed to the file*/
        time_t t = time(NULL);
        struct tm* tm = localtime(&t);
        char* timeString = malloc(sizeof(char)*100);
        sprintf(timeString, "%d %d %d %d:%d:%d", tm->tm_year + 1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

        return timeString;
    }

    void submitPost(userPost* up)
    {
        updateStream(up);
        return;
    }   
};

class getPost
{
    void getInfo(int argc, char** argv)
    {
        int i;
        if (argc < 2)
        {
            printf("Error: Not enough arguments.\nExitting.\n");
            exit(1);
        }

        char* userName = initString(255);
        for (i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-r") == 0)
            {
                printf("Error: Username cannot contain '-r'.\nExitting.\n");
                exit(1);
            }
            else
            {
                strcat(userName, argv[i]);
                if (argc > 2 && i + 1 != argc)
                    strcat(userName, " ");
            }
        }

        class PostEntry pe;

        /*getting user data*/
        char* data = pe.readInput(userName);
        /*if the stream name contained a space*/
        if (strcmp(data, " ") == 0)
        {
            printf("Error: Stream name cannot contain a space.\nExitting\n");
            free(data);
            free(userName);
            return;
        }
        /*if the user entered the newline as the stream*/
        else if (strcmp(data, "\n") == 0)
        {
            printf("Error: Stream name cannot be a newline.\nExitting\n");
            free(data);
            free(userName);
            return;
        }
        /*if the user has permission to post in the stream, then update the files necessary*/
        if (strcmp(data, "") != 0)
        {
            int k = 0;
            int j = 0;
            char* stream = initString(1000);
            char* text = initString(10000);
            while (data[k] != '\n')
            {
                stream[k] = data[k]; 
                k++;
            }
            k++;

            while(data[k] != '\0')
            {
                text[j] = data[k];
                j++;
                k++;
            }
            char* time = pe.getDateTime();

            /*creating struct, submitting post, and freeing memory*/
            userPost* post = pe.formatEntry(userName, stream, time, text);
            pe.submitPost(post);
            free(stream);
            free(text);
            free(data); 
            free(time);
            free(userName);

            destroyStruct(post);
        }
        /*else, free variables and exit*/
        else
        {
            free(data);
            free(userName);
        }
        return;
    }
};
int main(int argc, char const *argv[])
{
    int i = 0;
    class getPost myGetPost;
    int newArgc = argc;
    /*copying args to a char** because my A1 couldn't do ending braces in main????*/
    char** newArgv = initArray(argc, 255);
    for (i = 0; i < argc; i++)
        strcpy(newArgv[i], argv[i]);
    myGetPost.getInfo(newArgc, newArgv);
    destroyArray(newArgv, argc);


    return 0;
}