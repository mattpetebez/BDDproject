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
#include "GroupedRule.h"

class XMLParserOut
{
public:
    XMLParserOut(Direction _direction, Accept_Deny _accept_deny);
    void setRules(vector<string>& _rules);
    void buildGroupRules();
    void orderByIPDesc();
    vector<string> ruleCreater();
    void printoutputRule();

    ~XMLParserOut();
    string BinToDec();
    
private:
    vector<string> rules;
    vector<string> xmlrules;
    vector<GroupedRule> groupedRules;
    Direction direction;
    Accept_Deny accept_deny;
};


#endif // XMLPARSEROUT_H
