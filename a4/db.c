#include "db.h"

int main(int argc, char const *argv[])
{
	MYSQL mysql;
	MYSQL_ROW row;
	MYSQL_RES *res;
	char* query = calloc(MAX_QUERY_LENGTH, sizeof(char));
	char author[255];
	char stream[255];
	char text[10000];
	/*vars to represent what mode we are in*/
	int adding = 0;
	int posting = 0;
	int viewing = 0;
	int removing = 0;

	/*if adding an author to the database*/
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
	/*if sending a post to the database*/
	else if (strcmp(argv[1], "post") == 0)
	{
		posting = 1;
		if (argc != 5)
		{
			printf("Error: Incorrect number of arguments.\nExitting\n");
			mysql_close(&mysql);
			return 0;
		}

		strcpy(author, argv[2]);
		strcpy(stream, argv[3]);
		strcpy(text, argv[4]);
	}
	/*if viewing a post*/
	else if (strcmp(argv[1], "view") == 0)
		viewing = 1;
	/*if removing an author from the database*/
	else if (strcmp(argv[1], "removeAuthor") == 0)
	{
		removing = 1;

		if (argc != 4)
		{
			printf("Error: Incorrect number of arguments.\nExitting.\n");
			return 0;
		}
		strcpy(author, argv[2]);
		strcpy(stream, argv[3]);
	}

	int i;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");

	/*trying to connect to database*/
	if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0))
		handleError("Error: Connection to host unsuccessful.", &mysql);

	if (adding)
	{
		strcpy(query, "create table if not exists authors (name char(255),stream char(255),last_post_read int,primary key(name, stream))");
		if (mysql_query(&mysql, query))
			handleError("Users table creation not successful.", &mysql);
		query = clearQuery(query);

		strcpy(query, "create table if not exists streams (name char(255) primary key)");
		if (mysql_query(&mysql, query))
			handleError("Failed to create the streams table.\n", &mysql);

		strcpy(query, "select * from streams where name='");
		strcat(query, stream);
		strcat(query, "'");

		/*check if the stream is already in the streams table*/
		if (mysql_query(&mysql, query))
			handleError("Failed to select from streams table<BR>/n", &mysql);

		/*trying to store results*/
		if (!(res = mysql_store_result(&mysql)))
			handleError("Failed to store stream from stream table\n<BR>", &mysql);

		/*checking if the stream is already in the streams table*/
		if (mysql_num_rows(res) == 0)
		{	
			/*create query to insert the current stream into the table*/
			query = clearQuery(query);
			strcpy(query, "insert into streams value('");
			strcat(query, stream);
			strcat(query, "')");

			if (mysql_query(&mysql, query))
				handleError("Failed to insert stream into streams table.<BR>/n", &mysql);

		}

		query = clearQuery(query);
		strcat(query, "insert into authors values ('");
		strcat(query, author);
		strcat(query, "','");
		strcat(query, stream);
		strcat(query, "',0)");

		/*add author and handle if errors occur*/
		if (mysql_query(&mysql, query))
			printf("Failed to insert user into the users table:<BR>%s is already in the %s table.<BR>", author, stream);
		else
			printf("User successfully added to the %s stream.<BR>", stream);
		query = clearQuery(query);
	}

	else if (strcmp(argv[1], "-clear") == 0)
	{
		if (argc != 2)
		{
			printf("Error: Incorrect number of arguments");
			mysql_close(&mysql);
			return 0;
		}
		
		/*creating all tables if they do not exist*/

		strcpy(query, "create table if not exists authors (name char(255),stream char(255),last_post_read int,primary key(name, stream))");
		if (mysql_query(&mysql, query))
			handleError("Users table creation not successful.", &mysql);
		query = clearQuery(query);

		strcpy(query, "create table if not exists posts (name char(255),stream char(255),text varchar(10000), date_time datetime)");
		if (mysql_query(&mysql, query))
			handleError("Posts table creation not successful.", &mysql);
		query = clearQuery(query);

		strcpy(query, "create table if not exists streams (name char(255) primary key)");
		if (mysql_query(&mysql, query))
			handleError("Streams table creation not successful.", &mysql);
		query = clearQuery(query);

		/*getting count from stream table*/
		sprintf(query, "select count(*) from streams");
		if (mysql_query(&mysql, query))
			handleError("Failed to get count from streams table.", &mysql);

		/*storing results*/
		if (!(res = mysql_store_result(&mysql)))
			handleError("Failed to store results of count for streams table.", &mysql);

		/*calculating the number of rows*/
		int numRows = -1;
		while ((row = mysql_fetch_row(res)))
			numRows = atoi(row[0]);

		/*if 0, table is already empty*/
		if (numRows == 0)
		{
			printf("The streams table is already empty.\n");
		}
		/*else drop the table and recreate it*/
		else
		{
			query = clearQuery(query);
			sprintf(query, "truncate table streams");

			if (mysql_query(&mysql, query))
				handleError("Failed to get clear streams table.", &mysql);
			else
				printf("Streams table cleared successfully.\n");
		}

		query = clearQuery(query);

		/*getting count from authors table*/
		sprintf(query, "select count(*) from authors");
		if (mysql_query(&mysql, query))
			handleError("Failed to get count from users table.", &mysql);

		/*storing results*/
		if (!(res = mysql_store_result(&mysql)))
			handleError("Failed to store results of count for users table.", &mysql);

		/*calculating the number of rows*/
		numRows = -1;
		while ((row = mysql_fetch_row(res)))
			numRows = atoi(row[0]);

		/*if 0, table is already empty*/
		if (numRows == 0)
		{
			printf("The users table is already empty.\n");
		}
		/*else drop the table and recreate it*/
		else
		{
			query = clearQuery(query);
			sprintf(query, "truncate table authors");

			if (mysql_query(&mysql, query))
				handleError("Failed to clear users table.", &mysql);
			else
				printf("Users table cleared successfully.\n");
		}

		query = clearQuery(query);

		/*getting count from posts table*/
		sprintf(query, "select count(*) from posts");
		if (mysql_query(&mysql, query))
			handleError("Failed to get count from posts table.", &mysql);

		/*storing results*/
		if (!(res = mysql_store_result(&mysql)))
			handleError("Failed to store results of count for posts table.", &mysql);

		/*calculating the number of rows*/
		numRows = -1;
		while ((row = mysql_fetch_row(res)))
			numRows = atoi(row[0]);

		/*if 0, table is already empty*/
		if (numRows == 0)
		{
			printf("The posts table is already empty.\n");
		}
		/*else drop the table and recreate it*/
		else
		{
			query = clearQuery(query);
			sprintf(query, "truncate table posts");

			if (mysql_query(&mysql, query))
				handleError("Failed to clear posts table.", &mysql);
			else
				printf("Posts table cleared successfully.\n");
		}

		query = clearQuery(query);
	}
	/*else if removing an author from the database*/
	else if (removing == 1)
	{

		/*if incorrect number of arguments, exit the program.*/
		if (argc != 4)
		{
			printf("Error: Incorrect number of arguments.\nExitting\n");
			mysql_close(&mysql);
			exit(1);
		}

		sprintf(query, "select * from authors where name='%s' and stream='%s'", author, stream);

		/*delete the entry from the authors table if it exists*/
		if(mysql_query(&mysql, query))
			handleError("<BR>Failed to select user from users table.<BR>",&mysql);

		/*storing results*/
		if (!(res = mysql_store_result(&mysql)))
			handleError("Failed to store results of count for posts table.", &mysql);

		/*calculating the number of rows*/
		int numRows = 0;
		while ((row = mysql_fetch_row(res)))
			numRows++;

		/*if the user is not in the stream then exit.*/
		if (numRows == 0)
		{
			printf("%s is not in the %s stream and cannot be removed from it.<BR>\n", author, stream);
			return 0;
		}
		query = clearQuery(query);

		strcpy(query, "delete from authors where name='");
		strcat(query, argv[2]);
		strcat(query, "' and stream='");
		strcat(query, argv[3]);
		strcat(query, "'");

		/*delete the entry from the authors table if it exists*/
		if(mysql_query(&mysql, query))
			handleError("Deletion of author failed.",&mysql);
		else
			printf("%s successfully removed from the %s stream.<BR>\n", author, stream);
	}
	else if (posting)
	{

		strcpy(query, "select * from authors where name='");
		strcat(query, author);
		strcat(query, "' and stream='");
		strcat(query, stream);
		strcat(query, "'");

		if (mysql_query(&mysql, query))
		{
			handleError("Failed to select from users table. Table is empty.<BR>", &mysql);
		}

		if (!(res = mysql_store_result(&mysql)))
		{
			handleError("Failed to store", &mysql);
		}

		if (mysql_num_rows(res) == 0)
		{
			handleError("This user does not have access to this stream.\n<BR>Use the  add author page to gain permission to post to streams.\n<BR>", &mysql);
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
		strcat(query, text);
		strcat(query, "',NOW()");
		strcat(query, ")");

		printf("QUERY IS %s\n", query);
		if (mysql_query(&mysql, query))
			handleError("Failed to insert post.\n<BR>", &mysql);
		else
			printf("Post successfully added to the %s stream.<BR>\n", stream);
		query = clearQuery(query);
	}
	else if (strcmp(argv[1], "-posts") == 0)
	{
		strcpy(query, "select * from posts order by date_time");
	
		if(mysql_query(&mysql, query))
			handleError("Failed selecting from posts table\nThe table does not exist!\n",&mysql);
		
		if (!(res = mysql_store_result(&mysql)))
			handleError("Failed to store results for selection of posts in posts table.",&mysql);

		printf("*******POSTS:*******\n");
		int cnt = 0;
		while ((row = mysql_fetch_row(res))) {
			for (i = 0; i < mysql_num_fields(res); i++){
				printf("%s ", row[i]);

				if (i+1 == (int) mysql_num_fields(res)-2)
				{
					printf("\n");
					printf("********TEXT********\n");
				}
				else if (i+1 == (int) mysql_num_fields(res)-1)
				{
					printf("********************\n");
					printf("Date in database: ");
				}
			}
			cnt++;
			printf("\n\n");
		}
		if (cnt == 0)
			printf("No posts to display.\n");
		query = clearQuery(query);
	}
	else if (strcmp(argv[1], "-streams") == 0)
	{
		strcpy(query, "select * from streams order by name");
	
		if(mysql_query(&mysql, query))
			handleError("Failed selecting from streams table\nThe table does not exist or is empty!",&mysql);
		
		if (!(res = mysql_store_result(&mysql)))
			handleError("Failed to store results for streams.",&mysql);
		

		printf("*******STREAMS:*******\n");
		while ((row = mysql_fetch_row(res))) {
			for (i=0; i < mysql_num_fields(res); i++)
			{
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

		if(mysql_query(&mysql, query))
			handleError("This user does not have access to any streams.<BR>\n",&mysql);
		
		if (!(res = mysql_store_result(&mysql)))
			handleError("Store failed.",&mysql);

		/*saving the current number of posts read*/
		int curPost = -1;
		int found = 0;
		while ((row = mysql_fetch_row(res)))
		{
			found = 1;
			curPost = atoi(row[2]);
		}

		if (found == 0)
			handleError("Error: This user does not have access to this stream.", &mysql);
		query = clearQuery(query);

		strcpy(query, "select * from posts where stream='");
		strcat(query, stream);
		strcat(query, "'");

		if(mysql_query(&mysql, query))
			handleError("Failed selecting from users table\nThe table does not exist!\n",&mysql);
		
		if (!(res = mysql_store_result(&mysql)))
			handleError("Store failed.",&mysql);

		int numPosts = -1;
		numPosts = (int) mysql_num_rows(res);
		if (numPosts == 0)
			printf("No posts to display");
		int oldCount = curPost;

		curPost += offset;

		if (curPost < 0)
		{
			printf("*AT BEGINNING*");
			curPost = 0;
		}
		else if (curPost > numPosts-1)
		{
			curPost = numPosts -1;
		}
		strcpy(query, "select * from posts where stream='");
		strcat(query, stream);
		strcat(query,"'");

		if(mysql_query(&mysql, query))
			handleError("Failed selecting from posts table\nThe table does not exist!\n",&mysql);

		if (!(res = mysql_store_result(&mysql)))
			handleError("fail store 2",&mysql);

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

		if (oldCount < numPosts && (oldCount +offset >= oldCount))
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

	else if (strcmp(argv[1], "-users") == 0)
	{
		strcpy(query, "select * from authors order by name");
	
		if(mysql_query(&mysql, query))
			handleError("Error: The users table is empty or does not exist.",&mysql);

		/*storing results*/
		if (!(res = mysql_store_result(&mysql)))
			handleError("Error: The users table is empty or does not exist.",&mysql);

		/*going through all of the rows*/
		while ((row = mysql_fetch_row(res)))
		{
			for (i=0; i < mysql_num_fields(res); i++)
			{
				printf("%s ", row[i]);
			}
			printf("\n");
		}
	}
	/*marking all posts in a stream as read*/
	else if (strcmp(argv[1], "markAll") == 0)
	{	
		/*checking that correct number of arguments are present*/
		if (argc != 4)
		{
			printf("Error: Incorrect number of arguments.<BR>\nExitting.\n<BR>");
			return 0;
		}

		printf("*AT END*");
		/*copying author and stream from arguments*/
		strcpy(author, argv[2]);
		strcpy(stream, argv[3]);

		sprintf(query, "select * from authors where name='%s' and stream='%s'", author, stream);

		if(mysql_query(&mysql, query))
			handleError("Failed selecting from users table\nThe table does not exist!\n",&mysql);

		/*storing results*/
		if (!(res = mysql_store_result(&mysql)))
			handleError("Store failed.",&mysql);

		/*checking if the user has access to the desired stream*/
		int results = -1;
		results = (int) mysql_num_rows(res);
		if (results == 0)
		{
			printf("Error: This user does not have access to the %s stream.", stream);
			return 0;
		}

		/*building query to get total number of posts in a stream*/
		strcpy(query, "select * from posts where stream='");
		strcat(query, stream);
		strcat(query, "'");

		/*checking if query was successful or not*/
		if(mysql_query(&mysql, query))
			handleError("Failed selecting from users table\nThe table does not exist!\n",&mysql);

		/*storing results*/
		if (!(res = mysql_store_result(&mysql)))
			handleError("Store failed.",&mysql);

		int numPosts = -1;
		numPosts = (int) mysql_num_rows(res);

		/*making query for updating all posts read*/
		sprintf(query, "update authors set last_post_read = %d where name='%s' and stream='%s'", numPosts, author, stream);

		/*checking if query was successful or not*/
		if(mysql_query(&mysql, query))
			handleError("Failed to mark all posts as read in the post table!\n",&mysql);
		
		query = clearQuery(query);
		/*printing the most recent post now*/
		strcpy(query, "select * from posts where stream='");
		strcat(query, stream);
		strcat(query,"'");

		if(mysql_query(&mysql, query))
			handleError("Failed selecting from posts table\nThe table does not exist!\n",&mysql);
		
		if (!(res = mysql_store_result(&mysql)))
			handleError("fail store 2",&mysql);

		int postCnt = 0;
		while ((row = mysql_fetch_row(res))) {
			if (postCnt == numPosts-1)
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

		if (postCnt == 0)
			printf("No posts to display.");
		query = clearQuery(query);
	}
	else if (strcmp(argv[1], "output") == 0)
	{
		if (argc != 3)
		{
			printf("Error: Incorrect number of arguments\n<BR>Exitting.<BR>\n");
			return 0;
		}

		strcpy(author, argv[2]);

		sprintf(query, "select * from authors where name='%s'", author);

		if(mysql_query(&mysql, query))
			handleError("Failed selecting from users table\nThe table does not exist!\n",&mysql);
		
		if (!(res = mysql_store_result(&mysql)))
			handleError("Store failed.",&mysql);

		int cnt = 0;
		while ((row = mysql_fetch_row(res)))
		{
			printf("%s ", row[1]);
			cnt++;
		}

		if (cnt == 0)
			printf("This user has access to no posts.");
		else
			printf("all");
	}
	else if (strcmp(argv[1], "viewAll") == 0)
	{
		printf("IN VIEW ALL\n");
		if (argc != 5)
		{
			printf("Error: Incorrect number of arguments.\n<BR>Exitting.\n<BR>");
			return 0;
		}

		strcpy(stream, argv[2]);
		strcpy(author, argv[3]);
		int offset = atoi(argv[4]);

		sprintf(query, "select * from posts where stream in (select stream from authors where name = '%s')", author);
		if(mysql_query(&mysql, query))
			handleError("Failed selecting from posts table with subquery to users table.\nEither table does not exist!\n",&mysql);

		if (!(res = mysql_store_result(&mysql)))
			handleError("Store failed.",&mysql);

		int numRows = (int) mysql_num_rows(res);

		printf("NUM ROWS IS %d\n", numRows);
		if (offset > numRows-1)
		{
			offset = numRows-1;
			printf("*AT ALL END*");
		}

		int postCnt = 0;
		while ((row = mysql_fetch_row(res))) 
		{
			if (postCnt == offset)
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

		if (postCnt == 0)
			printf("This user has access to no posts.");
	}
	else if (strcmp(argv[1], "allMarkAll") == 0)
	{
		/*checking that correct number of arguments are present*/
		if (argc != 4)
		{
			printf("Error: Incorrect number of arguments.<BR>\nExitting.\n<BR>");
			return 0;
		}

		/*copying author and stream from arguments*/
		strcpy(author, argv[2]);
		strcpy(stream, argv[3]);

		sprintf(query, "select * from authors where name='%s'", author);
		if(mysql_query(&mysql, query))
			handleError("Failed selecting from author table.\nThe table does not exist!\n",&mysql);

		/*storing results*/
		if (!(res = mysql_store_result(&mysql)))
			handleError("Store failed.",&mysql);

		while ((row = mysql_fetch_row(res))) 
		{
			strcpy(stream, row[1]);

			MYSQL_RES * res2;
			query = clearQuery(query);

			sprintf(query, "select * from posts where stream='%s'", stream);
			if(mysql_query(&mysql, query))
				handleError("Failed selecting from posts table.\nThe table does not exist!\n",&mysql);

			/*storing results*/
			if (!(res2 = mysql_store_result(&mysql)))
				handleError("Store failed.",&mysql);

			int numPosts = -1;
			numPosts = (int) mysql_num_rows(res2);

			query = clearQuery(query);
			sprintf(query, "update authors set last_post_read = %d where name='%s' and stream='%s'", numPosts, author, stream);

			/*checking if query was successful or not*/
			if(mysql_query(&mysql, query))
				handleError("Failed to mark all posts as read in the post table!\n",&mysql);
		}

		query = clearQuery(query);
		/*printing out last post now*/
		sprintf(query, "select * from posts where stream in (select stream from authors where name = '%s')", author);
		if(mysql_query(&mysql, query))
			handleError("Failed selecting from posts table with subquery to users table.\nEither table does not exist!\n",&mysql);

		if (!(res = mysql_store_result(&mysql)))
			handleError("Store failed.",&mysql);

		int offset = 0;
		int postCnt = 0;

		/*printing out post*/
		while ((row = mysql_fetch_row(res))) 
		{
			if (postCnt == offset)
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
	}
	else if (strcmp(argv[1], "-reset") == 0)
	{
		query = clearQuery(query);
		sprintf(query, "drop table streams");

		if (mysql_query(&mysql, query))
			printf("The streams table does not exist and cannot be dropped.\n");
		else
			printf("Streams table dropped successfully.\n");
	
		query = clearQuery(query);
		sprintf(query, "drop table authors");

		if (mysql_query(&mysql, query))
			printf("The users table does not exist and cannot be dropped.\n");
		else
			printf("Users table dropped successfully.\n");
	
		query = clearQuery(query);
		sprintf(query, "drop table posts");

		if (mysql_query(&mysql, query))
			printf("The posts table does not exist and cannot be dropped.\n");
		else
			printf("Posts table dropped successfully.\n");

	}
	else if (strcmp(argv[1], "-help") == 0)
	{
		printf("\n*******DB PROGRAM HELP*******\n");
		printf("Commands and how to run them:\n\n");
		printf("-users\n\tOutputs the contents of the table containing all users, the streams they have access to,"); 
		printf("and the last post that they read in that stream.\n\tOutputs data for each row in the table in that order.\n\n");
		printf("-posts\n\tOutputs the contents of the table containing all posts.\n\tData stored in this table for each row includes the user, the stream name, ");
		printf("the content of the post, and the data and time it was sent to the database.\n\tThe content of the post is in between a header of asterisks marked ******TEXT******\n\n");
		printf("-streams\n\tLists all streams that are present in the database currently.\n\n");
		printf("-clear\n\tClears all tables in the database.\n\tIf a table is already empty an appropriate message will be outputted.\n\tThis flag will create the tables if they do not exist.\n\n");
		printf("-reset\n\tDeletes all tables from the database.\n");
	}
	/*closing connection to database*/
	free(query);
	mysql_close(&mysql);

	return 0;
}

/*function to handle errors within the database*/
void handleError (char* msg, MYSQL *mysql)
{
	printf("%s\n%s\n", msg, mysql_error(mysql));
	exit(0);
}

/*function to clear the query*/
char* clearQuery(char* query)
{
	int i;
	for (i = 0; i < MAX_QUERY_LENGTH; i++)
	{
		query[i] = '\0';
	}

	return query;
}