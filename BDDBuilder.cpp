#include "BDDBuilder.h"

BDDBuilder::BDDBuilder(vector<GroupedRule> &binRules)
{
    inRules = binRules;
    inRuleCount = inRules.size();
}

BDDBuilder::~BDDBuilder()
{
}

bool BDDBuilder::buildBDD()
{
    vector<GroupedRule>::iterator rulesIter = inRules.begin();
    string::iterator ruleCharIter;
    DdNode* curr, *var, *tmp, *temp;
    int count =0;
    int debugCount = 0;
    int nodeRef;
    while(rulesIter != inRules.end())
    {
        vector<string> currStrRule = (*rulesIter).returnBinRule();
        
        int action = (*rulesIter).returnAction();
        //cout<<"action: "<<action<<endl;
        vector<string>::iterator binIter = currStrRule.begin();
        while(binIter != currStrRule.end())
        {
            curr = Cudd_ReadOne(manager);
            Cudd_Ref(curr);
            ruleCharIter = (*binIter).begin();
          //  cout<<(*binIter)<<endl;
            count++;
            nodeRef = 0;
            debugCount =0;
            while(ruleCharIter != (*binIter).end())
            {
              //  debugCount++;
              //  cout<<debugCount<<endl;
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
            //cout<<"1 means accept, 2 means reject: "<<(int)action<<endl;
            if(action != 1)
            {
                curr = Cudd_Not(curr);
            }
            if(count == 1)
            {
                mainBdd = curr;
            }
            else 
            {
                addedBDD = curr;
            }
            if(count > 1)
            {
                temp = mainBdd;
               if(action == 1)
               {
                    mainBdd = Cudd_bddOr(manager, temp, addedBDD );
               }
               else 
               {
                    mainBdd =  Cudd_bddAnd(manager, temp, addedBDD );
               }
            }
            ++binIter;
        }
        ++rulesIter;
    }
	
	if(Cudd_CountPathsToNonZero(mainBdd) == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
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