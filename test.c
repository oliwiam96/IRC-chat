#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string.h>

static int callback(void *data, int argc, char **argv, char **azColName){
	int i;
	fprintf(stderr, "%s: ", (const char*)data);
	
	for(i = 0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	
	printf("\n");
	return 0;
}
static int callback_login_validation(void *data, int argc, char **argv, char **azColName){
	char *a = (char*) data;
	strcpy(a, argv[0]);
	return 0;
}
bool login_validation(sqlite3 *db, char *zErrMsg, int rc, char *name, char *password)
{
	char sql_select[80];
	strcpy(sql_select, "SELECT PASSWORD from USERS WHERE NAME = \"");
	strcat(sql_select, name);
	strcat(sql_select, "\";");
	char *password_select = (char *) malloc(50* sizeof(char));
	printf("%s\n", sql_select);
	rc = sqlite3_exec(db, sql_select, callback_login_validation, (void*)password_select, &zErrMsg);
	if( rc != SQLITE_OK ) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Operation \"password checking\" done successfully\n");
	}
	password_select = (char*) password_select;
	bool identical = !strcmp(password_select, password);
	free(password_select);
	return identical;
}
static int callback_name_free_validation(void *data, int argc, char **argv, char **azColName){
	int *a = (int*) data;
	*a = atoi(argv[0]);
	return 0;
}
bool name_free_validation(sqlite3 *db, char *zErrMsg, int rc, char *name)
{
	char sql_select[80];
	strcpy(sql_select, "SELECT COUNT(*) from USERS WHERE NAME = \"");
	strcat(sql_select, name);
	strcat(sql_select, "\";");
	int ile;
	printf("%s\n", sql_select);
	rc = sqlite3_exec(db, sql_select, callback_name_free_validation, (void*)&ile, &zErrMsg);
	if( rc != SQLITE_OK ) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Operation \"name free/taken\" done successfully\n");
	}
	printf("Ile wynosi: %d\n", ile);
	return ile == 0;
}

void add_new_user(sqlite3 *db, char *zErrMsg, int rc, char *name, char *password)
{
	char sql_insert[80];
	strcpy(sql_insert, "INSERT INTO USERS(NAME, PASSWORD, ACTIVE) VALUES (\"");
	strcat(sql_insert, name);
	strcat(sql_insert, "\", \"");
	strcat(sql_insert, password);
	strcat(sql_insert, "\", 1);");
	printf("%s\n", sql_insert);
	rc = sqlite3_exec(db, sql_insert, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Operation \"add new user\" done successfully\n");
	}
}

int main(int argc, char* argv[]) {
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	//char *sql;

	/* Open database */
	rc = sqlite3_open("test.db", &db);
	
	if( rc ) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	} else {
		fprintf(stdout, "Opened database successfully\n");
	}

	/* Create SQL statement */
	char sql_create[] = "CREATE TABLE USERS("  \
			"ID INTEGER PRIMARY KEY NOT NULL," \
			"NAME	TEXT NOT NULL," \
			"PASSWORD TEXT NOT NULL," \
			"ACTIVE INT NOT NULL );";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql_create, callback, 0, &zErrMsg);
	
	if( rc != SQLITE_OK ){
	fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Table created successfully\n");
	}


	/* Create SQL statement */
	char sql_insert[] = "INSERT INTO USERS (NAME, PASSWORD, ACTIVE) "  \
			"VALUES ('oli', 'oli123', 0 );" \
		 "INSERT INTO USERS (NAME, PASSWORD, ACTIVE) "  \
			"VALUES ('kuba', 'kuba123', 0 );" \
		 "INSERT INTO USERS (NAME, PASSWORD, ACTIVE) "  \
			"VALUES ('admin', 'admin', 0 );";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql_insert, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Records created successfully\n");
	}
	char name3[] = "zenek";
	char password3[] = "maslo";
	add_new_user(db, zErrMsg, rc, name3, password3);
	const char* data = "Callback function called";
	/* Create SQL statement */
	char sql_select[] = "SELECT * from USERS";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql_select, callback, (void*)data, &zErrMsg);
	
	if( rc != SQLITE_OK ) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Operation done successfully\n");
	}
	char name[] = "oli";
	char password[] = "oli123";
	if(login_validation(db, zErrMsg, rc, name, password))
		printf("Haslo ok\n");
	else
		printf("Haslo zle\n");
	char name2[] = "oliwka";
	if(name_free_validation(db, zErrMsg, rc, name2))
		printf("Login wolny\n");
	else
		printf("Login zajety\n");
	sqlite3_close(db);
	return 0;
}
