#include "RuleReturner.h"

RuleReturner::RuleReturner(DdNode* head)
{
    iter.setCurr(head);
//    cout << Cudd_NodeReadIndex(head) << endl;
    current = head;
}

RuleReturner::~RuleReturner()
{
    
}
vector <string> RuleReturner::returnRules()
{
    return rules;
}

void RuleReturner::startRuleReturn()
{
    this->findBddRules(iter);
}
void RuleReturner::findBddRules(BDDit tracker)
{
    
    char one = '1';
    char zero = '0';
    
    if(tracker.isPenultimateNode())
    {
		
        if(tracker.compIsOdd())
        {
            tracker.appendRule(zero);
        }
        
<<<<<<< Updated upstream
        else 
        {
            tracker.appendRule(one);
        }
        rules.push_back(tracker.returnWholeRule());
=======
        else tracker.appendRule(one);
        
		rules.push_back(tracker.returnWholeRule());
>>>>>>> Stashed changes
        return;
    }
    else
    {
        if(tracker.constElseChild() && tracker.compIsOdd())
        {
            tracker.appendRule(one);
            tracker.setCurr(tracker.returnThenChild());
            findBddRules(tracker);
        }
        
        else if (tracker.constThenChild() && tracker.compIsOdd())
        {
            tracker.appendRule(zero);
            tracker.setCurr(tracker.returnElseChild());
            findBddRules(tracker);
        }
        
        else if(!tracker.constThenChild() && !tracker.constElseChild())//split
        {
            BDDit branchTracker = tracker;
            branchTracker.appendRule(zero);
            branchTracker.setCurr(tracker.returnElseChild());
            
            findBddRules(branchTracker);
            
            tracker.appendRule(one);
            tracker.setCurr(tracker.returnThenChild());
            findBddRules(tracker);
        }
        
        else if (tracker.constElseChild() && !tracker.compIsOdd() && !tracker.constThenChild())
        {
<<<<<<< Updated upstream
=======
            //string action = Cudd_V(tracker.returnElseChild());
            BDDit branchTracker = tracker;
            
>>>>>>> Stashed changes
            tracker.appendRule(one);
            tracker.setCurr(tracker.returnThenChild());
            
            findBddRules(tracker);
        }
        
        else if (tracker.constThenChild() && !tracker.compIsOdd() && !tracker.constElseChild())
        {
            BDDit branchTracker = tracker;
            branchTracker.appendRule(one);
            rules.push_back(branchTracker.returnWholeRule());
            
            tracker.appendRule(zero);
            tracker.setCurr(tracker.returnElseChild());
            
            findBddRules(tracker);
        }
    }
    
}

bool RuleReturner::validNoRules()
{
    int numRules = Cudd_CountPathsToNonZero(current);
    cout << "Number of rules: " << numRules << endl;
    int calcNumRules = rules.size();
    if (numRules == calcNumRules)
    {
        return true;
    }
    else return false;
}

BDDit::BDDit()
{
    for (int i = 0; i < NO_BITS_IN_RULE; i++)
    {
        rule += '2';
    }
}

BDDit &BDDit::operator=(const BDDit &aBDDit)
{
    this->compCount = aBDDit.compCount;
    for (int i = 0; i < NO_BITS_IN_RULE; i++)
    this->rule.at(i) = aBDDit.rule.at(i);
    return *this;
}

void BDDit::setCurr(DdNode* _curr)
{
    curr = _curr;
    if(Cudd_IsComplement(curr))
    {
        compCount++;
    }
}

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

void BDDit::appendRule(char _rule)
{
    rule.at(Cudd_NodeReadIndex(curr)) = _rule;
<<<<<<< Updated upstream
=======
   // cout << Cudd_NodeReadIndex(curr) << endl;
>>>>>>> Stashed changes
}