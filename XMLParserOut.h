#ifndef XMLPARSEROUT_H
#define XMLPARSEROUT_H
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "cudd.h"
#include "BDDBuilder.h"
#include "RuleReturner.h"
#include "binDecConverter.h"
#include "GroupedRule.h"

class XMLParserOut
{
public:
    XMLParserOut(vector<GroupedRule> _rules);
    //void setRules(vector<GroupedRule>& _rules);
   // void buildGroupRules();
    void orderByIPDesc();
    vector<string> ruleCreater();
    void printoutputRule(string& username);

    ~XMLParserOut();
    string BinToDec();
    
private:
    vector<GroupedRule> rules;
    vector<string> xmlrules;
    vector<GroupedRule> outRules;
};


#endif // XMLPARSEROUT_H
