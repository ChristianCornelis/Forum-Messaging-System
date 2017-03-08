#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Error: No configuration file inputted.\nExitting.\n");
        return 1;
    }

    FILE* fptr = fopen(argv[1], "r");

    if (!fptr)
    {
        printf("Error: No such file.\nExitting\n");
        return 1;
    }

    char line[255];

    while (fgets(line, 255, fptr) != NULL)
    {
        int i;
        int inTag = 0;

        
        char* token;
        token = strtok(line, "(");
        char tag = ' ';
        if (strstr(token, ".h") != NULL)
            tag = 'h';

        switch(tag)
        {
            case 'h':
                printf("<h>");
                token = strtok(NULL, ")");
                if (strstr(token, "=") != NULL && strstr(token, "text") != NULL)
                {
                    char* token2 = strtok(token, "\"");
                    token2 = strtok(NULL, "\"");
                    printf("%s", token2);

                    if (strstr(token, "size") != NULL)
                }
                break;

        }


        
    }
    return 0;
}