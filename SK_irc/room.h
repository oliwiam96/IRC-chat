#ifndef ROOM_H
#define ROOM_H
#include<string>
#include "user.h"

class Room
{
public:
    Room();
private:
    int id;
    std::string name;
    User *admin;
};

#endif // ROOM_H
