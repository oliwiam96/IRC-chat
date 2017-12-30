#ifndef HASHCOLOUR_H
#define HASHCOLOUR_H
#include <QString>
#include <string>

class HashColour
{
public:
    HashColour();
    std::string hashColour(QString str);
private:
    int hashcode(QString str);
    std::string colour(int hashcode);
};

#endif // HASHCOLOUR_H
