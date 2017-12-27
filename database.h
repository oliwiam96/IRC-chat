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
        pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;  // mutex for critical section (checking name availability and inserting to database)

    public:
        void setUp();
        static int callback(void *data, int argc, char **argv, char **azColName);
        static int callbackShow2(void *data, int argc, char **argv, char **azColName);
        static int callbackLoginValidation(void *data, int argc, char **argv, char **azColName);
        bool loginValidation(char *name, char *password);
        void setUserActive(char *name);
        void setUserInctive(char *name);
        static int callbackNameFreeValidation(void *data, int argc, char **argv, char **azColName);
        bool nameFreeValidation(char *name);
        void addNewUser(char *name, char *password);

    //public:
        Database(char* fileName);
        virtual ~Database();
        void showDatabase();
        void showDatabase2();
        bool login(char *name, char *password);
        bool createNewAccount(char *name, char *password);

};

#endif // DATABASE_H
