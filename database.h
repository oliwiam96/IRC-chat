#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <pthread.h>
class Database
{
    private:
        sqlite3 *db;;
        std::string fileName;
        pthread_mutex_t	mutexUsers = PTHREAD_MUTEX_INITIALIZER;  // mutex for critical section (checking name availability and inserting to database)
        pthread_mutex_t	mutexRooms = PTHREAD_MUTEX_INITIALIZER;  // mutex for critical section (checking name availability and inserting to database)

    //public:
        static int callback(void *data, int argc, char **argv, char **azColName);
        static int callbackShow2(void *data, int argc, char **argv, char **azColName);
        static int callbackLoginValidation(void *data, int argc, char **argv, char **azColName);
        static int callbackGetStringWithAllRooms(void *data, int argc, char **argv, char **azColName);
        static int callbackSelectOneInt(void *data, int argc, char **argv, char **azColName);
        static int callbackGetArrayOfAllUsersConnfdInRoom(void *data, int argc, char **argv, char **azColName);
        bool loginValidation(char *name, char *password);
        void setUserActive(char *name);
        void setUserInactive(char *name);
        void setConnectionDescriptor(char *name, int connfd);
        bool userNameFreeValidation(char *name);
        bool roomNameFreeValidation(char *name);
        void addNewUser(char *name, char *password);
        void addNewRoom(char *name);
        void showDatabaseName(char *name);
        void deleteUserFromAllRooms(char *name);
        int findIdUserByName(char *name);
        int findIdRoomByName(char *name);

    public:
        Database(char* fileName);
        virtual ~Database();
        void createTables();
        void insertExampleData();
        void showDatabaseUsers();
        void showDatabaseRooms();
        void showDatabaseUsersInRooms();
        bool login(char *name, char *password, int connfd);
        void logout(char *name);
        bool createNewAccount(char *name, char *password, int connfd);
        bool createNewRoom(char *name);
        void deleteRoom(char *roomName);
        void enterRoom(char *userName, char *roomName);
        void leaveRoom(char *userName, char *roomName);
        char* getStringWithAllRooms();
        int* getArrayofAllUsersConnfdInRoom(char *roomName);
        int getNumberOfUsersInRoom(char *roomName);


};

#endif // DATABASE_H
