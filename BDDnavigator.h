#include <vector>
#include <iostream>
#include <string>
#include "cudd.h"
#include "BDDBuilder.h"
#include "GroupedRule.h"
#include "RangeHelper.h"
#include "RuleReturner.h"
using namespace std;

#ifndef BDDNAVIGATOR_H
#define BDDNAVIGATOR_H

class BDDnavigator
{
public:
    BDDnavigator(GroupedRule, vector<GroupedRule>);
    ~BDDnavigator();

  
    vector <GroupedRule> returnExceptedRules();
private:
    void traverseTilEqual(string& _binRule, BDDit& _curr, string::iterator& _binIter);
    void initialise();
    void findBinExceptedRules();
    void reducedFoundExceptedRules();
    void buildReturnableExceptedRules();
    GroupedRule requestedRule;
    vector<GroupedRule> unExceptableRules;
    vector<GroupedRule> expandedRequestedRule;
    vector<string> binRequestedRules;
    vector<string> binExceptedRules;
    vector<GroupedRule> returnableExceptedRules;
    
    DdNode* head;
};

#endif // BDDNAVIGATOR_H
