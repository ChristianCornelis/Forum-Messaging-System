#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getTagContents(char* token, char* toFind, char tag);

int main(int argc, char *argv[])
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
    char* fileName = argv[1];
    char* toOutput = strtok(fileName, ".");
    strcat(toOutput, ".html");
    /*freopen(toOutput , "w", stdout);*/
	printf("<html>\n<body>\n\n");
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
        char* id = NULL;
        int printForm = 0;
        token = strtok(line, ")");

        if (strstr(line, ".i(") != NULL || strstr(line, ".b(") != NULL || strstr(line, ".r(") != NULL || strstr(line, ".q(") != NULL)
        {
            printForm = 1;
            if (strstr(line, ".i") != NULL && strstr(line, "id=\"") != NULL)
            {
                printf("<form id=\"%s\" action = \"%s\" method=\"post\">\n", (id = getTagContents(line, "id=\"", 'i')),(action = getTagContents(line, "action=\"", 'i')));
                free(id);
            }
            else if (strstr(line, ".b(") != NULL)
                printf("<form action = \"%s\" method=\"post\">\n", (action = getTagContents(line, "link=\"", 'b')));
            else
                printf("<form action = \"%s\" method=\"post\">\n", (action = getTagContents(line, "action=\"", 'i')));

            free(action);
        }

        while (token != NULL)
        {
            if (token[1] == 'h')
            {
                if (strstr(token, "size=<") != NULL)
                {
                    size = getTagContents(token, "size=<", 'h');
                }
                else if (strstr(token, "size=<") == NULL)
                {
                    size = calloc(3, sizeof(char));
                    strcpy(size, "3>");
                }
                if (strstr(token, "text=") != NULL)
                {
                    text = getTagContents(token, "text=\"", 'h');
                }
                else if (strstr(token, "text=") == NULL)
                {
                    text = calloc(8, sizeof(char));
                    strcpy(text, "HEADING");
                }

                printf("<h%s ", size);
                printf("%s", text);
                printf(" </h%s\n", size);
                free(size);
                free(text);
            }
            else if (token[1] == 't')
            {
                int filePrnt = 0;
                char toPrint[100000];
                if (strstr(token, "text=") != NULL)
                {
                    text = getTagContents(token, "text=\"", 't');
                }
                if (strstr(token, "file=") != NULL)
                {
                  filePrnt = 1;
                    text = getTagContents(token, "file=\"", 't');
                    char line[255];
                    FILE* fptr = fopen(text, "r");
                    while (fgets(line, 255, fptr) != NULL)
                    {
                      strcat(toPrint, line);
                    }
                    fclose(fptr);
                }
                else if (strstr(token, "text=") == NULL && strstr(token, "file=") == NULL)
                {
                    text = calloc(15, sizeof(char));
                    strcpy(text, "Default text");
                }
                if (filePrnt == 1)
                {
                  printf("\n<p> %s </p>", toPrint);
                }
                else
                  printf("\n<p> %s </p>", text);
                free(text);
            }
            else if (token[1] == 'b')
            {
                if (strstr(token, "name=") != NULL)
                {
                    name = getTagContents(token, "name=\"", 'b');
                }
                if (strstr(token, "link=") != NULL)
                {
                    link = getTagContents(token, "link=\"", 'b');
                }
				char name2[255];
				strcpy(name2, name);
				int l = 0;
				for (l = 0; l < strlen(name2); l++)
				{
					if (name2[l] == ' ')
						name2[l] = '_';
				}
                printf("\t<input type = \"submit\" value = \"%s\" name = \"%s\">\n", name, name2);
                free(name);
                free(link);
            }
            else if (token[1] == 'd')
            {
                printf("<hr> </hr>\n");
            }
            else if (token[1] == 'e')
            {
                if (strstr(token, "exe=") != NULL)
                {
                    /*file = calloc(255, sizeof(char));
                    strcpy(file, "./");*/
                    file = getTagContents(token, "exe=\"", 'e');
                }
                printf("FILE %s\n", file);
                FILE* fptr = NULL;
                /*char* binName = calloc(255, sizeof(char));*/
                char binName[255];
                char sysBinName[255];
                strcpy(binName, "/usr/local/bin/");
                strcpy(sysBinName, "/bin/");
                strcat(binName, file);
                strcat(sysBinName, file);

                if ((fptr = fopen(file, "r")) != NULL)
                {
                    char toRun[255];
                    strcpy(toRun, "./");
                    strcat(toRun, file);
                    system(toRun);
                    fclose(fptr);
                }
                else if ((fptr=fopen(binName, "r")) != NULL)
                {
                    system(binName);
                    fclose(fptr);
                }
                else if ((fptr=fopen(sysBinName, "r")) != NULL)
                {
                    system(sysBinName);
                    fclose(fptr);
                }

                free(file);
            }
            else if (token[1] == 'i')
            {
                char* subStr;
                while(strstr(token, "name=\"") != NULL)
                {

	              if ((subStr = strstr(token, "value=")) != NULL)
	              {
	                  value = getTagContents(token, "value=\"", 'i');
	                  token[subStr-token] = '@';
	              }

	              if ((subStr = strstr(token, "text=")) != NULL)
	              {
	                  text = getTagContents(token, "text=\"", 'i');
	                  token[subStr-token] = '@';
	              }

	              if ((subStr = strstr(token, "name=")) != NULL)
	              {
	                  name = getTagContents(token, "name=\"", 'i');
	                  token[subStr-token] = '@';
	              }
				  /*if the input field should be a text area and not a text input*/
				  if ((subStr = strstr(token, "textArea=\"True\"")) != NULL)
				  {
                      token[subStr-token] = '@';
					  printf("\t%s:<br>\n\t<textarea rows=\"5\" cols=\"60\" name=\"%s\">%s</textarea><br>", text, name, value);
				  }
				  else
	              	printf("\t%s:<br>\n\t<input type=\"text\" name = \"%s\" value = \"%s\"> <br> <br>\n", text, name, value);

	              free(value);
	              free(text);
	              free(name);
              }
            }
            else if (token[1] == 'l')
            {
                if (strstr(token, "text=") != NULL)
                    text=getTagContents(token, "text=\"", 'l');
                else
                {
                    text = calloc(5, sizeof(char));
                    strcpy(text, "link");
                }
                if (strstr(token, "link=") != NULL)
                    link = getTagContents(token, "link=\"", 'l');

                printf("\n\t<a href = \"%s\"> %s </a>\n", link, text);

                free(text);
                free(link);
            }
            else if (token[1] == 'p')
            {
                if (strstr(token, "image=") != NULL)
                    image = getTagContents(token, "image=\"", 'p');

                if (strstr(token, "size=") != NULL)
                    size = getTagContents(token, "size=", 'p');
                else if (strstr(token, "size=") == NULL)
                {
                    size = calloc(25, sizeof(char));
                    strcpy(size, "<100>x<100>");
                }

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
						i++;
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

                printf("\t<img src = \"%s\" alt = \"image\" style = \"width:%spx; height:%spx;\"> <br>\n" , image, width, height);
                free(size);
                free(image);
                free(width);
                free(height);
            }
            else if (token[1] == 'r')
            {
				char* subStr;
				int firstLoop = 1;
				while(strstr(token, "value=\"") != NULL)
				{
	                if ((subStr = strstr(token, "action=")) != NULL)
	                    action = getTagContents(token, "action=\"", 'r');
	                if ((subStr = strstr(token, "name=")) != NULL)
	                    name = getTagContents(token, "name=\"", 'r');
	                if ((subStr = strstr(token, "value=")) != NULL)
					{
	                    value = getTagContents(token, "value=\"", 'r');
						token[subStr-token] = '@';
					}
					if (firstLoop == 1)
					{
	                	printf("\t<input type = \"radio\" name = \"%s\" value = \"%s\" checked = \"checked\"> %s<br>\n", name, value, value);
						firstLoop = 0;
					}
					else
						printf("\t<input type = \"radio\" name = \"%s\" value = \"%s\"> %s<br>\n", name, value, value);

	                free(action);
	                free(name);
	                free(value);
				}
            }
			else if (token[1] == 'q')
			{
				char* subStr;
				if ((subStr = strstr(token, "value=")) != NULL)
				{
					value = getTagContents(token, "value=\"", 'i');
					token[subStr-token] = '@';
				}

				if ((subStr = strstr(token, "name=")) != NULL)
				{
					name = getTagContents(token, "name=\"", 'i');
					token[subStr-token] = '@';
				}

				printf("\n\t<input type=\"hidden\" name = \"%s\" value=\"%s\">\n", name, value);
				free(name);
				free(value);
			}

            token = strtok(NULL, ")");
        }
		if (printForm == 1 && (strstr(line, ".i(") != NULL || strstr(line, ".i(") != NULL))
			printf("\n\t<input type = \"submit\" name = \"submit\" value = \"Submit\">\n");
        if (printForm == 1)
      		printf("</form>\n");
    }

    fclose(fptr);
	printf("</body>\n</html>\n");

    return 0;
}

char* getTagContents(char* token, char* toFind, char tag)
{
    char* toReturn = calloc(255, sizeof(char));
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int closingCnt = 0;
    /*if looking for picture sizes*/
    if (strcmp(toFind, "size=") == 0 && tag == 'p')
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
                        if (token[k] == '>' && closingCnt == 1)
                            break;
						else if (token[k] == '>' && closingCnt == 0)
						{
							toReturn[l] = token[k];
							l++;
							closingCnt++;
							k++;
						}
                        toReturn[l] = token[k];
                        l++;
                    }
                    return toReturn;
                }
            }
            else
                j = 0;
        }
    }
    /*else if looking for a heading size*/
    else if (strcmp(toFind, "size=") == 0 && tag == 'h')
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
                        if (token[k] == '>')
                            break;
                        else
                          toReturn[l] = token[k];
                        l++;
                    }
                    return toReturn;
                }
            }
            else
                j = 0;
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
        else
            j = 0;
    }

    return toReturn;
}
