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
#include "RangeHelper.h"

class XMLParserOut
{
public:
    XMLParserOut();
    ~XMLParserOut();

    void parseOutGroupedRules(vector<GroupedRule> _rules, string& username);
private:
    void sortIP(Field field, vector<GroupedRule>& unsorted);
    void sortAscendingIP();
    void printoutputRule(string& username);
    void expandRangedRules();
    void ruleCreater();
    vector<GroupedRule> rules;
    vector<string> xmlrules;
    vector<GroupedRule> outRules;
};


#endif // XMLPARSEROUT_H
