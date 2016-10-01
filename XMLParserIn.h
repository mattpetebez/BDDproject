#ifndef XMLPARSERIN_H
#define XMLPARSERIN_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "binDecConverter.h"
#include "GroupedRule.h"

using namespace std;

struct BinGroupedRule{
  BinGroupedRule(Accept_Deny _accept_deny, int _priority, Direction _direction, string _binRule);
  
private:
  Accept_Deny accept_deny;
  Direction direction;
  int priority;
  string binRule;
};

class XMLParserIn
{
public:
    XMLParserIn(string& filename);
    void buildStringRules();
    void buildBinRules();
    bool deleter(string& find, string& currentRule, string& rulepiece);
    void iptobin(string& ip);
    ~XMLParserIn();
private:
    string parseXMLtoBin(string& _wholeRule);
    string filename;
    vector <BinGroupedRule> parsedRules;
    vector<string> BinRules;
    vector<string> StringRules;
    binDecConverter _decToBin;
};

#endif // XMLPARSERIN_H
