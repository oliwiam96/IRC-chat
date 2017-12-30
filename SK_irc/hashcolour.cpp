#include "hashcolour.h"

using namespace std;

HashColour::HashColour()
{

}

int HashColour::hashcode(QString str)
{
    str = str.toLower();
    printf("%s\n",str.toLatin1().data());
    int hash = 0;
    for (int i = 0; i < str.size(); i++) {
        char *str2 = str.toLatin1().data();
        char sign = str2[i];
           hash = ((int) sign - 'a') + ((hash << 5) - hash);
        }
   return hash;
}

string HashColour::colour(int hash)
{
    string colour = "#";
    for (int i = 0; i < 3; i++) {
        int value = (hash >> (i * 8)) & 0xFF;
        char hex[20];
        sprintf(hex, "%X", value);
        if(value < 16)
            hex[1] = '0';

        colour += (char) hex[strlen(hex) -1 ];
        colour += (char) hex[strlen(hex) -2 ];
      }
      return colour;
}
string HashColour::hashColour(QString str)
{
    return colour(hashcode(str));
}
