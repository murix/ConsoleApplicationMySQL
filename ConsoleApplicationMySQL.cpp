// ConsoleApplicationMySQL.cpp : Define o ponto de entrada para a aplicação de console.
//

#include "stdafx.h"

#include <my_global.h>
#include <mysql.h>

#pragma comment(lib,"libmysql.lib")

void finish_with_error(MYSQL *con)
{
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	getchar();
	exit(1);
}

int main()
{
	MYSQL *con = mysql_init(NULL);

	if (con == NULL)
	{
		fprintf(stderr, "mysql_init() failed\n");
		getchar();
		exit(1);
	}

	if (mysql_real_connect(con, "localhost", "login", "password", "database", 0, NULL, 0) == NULL)
	{
		finish_with_error(con);
	}

	if (mysql_query(con, "SELECT * FROM example_table"))
	{
		finish_with_error(con);
	}

	MYSQL_RES *result = mysql_store_result(con);

	if (result == NULL)
	{
		finish_with_error(con);
	}

	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;

	while ((row = mysql_fetch_row(result)))
	{
		for (int i = 0; i < num_fields; i++)
		{
			printf("%s ", row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}

	mysql_free_result(result);
	mysql_close(con);

	getchar();
	exit(0);

}

