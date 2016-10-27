#include "RuleReturner.h"

RuleReturner::RuleReturner(DdNode* head, Direction _direction)
{
    iter.setCurr(head);
    current = head;
    direction = _direction;
	priority = 500;

}
RuleReturner::RuleReturner(DdNode* head, Direction _direction, int _priority)
{
    iter.setCurr(head);
    current = head;
    direction = _direction;
	priority = _priority;
}

RuleReturner::~RuleReturner()
{
    
}
vector<GroupedRule> RuleReturner::returnRules()
{
    startRuleReturn();
    populateGroupedRules();
    return gRules;
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
        
        else
        {
            tracker.appendRule(one);
        }
        
        //GroupedRule gRule(direction, tracker.returnWholeRule(), priority, Action::accept);
        
        //gRule.debugReturnEnglishRule();
        rules.push_back(tracker.returnWholeRule());
        return;
    }
    else
    {
        if(tracker.constElseChild() && tracker.compIsOdd())
        {
            if(Cudd_IsComplement(tracker.returnElseChild()))
            {
                BDDit branchTracker = tracker;
                branchTracker.appendRule(zero);
               // GroupedRule gRule(direction, branchTracker.returnWholeRule(), priority, Action::accept);
              //  gRule.debugReturnEnglishRule();
                rules.push_back(branchTracker.returnWholeRule());
            }
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
            tracker.appendRule(one);
            tracker.setCurr(tracker.returnThenChild());
            findBddRules(tracker);
        }
        
        else if (tracker.constThenChild() && !tracker.compIsOdd() && !tracker.constElseChild())
        {
            BDDit branchTracker = tracker;
            branchTracker.appendRule(one);
           // GroupedRule gRule(direction, branchTracker.returnWholeRule(), priority, Action::accept);
            //gRule.debugReturnEnglishRule();
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

const bool BDDit::isPenultimateNode()
{
    if(Cudd_IsConstant(Cudd_E(curr)) && Cudd_IsConstant(Cudd_T(curr)))
    {
        return true;
    }
    
    else return false;
}

const bool BDDit::hasTwoChildren()
{
    if(!Cudd_IsConstant(Cudd_E(curr)) && !Cudd_IsConstant(Cudd_T(curr)))
    {
        return true;
    }
    else return false;
}
const bool BDDit::constThenChild()
{
    if (Cudd_IsConstant(Cudd_T(curr)) && !Cudd_IsConstant(Cudd_E(curr)))
    {
        return true;
    }
    else return false;
}

const bool BDDit::constElseChild()
{
    if (Cudd_IsConstant(Cudd_E(curr)) && !Cudd_IsConstant(Cudd_T(curr)))
    {
        return true;
    }
    else return false;
}

const bool BDDit::compIsOdd()
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

const string BDDit::returnWholeRule()
{
    return rule;
}

void BDDit::appendRule(char _rule)
{
    rule.at(Cudd_NodeReadIndex(curr)) = _rule;
}

void RuleReturner::populateGroupedRules()
{
    TwoRanger ranger(rules);
    rules = ranger.returnNewRules();
    
    for(auto i: rules)
    {
        GroupedRule temp(direction, i, priority, Action::accept);
        gRules.push_back(temp);
    }
    
}