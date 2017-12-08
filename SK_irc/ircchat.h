#ifndef IRCCHAT_H
#define IRCCHAT_H
#include <map>
#include "user.h"
#include "room.h"

class IRCChat
{
public:
    IRCChat();
    void refreshUsersAndRoomsLists();

private:
    User *myAccount; // TODO add derived class with password?
    std::map < int, User > users; // user id is the key; stores list of available users
    std::map < int , Room > rooms; // room id is the key; stores list of available rooms

};

#endif // IRCCHAT_H
