#ifndef XMLPARSERIN_H
#define XMLPARSERIN_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


#include "binDecConverter.h"
class XMLParserIn
{
public:
    XMLParserIn(string& filename);
    void buildStringRules();
    void buildBinRules();
    ~XMLParserIn();
private:
    string parseXMLtoBin(string& _wholeRule);
    string filename;
    vector<string> BinRules;
    vector<string> StringRules;
    binDecConverter _decToBin;
};

#endif // XMLPARSERIN_H
