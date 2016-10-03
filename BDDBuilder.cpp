#include "BDDBuilder.h"

BDDBuilder::BDDBuilder(vector<GroupedRule> binRules)
{
    inRules = binRules;
    inRuleCount = inRules.size();
    //manager = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0);
}

BDDBuilder::~BDDBuilder()
{
}

void BDDBuilder::buildBDD()
{
    vector<GroupedRule>::iterator rulesIter = inRules.begin();
//    cout << *rulesIter << endl;
    string::iterator ruleCharIter;
    DdNode* curr, *var, *tmp, *temp;
    
    int nodeRef;
    while(rulesIter != inRules.end())
    {
        curr = Cudd_ReadOne(manager);
        Cudd_Ref(curr);
        string currStrRule = (*rulesIter).returnBinRule();
        //cout<<currStrRule<<endl;
        ruleCharIter = currStrRule.begin();
//        cout << *ruleCharIter << endl;
        nodeRef = 0;
        while(ruleCharIter != currStrRule.end())
        {
//            cout << nodeRef << endl;
            if (*ruleCharIter == '2')
            {
                nodeRef++;
            }
            else
            {
                var = Cudd_bddIthVar(manager, nodeRef);
                if(*ruleCharIter == '0')
                {
                    tmp = Cudd_bddAnd(manager, Cudd_Not(var), curr);
                }
                else if(*ruleCharIter == '1')
                {
                    tmp = Cudd_bddAnd(manager, var, curr);
                }
                
                Cudd_Ref(tmp);
                Cudd_RecursiveDeref(manager, curr);
                curr = tmp;
                
                nodeRef++;
            }
        ++ruleCharIter;
        }
        if(rulesIter == inRules.begin())
        {
            mainBdd = curr;
//            cout << "Adding mainBDD node" << endl;
        }
        else 
        {
            addedBDD = curr;
//            cout << "Adding addedBDD node" << endl;
        }
//        cout << Cudd_CountPath(addedBDD) << endl;
        if(rulesIter > inRules.begin())
        {
            temp = mainBdd;
            mainBdd = Cudd_bddOr(manager, temp, addedBDD);
        }
        ++rulesIter;
    }
}
void BDDBuilder::addRule(string& rule, string& action)
{
    int nodeRef = 0;
 
    DdNode* curr, *var, *tmp;
       curr = Cudd_ReadOne(manager);
    Cudd_Ref(curr);
    for(auto i: rule)
    {
                var = Cudd_bddIthVar(manager, nodeRef);
                if(i == '0')
                {
                    tmp = Cudd_bddAnd(manager, Cudd_Not(var), curr);
                }
                else if(i == '1')
                {
                    tmp = Cudd_bddAnd(manager, var, curr);
                }
                
                Cudd_Ref(tmp);
                Cudd_RecursiveDeref(manager, curr);
                if(action == "accept")
                curr = tmp;
                else curr = Cudd_Not(tmp);
                nodeRef++;
    }
         
         if(action == "accept")
         mainBdd = Cudd_bddOr(manager, mainBdd, curr );
         else mainBdd = Cudd_bddAnd(manager, mainBdd, curr );
}
    

void BDDBuilder::printBDD(string& filename)
{
    BDDDiag = fopen(filename.c_str(),"w");
    Cudd_DumpDot(manager, 1, &mainBdd, NULL,NULL,BDDDiag);
}

DdNode* BDDBuilder::returnHead()
{
    return mainBdd;
}