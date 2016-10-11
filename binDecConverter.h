#ifndef BINDECCONVERTER_H
#define BINDECCONVERTER_H
#include <string>
#include <bitset>
using namespace std;

class binDecConverter
{
public:
    binDecConverter();
    ~binDecConverter();
    const string returnStr(int& num, int bits);
    const int returnInt(string& _string);
};

#endif // BINDECCONVERTER_H
