#include "databaseManager.h"


int main(int argc, char const *argv[])
{
	MYSQL mysql;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	MYSQL_RES *res;
	char** records;


	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "databaseManager");

	if (mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0))
		handleError("Error: Connection to host unsuccessful.", &mysql);

	/*closing connection to database*/
	mysql_close(&mysql);
	return 0;
}

/*function to handle errors within the database*/
void handleError (char* msg, MYSQL *mysql)
{
	printf("%s\n%s\n", msg, mysql_error(mysql));
	exit(1);
}