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
        //fprintf(stdout, "Opened database successfully\n");
    }
    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", 0, 0, 0); //wlaczenie ograniczen dla kluczow obcych
}

Database::~Database()
{
    sqlite3_close(db);
    pthread_mutex_destroy(&mutexUsers);
    pthread_mutex_destroy(&mutexRooms);
}

void Database::createTables()
{
    char *zErrMsg = 0;
    /* Create SQL statement */
    char sql_create_users[] = "CREATE TABLE USERS("  \
                    "ID INTEGER PRIMARY KEY NOT NULL," \
                    "NAME TEXT NOT NULL UNIQUE," \
                    "PASSWORD TEXT NOT NULL," \
                    "CONNFD INT NOT NULL," \
                    "ACTIVE INT NOT NULL );";

    /* Execute SQL statement */
    int rc = sqlite3_exec(db, sql_create_users, callback, 0, &zErrMsg);

    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else
    {
        //fprintf(stdout, "Table Users created successfully\n");
    }


    char *zErrMsg3= 0;
    char sql_create_rooms[] = "CREATE TABLE ROOMS("  \
                    "ID INTEGER PRIMARY KEY NOT NULL," \
                    "NAME TEXT NOT NULL UNIQUE);";


    /* Execute SQL statement */
    int rc3 = sqlite3_exec(db, sql_create_rooms, callback, 0, &zErrMsg3);

    if( rc3 != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg3);
        sqlite3_free(zErrMsg3);
    } else
    {
        //fprintf(stdout, "Table Rooms created successfully\n");
    }

    char *zErrMsg4= 0;
    char sql_create_usersinrooms[] = "CREATE TABLE USERSINROOMS("  \
                    "IDUSER INTEGER NOT NULL REFERENCES USERS(ID)," \
                    "IDROOM INTEGER NOT NULL REFERENCES ROOMS(ID) ON DELETE CASCADE);";



    /* Execute SQL statement */
    int rc4 = sqlite3_exec(db, sql_create_usersinrooms, callback, 0, &zErrMsg4);

    if( rc4 != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg4);
        sqlite3_free(zErrMsg4);
    } else
    {
        //fprintf(stdout, "Table UsersInRooms created successfully\n");
    }


}
void Database::insertExampleData()
{
    char *zErrMsg2 = 0;
    char sql_insert_users[] = "INSERT INTO USERS (NAME, PASSWORD, CONNFD, ACTIVE) "  \
                    "VALUES ('oli', 'oli123', 3, 0 );" \
             "INSERT INTO USERS (NAME, PASSWORD, CONNFD, ACTIVE) "  \
                    "VALUES ('kuba', 'kuba123', 4, 0 );" \
             "INSERT INTO USERS (NAME, PASSWORD, CONNFD, ACTIVE) "  \
                    "VALUES ('admin', 'admin', 5, 0 );";

    /* Execute SQL statement */
    int rc2 = sqlite3_exec(db, sql_insert_users, callback, 0, &zErrMsg2);
    if( rc2 != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg2);
        sqlite3_free(zErrMsg2);
    } else {
        //fprintf(stdout, "Records in Users created successfully\n");
    }

    char *zErrMsg5 = 0;
    char sql_insert_rooms[] = "INSERT INTO ROOMS (NAME) "  \
                    "VALUES ('informatycy');" \
                    "INSERT INTO ROOMS (NAME) "  \
                    "VALUES ('faniSW');";

    /* Execute SQL statement */
    int rc5 = sqlite3_exec(db, sql_insert_rooms, callback, 0, &zErrMsg5);
    if( rc5 != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg5);
        sqlite3_free(zErrMsg5);
    } else {
        //fprintf(stdout, "Records in Rooms created successfully\n");
    }

    char *zErrMsg6 = 0;
    char sql_insert_usersinrooms[] = "INSERT INTO USERSINROOMS (IDUSER, IDROOM) "  \
                    "VALUES (1, 1);" \
                    "INSERT INTO USERSINROOMS (IDUSER, IDROOM) "  \
                    "VALUES (2, 1);";

    /* Execute SQL statement */
    int rc6 = sqlite3_exec(db, sql_insert_usersinrooms, callback, 0, &zErrMsg6);
    if( rc6 != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg6);
        sqlite3_free(zErrMsg6);
    } else {
        //fprintf(stdout, "Records in UsersInRooms created successfully\n");
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
    int rc = sqlite3_exec(db, sql_select, callbackLoginValidation, (void*)password_select, &zErrMsg);
    if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
    } else {
            //fprintf(stdout, "Operation \"password checking\" done successfully\n");
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
    int rc = sqlite3_exec(db, sql_update, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else
    {
        //fprintf(stdout, "Operation \"set user active\" done successfully\n");
    }

}

void Database::setUserInactive(char *name)
{
    char *zErrMsg = 0;
    char sql_update[80];
    strcpy(sql_update, "UPDATE USERS SET ACTIVE = 0 WHERE NAME = \"");
    strcat(sql_update, name);
    strcat(sql_update, "\";");
    int rc = sqlite3_exec(db, sql_update, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else
    {
        //fprintf(stdout, "Operation \"set user inactive\" done successfully\n");
    }

}
void Database::setConnectionDescriptor(char *name, int connfd)
{
    char *zErrMsg = 0;
    char sql_update[80];
    strcpy(sql_update, "UPDATE USERS SET CONNFD = ");
    char buffer[20];
    sprintf(buffer, "%d", connfd);
    strcat(sql_update, buffer);
    strcat(sql_update, " WHERE NAME = \"");
    strcat(sql_update, name);
    strcat(sql_update, "\";");
    int rc = sqlite3_exec(db, sql_update, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else
    {
        //fprintf(stdout, "Operation \"set connection descriptor \" done successfully\n");
    }

}

int Database::callbackSelectOneInt(void *data, int argc, char **argv, char **azColName)
{
    int *a = (int*) data;
    *a = atoi(argv[0]);
    return 0;
}

bool Database::userNameFreeValidation(char *name)
{
    char *zErrMsg = 0;
    char sql_select[80];
    strcpy(sql_select, "SELECT COUNT(*) from USERS WHERE NAME = \"");
    strcat(sql_select, name);
    strcat(sql_select, "\";");
    int ile;
    int rc = sqlite3_exec(db, sql_select, callbackSelectOneInt, (void*)&ile, &zErrMsg);
    if( rc != SQLITE_OK )
    {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
    } else
    {
            //fprintf(stdout, "Operation \"name free/taken\" done successfully\n");
    }
    return ile == 0;
}

void Database::addNewUser(char *name, char *password)
{
    char *zErrMsg = 0;
    char sql_insert[80];
    strcpy(sql_insert, "INSERT INTO USERS(NAME, PASSWORD, CONNFD, ACTIVE) VALUES (\"");
    strcat(sql_insert, name);
    strcat(sql_insert, "\", \"");
    strcat(sql_insert, password);
    strcat(sql_insert, "\", 0, 0);");
    int rc = sqlite3_exec(db, sql_insert, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK )
    {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
    } else
    {
            //fprintf(stdout, "Operation \"add new user\" done successfully\n");
    }
}

bool Database::roomNameFreeValidation(char *name)
{
    char *zErrMsg = 0;
    char sql_select[80];
    strcpy(sql_select, "SELECT COUNT(*) from ROOMS WHERE NAME = \"");
    strcat(sql_select, name);
    strcat(sql_select, "\";");
    int ile;
    int rc = sqlite3_exec(db, sql_select, callbackSelectOneInt, (void*)&ile, &zErrMsg);
    if( rc != SQLITE_OK )
    {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
    } else
    {
            //fprintf(stdout, "Operation \"name free/taken\" done successfully\n");
    }
    return ile == 0;
}

void Database::addNewRoom(char *name)
{
    char *zErrMsg = 0;
    char sql_insert[80];
    strcpy(sql_insert, "INSERT INTO ROOMS(NAME) VALUES (\"");
    strcat(sql_insert, name);
    strcat(sql_insert, "\");");
    int rc = sqlite3_exec(db, sql_insert, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK )
    {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
    } else
    {
            //fprintf(stdout, "Operation \"add new room\" done successfully\n");
    }
}


int Database::findIdUserByName(char *name)
{
    char *zErrMsg = 0;
    char sql_select[80];
    strcpy(sql_select, "SELECT ID from USERS WHERE NAME = \"");
    strcat(sql_select, name);
    strcat(sql_select, "\";");
    int id_select;
    int rc = sqlite3_exec(db, sql_select, callbackSelectOneInt, (void*)&id_select, &zErrMsg);
    if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
    } else {
            //fprintf(stdout, "Operation \"find id by name \" done successfully\n");
    }
    return id_select;
}

void Database::deleteUserFromAllRooms(char *name)
{
    int idUser = findIdUserByName(name);

    char *zErrMsg = 0;
    char sql_delete[80];
    strcpy(sql_delete, "DELETE FROM USERSINROOMS WHERE IDUSER = ");
    char buffer[20];
    sprintf(buffer, "%d", idUser);
    strcat(sql_delete, buffer);
    strcat(sql_delete, ";");
    int rc = sqlite3_exec(db, sql_delete, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
    } else {
            //fprintf(stdout, "Operation \"delete user from UsersInRooms\" done successfully\n");
    }
}


void Database::logout(char *name)
{
    setUserInactive(name);
    deleteUserFromAllRooms(name);
}

void Database::leaveRoom(char *userName, char *roomName)
{
    int idUser = findIdUserByName(userName);
    int idRoom = findIdRoomByName(roomName);
    char bufferUser[10];
    char bufferRoom[10];
    sprintf(bufferUser, "%d", idUser);
    sprintf(bufferRoom, "%d", idRoom);

    char *zErrMsg = 0;
    char sql_delete_usersinrooms[100];
    strcpy(sql_delete_usersinrooms, "DELETE FROM USERSINROOMS WHERE IDUSER = ");
    strcat(sql_delete_usersinrooms, bufferUser);
    strcat(sql_delete_usersinrooms, " AND IDROOM = ");
    strcat(sql_delete_usersinrooms, bufferRoom);
    strcat(sql_delete_usersinrooms, ";");

    /* Execute SQL statement */
    int rc = sqlite3_exec(db, sql_delete_usersinrooms, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        //fprintf(stdout, "Record in UsersInRooms deleted successfully\n");
    }

}

int Database::findIdRoomByName(char *name)
{
    char *zErrMsg = 0;
    char sql_select[80];
    strcpy(sql_select, "SELECT ID from ROOMS WHERE NAME = \"");
    strcat(sql_select, name);
    strcat(sql_select, "\";");
    int id_select;
    int rc = sqlite3_exec(db, sql_select, callbackSelectOneInt, (void*)&id_select, &zErrMsg);
    if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
    } else {
            //fprintf(stdout, "Operation \"find id by name \" done successfully\n");
    }
    return id_select;
}

void Database::enterRoom(char *userName, char *roomName)
{
    int idUser = findIdUserByName(userName);
    int idRoom = findIdRoomByName(roomName);
    char bufferUser[10];
    char bufferRoom[10];
    sprintf(bufferUser, "%d", idUser);
    sprintf(bufferRoom, "%d", idRoom);

    char *zErrMsg = 0;
    char sql_insert_usersinrooms[100];
    strcpy(sql_insert_usersinrooms, "INSERT INTO USERSINROOMS (IDUSER, IDROOM) VALUES (");
    strcat(sql_insert_usersinrooms, bufferUser);
    strcat(sql_insert_usersinrooms, ", ");
    strcat(sql_insert_usersinrooms, bufferRoom);
    strcat(sql_insert_usersinrooms, ");");


    /* Execute SQL statement */
    int rc = sqlite3_exec(db, sql_insert_usersinrooms, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        //fprintf(stdout, "Records in UsersInRooms created successfully\n");
    }

}

void Database::showDatabaseName(char *databaseName)
{
    printf("--- %s ---\n", databaseName);
    char *zErrMsg = 0;
    char data[] = "pierwszy";
    /* Create SQL statement */
    char sql_select[80];
    strcpy(sql_select, "SELECT * from ");
    strcat(sql_select, databaseName);
    strcat(sql_select, ";");

    /* Execute SQL statement */
    int rc = sqlite3_exec(db, sql_select, callbackShow2, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else
    {
        //fprintf(stdout, "Operation \" select * from ... \" done successfully\n");
    }
    printf("\n");
}

void Database::showDatabaseUsers()
{
    char users[] = "USERS";
    showDatabaseName(users);
}

void Database::showDatabaseRooms()
{
    char rooms[] = "ROOMS";
    showDatabaseName(rooms);
}

void Database::showDatabaseUsersInRooms()
{
    char usersinrooms[] = "USERSINROOMS";
    showDatabaseName(usersinrooms);
}
bool Database::login(char *name, char *password, int connfd)
{
    if(loginValidation(name, password))
    {
        setConnectionDescriptor(name, connfd);
        setUserActive(name);
        return true;
    }
    else
    {
        return false;
    }
}

bool Database::createNewAccount(char *name, char *password, int connfd)
{
    // mutex P
    pthread_mutex_lock(&mutexUsers);
    if(userNameFreeValidation(name))
    {
        addNewUser(name, password);
        setConnectionDescriptor(name, connfd);
        setUserActive(name);
        // mutex V
        pthread_mutex_unlock(&mutexUsers);
        return true;
    }
    else
    {
        // mutex V
        pthread_mutex_unlock(&mutexUsers);
        return false;
    }

}

bool Database::createNewRoom(char *name)
{
    // mutex P
    pthread_mutex_lock(&mutexRooms);
    if(roomNameFreeValidation(name))
    {
        addNewRoom(name);
        // mutex V
        pthread_mutex_unlock(&mutexRooms);
        return true;
    }
    else
    {
        // mutex V
        pthread_mutex_unlock(&mutexRooms);
        return false;
    }

}

void Database::deleteRoom(char *name)
{

    int idRoom = findIdRoomByName(name);

    char *zErrMsg = 0;
    char sql_delete[80];
    strcpy(sql_delete, "DELETE FROM ROOMS WHERE ID = ");
    char buffer[20];
    sprintf(buffer, "%d", idRoom);
    strcat(sql_delete, buffer);
    strcat(sql_delete, ";");
    int rc = sqlite3_exec(db, sql_delete, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
    } else {
            //fprintf(stdout, "Operation \"delete room\" done successfully\n");
    }
}

int Database::callbackGetStringWithAllRooms(void *data, int argc, char **argv, char **azColName)
{
    char *a = (char*) data;
    strcat(a, argv[0]);
    strcat(a, " ");
    return 0;
}


char* Database::getStringWithAllRooms()
{
    char *zErrMsg = 0;
    char sql_select[] = "SELECT NAME FROM ROOMS;";
    char *data = (char *) malloc(500* sizeof(char));; //MAKS 500 dlugosc lancucha z nazwami pokojow
    strcpy(data, "");

    int rc = sqlite3_exec(db, sql_select, callbackGetStringWithAllRooms, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
    } else {
            //fprintf(stdout, "Operation \"get string with all rooms\" done successfully\n");
    }
    data[strlen(data) - 1] = '\0'; //delete last space
    return data;
}

int Database::getNumberOfUsersInRoom(char *roomName)
{

    int idRoom = findIdRoomByName(roomName);
    char bufferRoom[10];
    sprintf(bufferRoom, "%d", idRoom);

    char *zErrMsg = 0;
    char sql_select[80];
    strcpy(sql_select, "SELECT COUNT(*) from USERSINROOMS WHERE IDROOM = ");
    strcat(sql_select, bufferRoom);
    strcat(sql_select, ";");
    int ile;
    int rc = sqlite3_exec(db, sql_select, callbackSelectOneInt, (void*)&ile, &zErrMsg);
    if( rc != SQLITE_OK )
    {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
    } else
    {
            //fprintf(stdout, "Operation \"name get number of users in a room\" done successfully\n");
    }
    return ile;
}

int Database::callbackGetArrayOfAllUsersConnfdInRoom(void *data, int argc, char **argv, char **azColName)
{
    int *a = (int*) data;
    int index = 0;
    while(a[index] != -1)
    {
        index++;
    }
    a[index] = atoi(argv[0]);
    return 0;
}

int *Database::getArrayofAllUsersConnfdInRoom(char *roomName)
{
    int n = getNumberOfUsersInRoom(roomName);
    int *array = (int *) malloc(n* sizeof(int));
    for(int i = 0; i < n; i++)
    {
        array[i] = -1;
    }

    int idRoom = findIdRoomByName(roomName);
    char bufferRoom[10];
    sprintf(bufferRoom, "%d", idRoom);

    char *zErrMsg = 0;
    char sql_select[200];
    strcpy(sql_select, "SELECT USERS.CONNFD from USERS INNER JOIN USERSINROOMS ON USERS.ID = USERSINROOMS.IDUSER " \
                       "WHERE USERSINROOMS.IDROOM = ");
    strcat(sql_select, bufferRoom);
    strcat(sql_select, ";");
    int rc = sqlite3_exec(db, sql_select, callbackGetArrayOfAllUsersConnfdInRoom, (void*)array, &zErrMsg);
    if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
    } else {
            //fprintf(stdout, "Operation \"get array of all users' connfd in a room\" done successfully\n");
    }
    array = (int*) array;

    return array;
}



///* main tylko dla testowania klasy
int main(int argc, char* argv[]) {
    char fileName[] = "test.db";
    Database *db = new Database(fileName);
    db->createTables();
    db->insertExampleData();

    char name[100];
    char name2[100];
    char password[100];

    strcpy(name, "ala");
    strcpy(password, "hasloali");
    db->createNewAccount(name, password, 123);

    strcpy(name, "ola");
    strcpy(password, "hasloOli");
    db->createNewAccount(name, password, 124);
    db->logout(name);

    strcpy(name, "misio");
    strcpy(password, "tajne");
    db->createNewAccount(name, password, 125);

    strcpy(name, "anonki");
    db->createNewRoom(name);

    strcpy(name, "faniGothica");
    db->createNewRoom(name);

    strcpy(name2, "ala");
    db->enterRoom(name2, name);

    db->showDatabaseUsers();
    db->showDatabaseRooms();
    db->showDatabaseUsersInRooms();

    strcpy(name, "informatycy");
    db->deleteRoom(name);

    strcpy(name2, "ala");
    db->logout(name2);


    db->showDatabaseUsers();
    db->showDatabaseRooms();
    db->showDatabaseUsersInRooms();

    strcpy(name, "ola");
    strcpy(name2, "faniGothica");
    db->enterRoom(name, name2);
    strcpy(name2, "anonki");
    db->enterRoom(name, name2);
    db->showDatabaseUsersInRooms();
    db->leaveRoom(name, name2);
    db->showDatabaseUsersInRooms();



    strcpy(name, "misio");
    db->enterRoom(name, name2);
    strcpy(name, "ala");
    db->enterRoom(name, name2);
    printf("\nAll rooms: %s\n", db->getStringWithAllRooms());

    int *tab = db->getArrayofAllUsersConnfdInRoom(name2);
    for(int i = 0; i < db->getNumberOfUsersInRoom(name2); i++)
        if(tab[i] != -1)
            printf("Connfd: %d\n", tab[i]);


    delete db;
    return 0;
}

//*/

