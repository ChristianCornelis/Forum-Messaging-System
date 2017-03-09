#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getTagContents(char* token, char* toFind);

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
    int first = 1;

    while (fgets(line, 255, fptr) != NULL)
    {
        int i;
        int inTag = 0;
        char* token;
        char* text = NULL;
        char* size = NULL;

        if (first == 1)
        {
            token = strtok(line, ")");
            first = 0;
        }
        else
            token = strtok(NULL, ")");

        printf("LINE: %s\n", line);

        if (token[1] == 'h')
        {
            if (strstr(token, "size=") != NULL)
            {
                size = getTagContents(token, "size=");
            }
            else if (strstr(token, "size=") == NULL)
            {
                size = calloc(3, sizeof(char));
                strcpy(size, "3");
            }
            else if (strstr(token, "text=") != NULL)
            {
                text = getTagContents(token, "text=\"");
            }
            else if (strstr(token, "text=") == NULL)
            {
                text = calloc(8, sizeof(char));
                strcpy(text, "HEADING");
            }

            printf("<h%s> ", size);
            printf("%s", text);
            printf(" </h%s>\n", size);
            free(size);
            free(text);
        }
        else if (token[1] == 't')
        {
            if (strstr(token, "text=") != NULL)
            {
                text = getTagContents(token, "text=\"");
            }
            else if (strstr(token, "file=") != NULL)
            {
                text = getTagContents(token, "file=\"");
            }
            else if (strstr(token, "text=") == NULL && strstr(token, "file=") == NULL)
            {
                text = calloc(15, sizeof(char));
                strcpy(text, "Default text");
            }

            printf("\n<p> %s </p>", text);
            free(text);
        }
        
    }

    fclose(fptr);
    return 0;
}

char* getTagContents(char* token, char* toFind)
{
    char* toReturn = calloc(255, sizeof(char));
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;

    if (strcmp(toFind, "size=") == 0)
    {
        for (i = 0; i < strlen(token); i++)
        {
            if (token[i] == toFind[j])
            {
                j++;
                if (j == strlen(toFind))
                {
                    for (k = i+1; k < strlen(token); k++)
                    {
                        if (token[k] == ',')
                            break;
                        toReturn[l] = token[k];
                        l++;   
                    }
                    return toReturn;
                }
            }
        }
    }

    for (i = 0; i < strlen(token); i++)
    {
        if (token[i] == toFind[j])
        {
            j++;
            if (j == strlen(toFind))
            {
                for (k = i+1; k < strlen(token); k++)
                {
                    if (token[k] == '"')
                        break;
                    toReturn[l] = token[k];
                    l++;   
                }
                return toReturn;
            }
        }
    }

    return toReturn;
}