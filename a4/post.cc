/***************************************************
Christian Cornelis        ccorneli@mail.uoguelph.ca
CIS*2750                  ID# 0939357
February 19th, 2017       Assignment 2
***************************************************/

#include "stream.h"
#include "helperFunctions.h"

class PostEntry
{
    char* readInput(char* stream, char* username)
    {
		char* text = initString(100);
        
        if (strstr(stream, " ") != NULL)
            strcpy(stream, " ");
        else if (strcmp(stream, "\n") == 0)
            strcpy(text, "\n");
        else
            strcpy(text, "a");

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

        char textCpy[12000];
        int j;
        int k = 0;

        for (j = 0; j < strlen(text); j++)
        {
            if (text[j] == '\'')
            {
                textCpy[k] = '\'';
                textCpy[k+1] = '\'';
                k += 2;
            }
            else
            {
                textCpy[k] = text[j];
                k++;
            }
        }
        /*copying strings to struct*/
        strcpy(toReturn->username, username);
        strcpy(toReturn->streamname, streamname);
        strcpy(toReturn->date, date);
        strcpy(toReturn->text, textCpy);

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
        sprintf(timeString, "%d %02d %02d %02d:%02d:%02d", tm->tm_year + 1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

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
        char* userName = initString(255);
		char* text = initString(10000);
		char* stream = initString(255);
		strcpy(stream, argv[1]);
		strcpy(userName, argv[2]);
		strcpy(text, argv[3]);
        if (text[strlen(text)-1] != '\n')
		  strcat(text, "\n");

        class PostEntry pe;

        /*getting user data*/
        char* data = pe.readInput(stream, userName);
        /*if the stream name contained a space*/
        if (strcmp(data, " ") == 0)
        {
            printf("Error: Stream name cannot contain a space.<BR>");
            free(data);
            free(userName);
			free(stream);
			free(text);
            return;
        }
        /*if the user entered the newline as the stream*/
        else if (strcmp(data, "\n") == 0)
        {
            printf("Error: Stream name cannot be a newline.<BR>");
            free(data);
			free(stream);
			free(text);
            free(userName);
            return;
        }
        /*if the stream is formatted correctly*/
        else
        {
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
        return;
    }
};

int main(int argc, char const *argv[])
{
    int i = 0;
    class getPost myGetPost;
    int newArgc = argc;
    /*copying args to a char** because my A1 couldn't do ending braces in main????*/
    char** newArgv = initArray(argc, 10000);
    for (i = 0; i < argc; i++)
        strcpy(newArgv[i], argv[i]);
    myGetPost.getInfo(newArgc, newArgv);
    destroyArray(newArgv, argc);


    return 0;
}
