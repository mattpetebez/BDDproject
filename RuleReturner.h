#include <iostream>
#include "GroupedRule.h"
#include "cudd.h"
#include <vector>

using namespace std;

#ifndef RULERETURNER_H
#define RULERETURNER_H

#define NO_BITS_IN_RULE 72

struct BDDit
{
    BDDit();
    int compCount = 0;
    DdNode * curr;
    string rule;
    void setCurr(DdNode* _curr);
    void appendRule(char _rule);
    bool isPenultimateNode();
    bool hasTwoChildren();
    bool constThenChild();
    bool constElseChild();
    
    bool compIsOdd();
    
    BDDit &operator=(const BDDit &aBDDit);
    DdNode * returnElseChild();
    DdNode * returnThenChild();
    
    const string returnWholeRule();
};

class RuleReturner
{
public:
    RuleReturner(DdNode* head, Direction _direction);
    ~RuleReturner();
    void startRuleReturn();
    void findBddRules(BDDit tracker);
    bool validNoRules();
    vector<GroupedRule> returnRules();
private:
    DdNode * current;
    vector<GroupedRule> rules;
    BDDit iter;
    Direction direction;
    
};

#endif // RULERETURNER_H
