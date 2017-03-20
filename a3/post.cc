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
        char* filename = initString(1000);
		char* text = initString(100);
        /*if messages folder does not exist, then create it*/
        DIR* dirPtr;
        if (!(dirPtr=opendir("messages")))
        {
            mkdir("messages/", 0777);
        }

        free(dirPtr);
        strcpy(filename,"messages/");
		strcat(filename, stream);
        strcat(filename, "StreamUsers");

        /*if the user is not permitted to add to the stream, then print an error message and don't accept user input*/
        if (checkAuthorExists(username, filename) == 0)
        {
            printf("Error: This user does not have permission to post in this stream.<BR>Use the addauthor program to gain permission to post to this stream.<BR>");
            free(filename);
            text = clearString(text, 100);
            return text;
        }
        /*else if the user is not permitted to add to the stream, then print an error message and don't accept user input*/
        else if (checkAuthorExists(username, filename) == -1)
        {
            printf("Error: Invalid stream name: Stream does not exist<BR>To post to this stream, please use the addauthor program to first create it. <BR>");
            free(filename);
            text = clearString(text, 100);
            return text;
        }
        /*if the user is permitted to post to the stream then return an arbitrary value to represent that*/
        strcpy(text, "a");
        free(filename);

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
        /*if the user has permission to post in the stream, then update the files necessary*/
        if (strcmp(data, "") != 0)
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
        /*else, free variables and exit*/
        else
        {
            free(data);
            free(userName);
			free(stream);
			free(text);
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
