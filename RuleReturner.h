#include <iostream>
#include "cudd.h"
#include <vector>

using namespace std;

#ifndef RULERETURNER_H
#define RULERETURNER_H

struct BDDit
{
    int compCount = 0;
    DdNode * curr;
    string rule = "";
    void setCurr(DdNode* _curr);
    void appendRule(string _rule);
    bool isPenultimateNode();
    bool hasTwoChildren();
    bool constThenChild();
    bool constElseChild();
    
    bool compIsOdd();
        
    DdNode * returnElseChild();
    DdNode * returnThenChild();
    
    string returnWholeRule();
};


bool BDDit::isPenultimateNode()
{
    if(Cudd_IsConstant(Cudd_E(curr)) && Cudd_IsConstant(Cudd_T(curr)))
    {
        return true;
    }
    
    else return false;
}

bool BDDit::hasTwoChildren()
{
    if(!Cudd_IsConstant(Cudd_E(curr)) && !Cudd_IsConstant(Cudd_T(curr)))
    {
        return true;
    }
    else return false;
}
bool BDDit::constThenChild()
{
    if (Cudd_IsConstant(Cudd_T(curr)) && !Cudd_IsConstant(Cudd_E(curr)))
    {
        return true;
    }
    else return false;
}

bool BDDit::constElseChild()
{
    if (Cudd_IsConstant(Cudd_E(curr)) && !Cudd_IsConstant(Cudd_T(curr)))
    {
        return true;
    }
    else return false;
}

bool BDDit::compIsOdd()
{
    if ((compCount%2) == 0)
    {
        return false;
    }
    else return true;
}
DdNode* BDDit::returnElseChild()
{
    return Cudd_E(curr);
}

DdNode* BDDit::returnThenChild()
{
    return Cudd_T(curr);
}

string BDDit::returnWholeRule()
{
    return rule;
}

void BDDit::appendRule(string _rule)
{
    rule += _rule;
}
class RuleReturner
{
    RuleReturner();
    ~RuleReturner();
    void findBddRules(DdNode * node);
    
    
private:
    DdNode * current;
    vector<string> rules;
};

#endif // RULERETURNER_H
