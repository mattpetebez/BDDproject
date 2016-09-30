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
enum class Accept_Deny
{
    accept,
    deny
};

enum class Direction
{
    in,
    out
};
enum class Protocol
{
    tcp=1,
    udp,
    icmp
};
struct GroupedRule
{
    GroupedRule(int _prot,int _srcPort,int _destPort,int _ip1,int _ip2,int _ip3, int _ip4, Direction _direction, Accept_Deny _accept_deny);
    string returnProt();
    string returnSrcPort();
    string returnDestPort();
    string returnIp1();
    string returnIp2();
    string returnIp3();
    string returnIp4();
    
    string returnWholeIP();
    
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
    XMLParserOut(Direction _direction Accept_Deny _accept_deny);
    void setRules(vector<string>& _rules);
    void buildGroupRules();
    void orderByIPDesc();
    vector<string> outputRule(Direction _direction, Accept_Deny _accept_deny);
    void printoutputRule();

    ~XMLParserOut();
    string BinToDec();
    
private:
    string wholeRuleBuilder(vector<GroupedRule>::iterator _iter);
    vector<string> rules;
    vector<string> xmlrules;
    vector<GroupedRule> groupedRules;
    Direction direction;
    Accept_Deny accept_deny;
};


#endif // XMLPARSEROUT_H
