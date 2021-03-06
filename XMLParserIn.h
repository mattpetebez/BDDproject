#ifndef XMLPARSERIN_H
#define XMLPARSERIN_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "binDecConverter.h"
#include "GroupedRule.h"

#define BIT_8 8
#define BIT_16 16

using namespace std;

/*struct BinGroupedRule{
    BinGroupedRule();
 BinGroupedRule(Accept_Deny _accept_deny, int _priority, Direction _direction, string _binRule);
 int returnPriority(); 
private:
  Accept_Deny accept_deny;
  Direction direction;
  int priority;
  string binRule;
};*/

class XMLParserIn
{
public:
    XMLParserIn(string& filename);
    void buildInOutRules(vector<GroupedRule>& _inRules, vector<GroupedRule>& _outRules);
    void printRulesConsole();
        
    ~XMLParserIn();
private:
    int ips[4]={0};
    void buildStringRules();
    void buildBinRules();
    bool deleter(string& find, string& currentRule, string& rulepiece);
    void iptobin(string& ip);
    void sortBinGroupedRule();
    void sortByPriority(vector<GroupedRule>& rules);
    string filename;
    //Need these
    vector<GroupedRule> inRules;
    vector<GroupedRule> outRules;
    vector<string> StringRules;
    
    binDecConverter _decToBin;
};
//Lekker
#endif // XMLPARSERIN_H
