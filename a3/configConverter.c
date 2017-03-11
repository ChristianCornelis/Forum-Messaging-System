#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getTagContents(char* token, char* toFind);

int main(int argc, char const *argv[])
{
    freopen("test.html" , "w", stdout);
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
        char* token;
        char* text = NULL;
        char* size = NULL;
        char* name = NULL;
        char* link = NULL;
        char* file = NULL;
        char* action = NULL;
        char* value = NULL;
        char* image = NULL;

        token = strtok(line, ")");

        while (token != NULL)
        {
            if (token[1] == 'h')
            {
                if (strstr(token, "size=") != NULL)
                {
                    size = getTagContents(token, "size=\"");
                }
                else if (strstr(token, "size=") == NULL)
                {
                    size = calloc(3, sizeof(char));
                    strcpy(size, "3");
                }
                if (strstr(token, "text=") != NULL)
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
                if (strstr(token, "file=") != NULL)
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
            else if (token[1] == 'b')
            {
                if (strstr(token, "name=") != NULL)
                {
                    name = getTagContents(token, "name=\"");
                }
                if (strstr(token, "link=") != NULL)
                {
                    link = getTagContents(token, "link=\"");
                }

                printf("\n<form action = %s>\n\t<input type = \"submit\" value = %s> \n</form>\n", link, name);
                free(name);
                free(link);
            }
            else if (token[1] == 'd')
            {
                printf("<hr> </hr>\n");
            }
            else if (token[1] == 'e')
            {
                if (strstr(token, "file=") != NULL)
                {
                    file = getTagContents(token, "file=\"");
                }

                printf("<?php\n\techo exec '%s';\n?>\n", file);

                free(file);
            }
            else if (token[1] == 'i')
            {
                if (strstr(token, "action=") != NULL)
                {
                    action = getTagContents(token, "action=\"");
                }

                if (strstr(token, "value=") != NULL)
                    value = getTagContents(token, "value=\"");

                if (strstr(token, "text=") != NULL)
                    text = getTagContents(token, "text=\"");

                if (strstr(token, "name=") != NULL)
                    name = getTagContents(token, "name=\"");

                printf("<form action=\"%s\">\n\t%s:<br>\n\t<input type=\"text\" name = \"%s\" value = \"%s\"> <br> <br>", action, text, name, value);
                printf("\n\t<input type = \"submit\" value = \"Submit\">\n</form>\n)");

                free(action);
                free(value);
                free(text);
                free(name);
            }
            else if (token[1] == 'l')
            {
                if (strstr(token, "text=") != NULL)
                    text=getTagContents(token, "text=\"");
                else
                {
                    text = calloc(5, sizeof(char));
                    strcpy(text, "link");
                }
                if (strstr(token, "link=") != NULL)
                    link = getTagContents(token, "link=\"");

                printf("\n\t<a href = \"%s\"> %s </a>\n", link, text);

                free(text);
                free(link);
            }
            else if (token[1] == 'p')
            {
                if (strstr(token, "image=") != NULL)
                    image = getTagContents(token, "image=\"");

                if (strstr(token, "size=") != NULL)
                    size = getTagContents(token, "size=");
                else if (strstr(token, "size=") == NULL)
                {
                    size = calloc(25, sizeof(char));
                    strcpy(size, "<100><100>");
                }

                printf("SIZE %s\n", size);
                char* width = calloc(25, sizeof(char));
                char* height = calloc(25, sizeof(char));
                int i = 0;
                int j = 0;
                int closeCnt = 0;

                /*pulling out dimensions*/
                for (i = 0; i < strlen(size); i++)
                {
                    if (size[i] == '>' && closeCnt == 2)
                        break;
                    else if (size[i] == '>')
                    {
                        closeCnt++;
                        j = 0;
                        continue;
                    }

                    if (size[i] != '<' && closeCnt == 0)
                    {
                        width[j] = size[i];
                        j++;
                    }
                    else if (size[i] != '<' && closeCnt == 1)
                    {
                        height[j] = size[i];
                        j++;
                    }
                }

                printf("\t<img src = \"%s\" alt = \"image\" style = \"width:%spx; height:%spx;\">\n" , image, width, height);
                free(size);
                free(image);
                free(width);
                free(height);
            }
            else if (token[1] == 'r')
            {
                if (strstr(token, "action=") != NULL)
                    action = getTagContents(token, "action=\"");
                if (strstr(token, "name=") != NULL)
                    name = getTagContents(token, "name=\"");
                if (strstr(token, "value=") != NULL)
                    value = getTagContents(token, "value=\"");

                printf("<form action = \"%s\">\n\t<input type = \"radio\" name = \"%s\" value = \"%s\"> %s<br>\n</form>\n", action, name, value, value);

                free(action);
                free(name);
                free(value);
            }

            token = strtok(NULL, ")");
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
    int closingCnt = 0;
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
                        if (token[k] == '>' && closingCnt == 2)
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