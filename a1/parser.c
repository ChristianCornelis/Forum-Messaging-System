#include "helperFunctions.h"
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Incorrect number of arguments. \nExitting");
        return 1;
    }
    FILE* ccFile = NULL;
    ccFile = fopen(argv[1], "r");

    if (ccFile == NULL)
    {
        printf("File not found. \nExitting");
        return 1;
    }

    int character = -1;

    while ((character = getc(ccFile)) != EOF)
    {
        if (character == '"')
        {
            printf("%c", character);
            character = getc(ccFile);
            while (character != '"')
            {
                printf("%c", character);
                character = getc(ccFile);

                if (character == '\\')
                {
                    printf("%c%c" , character, getc(ccFile));
                    character = getc(ccFile);
                }
            }
            printf("%c", character);
        }
        else if (character == '/')
        {
            printf("%c", character);

            if ((character = getc(ccFile)) == '/')
            {
                while (character != '\n')
                {
                    printf("%c", character);
                    character = getc(ccFile);
                }
                printf("%c", character);
            }

            else if (character == '*')
            {
                printf("%c" , character);
                character = getc(ccFile);
                while (character != '/')
                {
                    printf("%c" , character);
                    character = getc(ccFile);
                }
                printf("%c" , character);
                continue;
            }
        }
        else if (character == '\n' ||character == ' ' || character == '\t')
            printf("\n");
        else if (character == ',' || character == ';' || character == '(' || character == ')' || character == '{' || character == '}')
            printf("%c\n" , character);
        else
            printf("%c", character);
    } 

    char ** array = initArray(10, 5);
    destroyArray(array, 10);
    fclose(ccFile);

    return 0;
}