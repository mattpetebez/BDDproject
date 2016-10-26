#include "RuleReturner.h"

RuleReturner::RuleReturner()
{
    
}

RuleReturner::~RuleReturner()
{
    
}

void RuleReturner::findBddRules(BDDit tracker)
{
    
    string one = "1";
    string zero = "0";
    //tracker.setCurr(node);
    
    if(tracker.isPenultimateNode())
    {
        rules.push_back(tracker.returnWholeRule());
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
        
        else if(!tracker.constThenChild() && !tracker.constElseChild())
        {
            BDDit branchTracker;
            
            branchTracker.setCurr(tracker.returnElseChild());
            branchTracker.appendRule(tracker.returnWholeRule());
            branchTracker.appendRule(zero);
            findBddRules(branchTracker);
            
            tracker.appendRule(one);
            tracker.setCurr(tracker.returnThenChild());
            findBddRules(tracker);
        }
        
        else if (tracker.constElseChild() && !tracker.compIsOdd())
        {
            string action = Cudd_V(tracker.returnElseChild());
        }
    }
//    BDDit bddit;
//    string zero ="0";
//    string one="1";
//    DdNode *elsechild, *thenchild;
//    bddit.curr = node;
//    if(bddit.isPenultimateNode())
//    {
//        //do nothing
//    }
//    else if(bddit.constElseChild())
//    {
//        thenchild = Cudd_T(bddit.curr);
//        if(Cudd_IsComplement(thenchild))
//        {
//            bddit.compCount++;
//        }
//        if(compCount % 2 == 0)
//        {
//            rule = rule + one;
//        }
//    }
//    else if(bddit.constThenChild())
//    {
//        elsechild = Cudd_E(bddit.curr);
//        if(Cudd_IsComplement(elsechild))
//        {
//            bddit.compCount++;
//        }
//        if(compCount % 2 == 0)
//        {
//            rule = rule + zero;
//        }
//    }
//    
        
}