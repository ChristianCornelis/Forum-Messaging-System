#include "db.h"


int main(int argc, char const *argv[])
{
	MYSQL mysql;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	MYSQL_RES *res;
	char* query = calloc(MAX_QUERY, sizeof(char));
	char author[255];
	char stream[255];
	char text[10000];
	/*vars to represent what mode we are in*/
	int adding = 0;
	int posting = 0;
	int viewing = 0;
	int removing = 0;

	if (strcmp(argv[1], "addAuthor") == 0)
	{
		adding = 1;
		if (argc != 4)
		{
			printf("Error: Incorrect number of arguments.\nExitting\n");
			mysql_close(&mysql);
			return 1;
		}
		strcpy(author, argv[2]);
		strcpy(stream, argv[3]);
	}
	else if (strcmp(argv[1], "post") == 0)
	{
		posting = 1;
		strcpy(author, argv[2]);
		strcpy(stream, argv[3]);
		strcpy(text, argv[4]);
	}
	else if (strcmp(argv[1], "view") == 0)
		viewing = 1;
	else if (strcmp(argv[1], "removeAuthor") == 0)
		removing = 1;

	int i;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");

	/*trying to connect to database*/
	if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0))
		handleError("Error: Connection to host unsuccessful.", &mysql);

	printf("Connection to host successful\n");
	if (adding)
	{
		printf("Creating table if it does not exist\n");
		strcpy(query, "create table if not exists authors (name char(255),stream char(255),last_post_read int,primary key(name, stream))");
		if (mysql_query(&mysql, query))
			handleError("Table creation not successful.", &mysql);
		query = clearQuery(query);

		strcpy(query, "create table if not exists streams (name char(255) primary key)");
		if (mysql_query(&mysql, query))
			handleError("Failed to create the stream table.\n", &mysql);

		strcpy(query, "select * from streams where name='");
		strcat(query, stream);
		strcat(query, "'");

		if (mysql_query(&mysql, query))
		{
			handleError("Failed to select from streams table<BR>/n", &mysql);
		}

		if (!(res = mysql_store_result(&mysql)))
		{
			handleError("Failed to store stream from stream table\n<BR>", &mysql);
		}

		/*checking if the stream is already in the streams table*/
		if (mysql_num_rows(res) == 0)
		{	
			/*create query to insert the current stream into the table*/
			query = clearQuery(query);
			strcpy(query, "insert into streams value('");
			strcat(query, stream);
			strcat(query, "')");

			if (mysql_query(&mysql, query))
			{
				handleError("Failed to insert stream into streams table.<BR>/n", &mysql);
			}

		}

		query = clearQuery(query);
		printf("Creation successful!\n");
		strcat(query, "insert into authors values ('");
		strcat(query, author);
		strcat(query, "','");
		strcat(query, stream);
		strcat(query, "',1)");

		printf("trying to add to table with query: %s\n", query);
		/*add author and handle if errors occur*/
		if (mysql_query(&mysql, query))
		{
			printf("Failed to insert author %s\n", author);
			handleError("Failed to insert record.", &mysql);
		}
		printf("Add successful!\n");
		query = clearQuery(query);
		strcpy(query, "select * from authors order by name");

		if (mysql_query(&mysql, query))
			handleError("Selection failed", &mysql);

		if (!(res = mysql_store_result(&mysql)))
		{
			handleError("Failed to store", &mysql);
		}

		printf("Trying to print rows!\n");
		while ((row = mysql_fetch_row(res)))
			printf("%s ", row[0]);
		printf("\n");
		query = clearQuery(query);


		strcpy(query, "select * from authors order by name");
	
		if(mysql_query(&mysql, query)){
			handleError("fail select 2",&mysql);
		}

		/*
			Store results from query into res structure.
		*/
		if (!(res = mysql_store_result(&mysql))){
			handleError("fail store 2",&mysql);
		}

		/*
			print all results
		*/
		while ((row = mysql_fetch_row(res))) {
			for (i=0; i < mysql_num_fields(res); i++){
				printf("%s ", row[i]);
			}
			printf("\n");
		}

		query = clearQuery(query);

	}

	else if (strcmp(argv[1], "-drop") == 0)
	{
		if (argc != 3)
		{
			printf("Error: Incorrect number of arguments");
			mysql_close(&mysql);
			exit(1);
		}
		strcpy(query, "drop table ");
		strcat(query, argv[2]);
		if (mysql_query(&mysql, query))
			handleError("Failed to drop table", &mysql);
		printf("table dropped\n");
	}
	/*else if removing an author from the database*/
	else if (removing == 1)
	{
		printf("Attempting to delete.\n");

		/*if incorrect number of arguments, exit the program.*/
		if (argc != 4)
		{
			printf("Error: Incorrect number of arguments.\nExitting\n");
			mysql_close(&mysql);
			exit(1);
		}

		strcpy(query, "delete from authors where name='");
		strcat(query, argv[2]);
		strcat(query, "' and stream='");
		strcat(query, argv[3]);
		strcat(query, "'");

		/*delete the entry from the authors table if it exists*/
		if(mysql_query(&mysql, query))
			handleError("Deletion failed.",&mysql);
	}
	else if (posting)
	{
		if (argc != 5)
		{
			printf("Error: Incorrect number of arguments.\nExitting\n");
			mysql_close(&mysql);
			return 1;
		}

		strcpy(query, "select * from authors where name='");
		strcat(query, author);
		strcat(query, "' and stream='");
		strcat(query, stream);
		strcat(query, "'");

		if (mysql_query(&mysql, query))
		{
			handleError("Failed to select from authors table<BR>/n", &mysql);
		}

		if (!(res = mysql_store_result(&mysql)))
		{
			handleError("Failed to store", &mysql);
		}

		if (mysql_num_rows(res) == 0)
		{
			handleError("This user does not have access to this stream.\n<BR>Use addauthor to gain permission to post to streams.\n<BR>", &mysql);
		}

		while ((row = mysql_fetch_row(res))) {
			for (i=0; i < mysql_num_fields(res); i++){
				printf("%s ", row[i]);
			}
			printf("\n");
		}
		query = clearQuery(query);

		strcpy(query, "create table if not exists posts (name char(255),stream char(255),text varchar(10000), date_time datetime)");
		if (mysql_query(&mysql, query))
			handleError("Post table creation not successful.", &mysql);
		query = clearQuery(query);

		strcat(query, "insert into posts values ('");
		strcat(query, author);
		strcat(query, "','");
		strcat(query, stream);
		strcat(query, "','");
		/*strcat(query, (mysql_real_escape_string(&mysql, end, text, ((int)strlen(text)))));*/
		strcat(query, text);
		strcat(query, "',NOW()");
		strcat(query, ")");

		if (mysql_query(&mysql, query))
			handleError("Failed to insert post.\n<BR>", &mysql);

		query = clearQuery(query);

		strcpy(query, "select * from posts order by name");
	
		if(mysql_query(&mysql, query)){
			handleError("fail select 2",&mysql);
		}
		if (!(res = mysql_store_result(&mysql))){
			handleError("fail store 2",&mysql);
		}

		while ((row = mysql_fetch_row(res))) {
			for (i=0; i < mysql_num_fields(res); i++){
				printf("%s ", row[i]);
			}
			printf("\n");
		}
		query = clearQuery(query);
	}
	else if (strcmp(argv[1], "-posts") == 0)
	{
		strcpy(query, "select * from posts order by name");
	
		if(mysql_query(&mysql, query)){
			handleError("Failed selecting from posts table\nThe table does not exist!\n",&mysql);
		}
		if (!(res = mysql_store_result(&mysql)))
		{
			handleError("fail store 2",&mysql);
		}

		printf("*******POSTS:*******\n");
		while ((row = mysql_fetch_row(res))) {
			for (i=0; i < mysql_num_fields(res); i++){
				printf("%s ", row[i]);
			}
			printf("\n");
		}
		query = clearQuery(query);
	}
	else if (strcmp(argv[1], "-streams") == 0)
	{
		strcpy(query, "select * from streams order by name");
	
		if(mysql_query(&mysql, query)){
			handleError("Failed selecting from streams table\nThe table does not exist!\n",&mysql);
		}
		if (!(res = mysql_store_result(&mysql))){
			handleError("fail store 2",&mysql);
		}

		printf("*******STREAMS:*******\n");
		while ((row = mysql_fetch_row(res))) {
			for (i=0; i < mysql_num_fields(res); i++){
				printf("%s ", row[i]);
			}
			printf("\n");
		}
		query = clearQuery(query);
	}
	else if (viewing)
	{
		if (argc != 5)
		{
			printf("Error: Incorrect number of arguments.\nExitting.\n");
			mysql_close(&mysql);
			return 1;
		}

		strcpy(author, argv[2]);
		strcpy(stream, argv[3]);
		int offset = atoi(argv[4]);

		/*building query to find the number of posts read by the current user*/
		query = clearQuery(query);
		strcpy(query, "select * from authors where name='");
		strcat(query, author);
		strcat(query, "' and stream ='");
		strcat(query, stream);
		strcat(query, "'");

		if(mysql_query(&mysql, query)){
			handleError("Failed selecting from authors table\nThe table does not exist!\n",&mysql);
		}
		if (!(res = mysql_store_result(&mysql)))
		{
			handleError("Store failed.",&mysql);
		}

		/*saving the current number of posts read*/
		int curPost = -1;
		while ((row = mysql_fetch_row(res)))
		{
			curPost = atoi(row[2]);
		}
		printf("CURPOST IS %d\n", curPost);
		query = clearQuery(query);

		strcpy(query, "select * from posts where stream='");
		strcat(query, stream);
		strcat(query, "'");

		if(mysql_query(&mysql, query)){
			handleError("Failed selecting from authors table\nThe table does not exist!\n",&mysql);
		}
		if (!(res = mysql_store_result(&mysql)))
		{
			handleError("Store failed.",&mysql);
		}

		int numPosts = -1;
		numPosts = (int) mysql_num_rows(res);
		/*
		strcpy(query, "select count(*) from posts");
		if(mysql_query(&mysql, query)){
			handleError("Failed selecting from authors table\nThe table does not exist!\n",&mysql);
		}
		if (!(res = mysql_store_result(&mysql)))
		{
			handleError("Store failed.",&mysql);
		}

		int numPosts = -1;
		while ((row = mysql_fetch_row(res)))
		{
			numPosts = atoi(row[0]);
		}*/

		printf("NUM POSTS IS %d\n", numPosts);
		int oldCount = curPost;
		curPost += offset;
		strcpy(query, "select * from posts where stream='");
		strcat(query, stream);
		strcat(query,"'");

		printf("CURPOST W OFFSET IS %d\n", curPost);
		if(mysql_query(&mysql, query)){
			handleError("Failed selecting from posts table\nThe table does not exist!\n",&mysql);
		}
		if (!(res = mysql_store_result(&mysql)))
		{
			handleError("fail store 2",&mysql);
		}

		int postCnt = 0;
		while ((row = mysql_fetch_row(res))) {
			if (postCnt == curPost)
			{
				char textCpy[12000];
				strcpy(textCpy, row[2]);
				int j;
				for (j = 0; j < strlen(textCpy); j++)
				{
					if (textCpy[j] == '\n')
						printf("<BR>");
					else
						printf("%c", textCpy[j]);
				}
			}
			postCnt++;
		}
		query = clearQuery(query);

		if (oldCount < numPosts)
		{
			strcpy(query, "update authors set last_post_read = 1 + authors.last_post_read where name='");
			strcat(query, author);
			strcat(query, "' and stream = '");
			strcat(query, stream);
			strcat(query, "'");

			if(mysql_query(&mysql, query)){
				handleError("Failed selecting from posts table\nThe table does not exist!\n",&mysql);
			}
		}

	}

	/*closing connection to database*/
	free(query);
	mysql_close(&mysql);

	printf("Finished!\n");
	return 0;
}

/*function to handle errors within the database*/
void handleError (char* msg, MYSQL *mysql)
{
	printf("%s\n%s\n", msg, mysql_error(mysql));
	exit(1);
}

/*function to clear the query*/
char* clearQuery(char* query)
{
	int i;
	for (i = 0; i < MAX_QUERY; i++)
	{
		query[i] = '\0';
	}

	return query;
}