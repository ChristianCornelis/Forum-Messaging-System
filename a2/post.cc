#include "stream.h"
#include "helperFunctions.h"

class PostEntry
{
    char* readInput()
    {
        printf("\nstream: ");
        char * stream = initString(1000);

        fgets(stream, 1000, stdin);
        
        char line[500];
        char* text = initString(10000);
        strcpy(text, stream);
        strcat(text, " ");

        /*prompting user for text and reading it in until CTRL + d is entered*/
        printf("enter text: ");
        while(fgets(line, 500, stdin) != NULL)
        {
            printf("-");
            strcat(text, line);
        }

        free(stream);
        return text;
    }
    userPost* formatEntry(char* username, char* streamname, char* date, char* text)
    {
        userPost * toReturn = malloc(sizeof(userPost));

        /*mallocing for strings inside struct*/
        /*toReturn->username      = malloc(sizeof(char) * (sizeof(username) +1));
        toReturn->streamname    = malloc(sizeof(char) * (sizeof(streamname) +1));
        toReturn->date          = malloc(sizeof(char) * (sizeof(date) + 1));
        toReturn->text          = malloc(sizeof(char) * (sizeof(text) + 1));*/

        /*mallocing for strings inside struct*/
        toReturn->username      = initString(300);
        toReturn->streamname    = initString(300);
        toReturn->date          = initString(300);
        toReturn->text          = initString(10000);

        printf("username: %d\n", sizeof(username));
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
        strftime(timeString, sizeof(timeString), "%c", tm);

        return timeString;
    }

    void submitPost()
    {
        return;
    }   
};

class a
{
    void getInfo(int argc, char** argv)
    {
        printf("argc: %d\n", argc);
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

                if (argv[i+1] != NULL)
                    strcat(userName, " ");
            }
        }

        class PostEntry pe;

        /*getting user data*/
        char* data = pe.readInput();
        char* stream = initString(1000);
        stream = strtok(stream, " ");
        char* text = initString(10000);
        text = strtok(data, "\0");
        char* time = pe.getDateTime();

        userPost* post = pe.formatEntry(userName, stream, time, text);

        printf("stream: %s\n", post->streamname);
        return;
    }
};
int main(int argc, char const *argv[])
{
    int i = 0;
    class a myA;
    int newArgc = argc;
    char** newArgv = initArray(argc, 255);
    for (i = 0; i < argc; i++)
        strcpy(newArgv[i], argv[i]);
    myA.getInfo(newArgc, newArgv);

    destroyArray(newArgv, argc);


    return 0;
}