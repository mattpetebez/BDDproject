#include "GroupedRuleSorter.h"

GroupedRuleSorter::GroupedRuleSorter(vector<GroupedRule>& _rules)
{
    rules = _rules;
}

GroupedRuleSorter::~GroupedRuleSorter()
{
}

void GroupedRuleSorter::groupByIP()
{
    string tempIP = "";
    
    vector<GroupedRule>::iterator iter;
    
    while(!rules.empty())
    {
        vector<GroupedRule> tempGrpIP;
        
        iter = rules.begin();
         
        tempIP = (*iter).returnWholeIP();
        
        vector<GroupedRule>::iterator tempIter = rules.begin();
        
        while(tempIter != rules.end())
        {
            if((*tempIter).returnWholeIP() == tempIP)
            {
                GroupedRule tempGroupedRule = (*tempIter);
                tempGrpIP.push_back(tempGroupedRule);
                rules.erase(tempIter);
            }
            else ++tempIter;
        }
        
        grpedByIP.push_back(tempGrpIP);
        
    }
}

vector<vector<GroupedRule>> GroupedRuleSorter::returnGroup()
{
    return grpedByIP;
}

void GroupedRuleSorter::sortBySrcPort()
{
    for(auto i:grpedByIP)
    {
        for(auto m:i)
        {
            GroupedRule temp = m;
            int j;
            int limit = rules.size();
            for(int i =0; i<limit; i++)
            {
                j=i;
                while(j>0 && rules[j].returnSrcPort() < rules[j-1].returnSrcPort())
                {
                    temp = rules[j];
                    rules[j]=rules[j-1];
                    rules[j-1]=temp;
                    j--;
                }
            }
        }
    }
}
    
