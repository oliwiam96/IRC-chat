#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <pthread.h>

using namespace std;

Database::Database(char* fileName)
{
    int rc;
    /* Open database */
    rc = sqlite3_open(fileName, &db);
    if(rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
    else
    {
        fprintf(stdout, "Opened database successfully\n");
    }
}

Database::~Database()
{
    sqlite3_close(db);
    pthread_mutex_destroy(&mutex);
}

void Database::setUp()
{
    char *zErrMsg = 0;
    /* Create SQL statement */
    char sql_create[] = "CREATE TABLE USERS("  \
                    "ID INTEGER PRIMARY KEY NOT NULL," \
                    "NAME	TEXT NOT NULL," \
                    "PASSWORD TEXT NOT NULL," \
                    "ACTIVE INT NOT NULL );";

    /* Execute SQL statement */
    int rc = sqlite3_exec(db, sql_create, callback, 0, &zErrMsg);

    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else
    {
        fprintf(stdout, "Table created successfully\n");
    }

    char *zErrMsg2 = 0;
    char sql_insert[] = "INSERT INTO USERS (NAME, PASSWORD, ACTIVE) "  \
                    "VALUES ('oli', 'oli123', 0 );" \
             "INSERT INTO USERS (NAME, PASSWORD, ACTIVE) "  \
                    "VALUES ('kuba', 'kuba123', 0 );" \
             "INSERT INTO USERS (NAME, PASSWORD, ACTIVE) "  \
                    "VALUES ('admin', 'admin', 0 );";

    /* Execute SQL statement */
    int rc2 = sqlite3_exec(db, sql_insert, callback, 0, &zErrMsg2);
    if( rc2 != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg2);
        sqlite3_free(zErrMsg2);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }
}
int Database::callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for(i = 0; i<argc; i++)
    {
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}
int Database::callbackShow2(void *data, int argc, char **argv, char **azColName)
{
    int i;
    char *a = (char*) data;
    if(!strcmp(a, "pierwszy"))
    {
        for(i = 0; i<argc; i++)
        {
                printf("%s\t", azColName[i]);
        }
        strcpy(a, "drugi");
        printf("\n");
    }
    for(i = 0; i<argc; i++){
            printf("%s\t", argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}
int Database::callbackLoginValidation(void *data, int argc, char **argv, char **azColName)
{
    char *a = (char*) data;
    strcpy(a, argv[0]);
    return 0;
}

bool Database::loginValidation(char *name, char *password)
{
    char *zErrMsg = 0;
    char sql_select[80];
    strcpy(sql_select, "SELECT PASSWORD from USERS WHERE NAME = \"");
    strcat(sql_select, name);
    strcat(sql_select, "\";");
    char *password_select = (char *) malloc(50* sizeof(char));
    printf("%s\n", sql_select);
    int rc = sqlite3_exec(db, sql_select, callbackLoginValidation, (void*)password_select, &zErrMsg);
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

void Database::setUserActive(char *name)
{
    char *zErrMsg = 0;
    char sql_update[80];
    strcpy(sql_update, "UPDATE USERS SET ACTIVE = 1 WHERE NAME = \"");
    strcat(sql_update, name);
    strcat(sql_update, "\";");
    printf("%s\n", sql_update);
    int rc = sqlite3_exec(db, sql_update, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else
    {
        fprintf(stdout, "Operation \"set user active\" done successfully\n");
    }

}

void Database::setUserInctive(char *name)
{
    char *zErrMsg = 0;
    char sql_update[80];
    strcpy(sql_update, "UPDATE USERS SET ACTIVE = 0 WHERE NAME = \"");
    strcat(sql_update, name);
    strcat(sql_update, "\";");
    printf("%s\n", sql_update);
    int rc = sqlite3_exec(db, sql_update, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else
    {
        fprintf(stdout, "Operation \"set user inactive\" done successfully\n");
    }

}

int Database::callbackNameFreeValidation(void *data, int argc, char **argv, char **azColName)
{
    int *a = (int*) data;
    *a = atoi(argv[0]);
    return 0;
}

bool Database::nameFreeValidation(char *name)
{
    char *zErrMsg = 0;
    char sql_select[80];
    strcpy(sql_select, "SELECT COUNT(*) from USERS WHERE NAME = \"");
    strcat(sql_select, name);
    strcat(sql_select, "\";");
    int ile;
    printf("%s\n", sql_select);
    int rc = sqlite3_exec(db, sql_select, callbackNameFreeValidation, (void*)&ile, &zErrMsg);
    if( rc != SQLITE_OK )
    {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
    } else
    {
            fprintf(stdout, "Operation \"name free/taken\" done successfully\n");
    }
    printf("Ile wynosi: %d\n", ile);
    return ile == 0;
}

void Database::addNewUser(char *name, char *password)
{
    char *zErrMsg = 0;
    char sql_insert[80];
    strcpy(sql_insert, "INSERT INTO USERS(NAME, PASSWORD, ACTIVE) VALUES (\"");
    strcat(sql_insert, name);
    strcat(sql_insert, "\", \"");
    strcat(sql_insert, password);
    strcat(sql_insert, "\", 0);");
    printf("%s\n", sql_insert);
    int rc = sqlite3_exec(db, sql_insert, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK )
    {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
    } else
    {
            fprintf(stdout, "Operation \"add new user\" done successfully\n");
    }
}

void Database::showDatabase()
{
    char *zErrMsg = 0;
    const char* data = "Kolejny rekord z relacji USERS";
    /* Create SQL statement */
    char sql_select[] = "SELECT * from USERS";

    /* Execute SQL statement */
    int rc = sqlite3_exec(db, sql_select, callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else
    {
        fprintf(stdout, "Operation done successfully\n");
    }
}
void Database::showDatabase2()
{
    char *zErrMsg = 0;
    char data[] = "pierwszy";
    /* Create SQL statement */
    char sql_select[] = "SELECT * from USERS";

    /* Execute SQL statement */
    int rc = sqlite3_exec(db, sql_select, callbackShow2, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else
    {
        fprintf(stdout, "Operation done successfully\n");
    }
}

bool Database::login(char *name, char *password)
{
    if(loginValidation(name, password))
    {
        setUserActive(name);
        return true;
    }
    else
    {
        return false;
    }
}

bool Database::createNewAccount(char *name, char *password)
{
    // mutex P
    pthread_mutex_lock(&mutex);
    if(nameFreeValidation(name))
    {
        addNewUser(name, password);
        setUserActive(name);
        // mutex V
        pthread_mutex_unlock(&mutex);
        return true;
    }
    else
    {
        // mutex V
        pthread_mutex_unlock(&mutex);
        return false;
    }

}


int main(int argc, char* argv[]) {
    char fileName[] = "test.db";
    Database *db = new Database(fileName);
    db->setUp();

    char name3[] = "zenek";
    char password3[] = "maslo";
    db->addNewUser(name3, password3);
    char name[] = "oli";
    char password[] = "oli123";
    if(db->loginValidation(name, password))
            printf("Haslo ok\n");
    else
            printf("Haslo zle\n");
    char name2[] = "oliwka";
    if(db->nameFreeValidation(name2))
        printf("Login wolny\n");
    else
        printf("Login zajety\n");
    db->setUserActive(name);
    char i[] = "hejka";
    db->createNewAccount(i, i);
    char j[] = "siemka";
    db->createNewAccount(j, j);

    db->showDatabase();
    db->showDatabase2();


    delete db;
    return 0;
}


