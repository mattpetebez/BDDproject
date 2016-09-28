#ifndef XMLPARSEROUT_H
#define XMLPARSEROUT_H
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include "cudd.h"
#include "BDDBuilder.h"
#include "RuleReturner.h"
#include "binDecConverter.h"
struct GroupedRule
{
    GroupedRule(int _prot,int _srcPort,int _destPort,int _ip1,int _ip2,int _ip3, int _ip4);
    string returnProt();
    string returnSrcPort();
    string returnDestPort();
    string returnIp1();
    string returnIp2();
    string returnIp3();
    string returnIp4();
    
    int prot;
    int srcPort;
    int destPort;
    int ip1;
    int ip2;
    int ip3;
    int ip4;    
    
};
class XMLParserOut
{
public:
    XMLParserOut();
    void setRules(vector<string>& _rules);
    void buildGroupRules();
    void orderByIPDesc();
    vector<string> outputRule();
    void printoutputRule();
    ~XMLParserOut();
    string BinToDec();
    
private:
    vector<string> rules;
    vector<string> xmlrules;
    vector<GroupedRule> groupedRules;

};


#endif // XMLPARSEROUT_H
