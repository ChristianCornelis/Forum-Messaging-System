#include "stream.h"
#include "helperFunctions.h"

class PostEntry
{
    char* readInput(char* username)
    {
        printf("\nstream: ");
        char * stream = initString(1000);

        fgets(stream, 1000, stdin);
        char* line = initString(500);
        char* text = initString(10000);
        strcpy(text, stream); 
        stream[strlen(stream)-1] = '\0';
        char* filename = initString(1000);

        /*if messages folder does not exist, then create it*/
        if (!opendir("messages"))
        {
            mkdir("messages/", 0777);
        }
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
                if (argc > 2 && i + 1 != argc)
                    strcat(userName, " ");
            }
        }

        class PostEntry pe;

        /*getting user data*/
        char* data = pe.readInput(userName);
        
        /*if the user has permission to post in the stream, then update the files necessary*/
        if (strcmp(data, "") != 0)
        {
            printf("%s\n", data);
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
            /*char* stream = strtok(data, "\n");
            char* text = "\n";
            int a = (int) strlen(stream) +1;
            int b = 0;
            printf("a %d\n", a);
            while (data[a] != '\0')
            {
                text[b] = data[a];
            }
            printf("|%s|\n", data);*/
            printf("stream; %s\n text: %s\n", stream, text);
            /*char* text = strtok(NULL, "\0");*/
            char* time = pe.getDateTime();

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
    class a myA;
    int newArgc = argc;
    char** newArgv = initArray(argc, 255);
    for (i = 0; i < argc; i++)
        strcpy(newArgv[i], argv[i]);
    myA.getInfo(newArgc, newArgv);
    destroyArray(newArgv, argc);


    return 0;
}