#include "binDecConverter.h"

binDecConverter::binDecConverter()
{
}

binDecConverter::~binDecConverter()
{
}

int binDecConverter::returnInt(string& num)
{
    ulong decimal;
    if(num.size()==8)
    decimal = (std::bitset<8>(num).to_ulong());
    else
    decimal = (std::bitset<16>(num).to_ulong());    
    
    return (int)decimal;
}

string binDecConverter::returnStr(int& decimal, int bits)
{
    string binary="";
    if(bits == 8)
    binary = std::bitset<8>(decimal).to_string();
    else
    binary = std::bitset<16>(decimal).to_string();    
    

    return binary;
}
