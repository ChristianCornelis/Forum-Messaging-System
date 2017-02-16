#include "stream.h"
#include "helperFunctions.h"
class PostEntry
{
    struct userpost* readInput()
    {
        printf("\nstream: ");
        char* stream = " ";
        while (strcmp("", stream) != 0)
            scanf("%s", stream);

        char line[255];
        char* text = initString(2000);
        while(fgets(line, 255, stdin) != NULL)
        {
            printf("-\n");
            strcat(text, line);
        }


    }
    void formatEntry()
    {
        return;
    }
    void getDateTime()
    {
        return;
    }
    void submitPost()
    {
        return;
    }   
};

class a
{
    void getInfo(int argc, char const * argv[])
    {
        int i;
        if (argc > 2)
        {
            printf("Error: Not enough arguments.\nExitting.\n");
        }

        for (i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-r") == 0)
            {
                printf("Error: Username cannot be '-r'.\nExitting.\n");
                exit(1);
            }
        }
    }
};
int main(int argc, char const *argv[])
{
    class a myA;
    int newArgc = argc;
    char** newArgv = &argv;
    myA.getInfo(newArgc, &newArgv);
    return 0;
}