#include <iostream>
#include "binDecConverter.h"

using namespace std;

int main()
{
    binDecConverter converter;
    string testRule = "00001010";
    string test116 = "0000000000001111";
    
    cout << "String to int 8 bit: " << converter.returnInt(testRule) << endl;
    cout << "String to int 16 bits: " << converter.returnInt(test116) << endl;
    
    int decimal = 255;
    
    cout << "String to binary 8 bits: " << converter.returnStr(decimal,8) << endl;
    cout << "String to binary 16 bits: " << converter.returnStr(decimal,16) << endl;
    
}