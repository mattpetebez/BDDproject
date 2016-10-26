#include "BDDnavigator.h"

BDDnavigator::BDDnavigator(GroupedRule _requestedRule, vector<GroupedRule> _unExceptableRules)
{
    requestedRule = _requestedRule;
    unExceptableRules = _unExceptableRules;
}

BDDnavigator::~BDDnavigator()
{
}

void BDDnavigator::initialise()
{
    RangeHelper helper;
    expandedRequestedRule = helper.returnRangedRules(requestedRule);
    
    for(auto i: expandedRequestedRule)
    {
        vector<string> temp = i.returnRangedBinRule();
        binRequestedRules.insert(binRequestedRules.end(), temp.begin(), temp.end());
        temp.clear();
    }
    
    BDDBuilder unExceptableRulesBDD(unExceptableRules);
    unExceptableRulesBDD.buildBDD();

    head = unExceptableRulesBDD.returnHead();    

}

void BDDnavigator::findBinExceptedRules()
{
    auto iter = binRequestedRules.begin();
    while(iter != binRequestedRules.end())
    {
        bool isExceptable = true;
        auto binIter = (*iter).begin();
        BDDit curr;
        curr.setCurr(head);
        while(binIter != (*iter).end())
        {
            if(Cudd_NodeReadIndex(curr.curr) != distance((*iter).begin(), binIter))
            {
                traverseTilEqual((*iter), curr, binIter);
            }
            if(Cudd_NodeReadIndex(curr.curr) != distance((*iter).begin(), binIter))
            {
                cout << "Traverse function did not work." << endl;
            }
            if(curr.isPenultimateNode())
            {
                if((*binIter == '0'))
                {
                    if(curr.compIsOdd() && Cudd_IsComplement(Cudd_E(curr.curr)))
                    {
                        isExceptable = false;
                        break;
                    }
                    
                    else if(!curr.compIsOdd() && !Cudd_IsComplement(Cudd_E(curr.curr)))
                    {
                        isExceptable = false;
                        break;
                    }
                    
                    else break;
                }
                else if((*binIter) == '1')
                {
                    if(!curr.compIsOdd())
                    {
                        isExceptable = false;
                        break;
                    }
                    else break;
                }
            }
            
            if((*binIter) == '1')
            {
                if(curr.constThenChild())
                {
                    if(!curr.compIsOdd())
                    {
                        isExceptable = false;
                        break;
                    }
                    else 
                    {
                        break;
                    }
                }
                else 
                {
                    curr.setCurr(curr.returnThenChild());
                    ++binIter;
                }
            }
            else if((*binIter) == '0')
            {
                if(curr.constElseChild())
                {
                    if(curr.compIsOdd() && Cudd_IsComplement(Cudd_E(curr.curr)))
                    {
                        isExceptable = false;
                        break;
                    }
                    else if(!curr.compIsOdd() && !Cudd_IsComplement(Cudd_E(curr.curr)))
                    {
                        isExceptable = false;
                        break;
                    }
                    else break;
                }
                else
                {
                    curr.setCurr(curr.returnElseChild());
                    ++binIter;
                }
            }
        }
        if(isExceptable)
        {
            binExceptedRules.push_back((*iter));
        }
        ++iter;
    }
}

void BDDnavigator::traverseTilEqual(string& _binRule, BDDit& _curr, string::iterator& _binIter)
{
    while(distance(_binRule.begin(), _binIter) < Cudd_NodeReadIndex(_curr.curr))
    {
        ++_binIter;
    }
}

void BDDnavigator::buildReturnableExceptedRules()
{
    for(auto i: binExceptedRules)
    {
        GroupedRule temp(requestedRule.returnDirection(),i,requestedRule.returnPriority(), requestedRule.returnActionEnum());
        returnableExceptedRules.push_back(temp);
    }
}

vector <GroupedRule> BDDnavigator::returnExceptedRules()
{
    initialise();
    findBinExceptedRules();
    buildReturnableExceptedRules();
    return returnableExceptedRules;
}