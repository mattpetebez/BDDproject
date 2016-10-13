#include "GroupedRuleSorter.h"

GroupedRuleSorter::GroupedRuleSorter(vector<GroupedRule>& _rules)
{
    rules = _rules;
}

GroupedRuleSorter::~GroupedRuleSorter()
{
}

vector<GroupedRule> GroupedRuleSorter::sortRules()
{
    
    groupByIP();
    sortBySrcPort();
    groupByDstPort();//Need to change the name of this function.
    rebuildRules();
    return rules;
}

void GroupedRuleSorter::rebuildRules()
{
    vector<vector<GroupedRule>>::iterator primary = grpedByIP.begin();
    vector<vector<GroupedRule>>::iterator secondary = grpedByIP.begin();
    ++secondary;
    while(secondary != grpedByIP.end())
    {
        (*primary).insert((*primary).end(), (*secondary).begin(), (*secondary).end());
/*        for(auto i: (*primary))
        {
            i.debugReturnEnglishRule();
        }*/
        ++secondary;
    }
    rules.clear();
    rules = (*primary);
/*    for(auto i: rules)
    {
        i.debugReturnEnglishRule();
    }*/
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
//                cout<<(*tempIter).returnWholeIP()<<endl;
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
                while(j>0 && rules[j].GenericReturn(Field::srcportstart) < rules[j-1].GenericReturn(Field::srcportstart))
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
    
void GroupedRuleSorter::groupByDstPort()
{
    vector<vector<GroupedRule>>::iterator vecIter = grpedByIP.begin();
    
    while(vecIter != grpedByIP.end())
    {
        reduceByDestPort((*vecIter));
        ++vecIter;
    }
    
    vecIter = grpedByIP.begin();
    
     while(vecIter != grpedByIP.end())
    {
        reduceBySrcPort((*vecIter));
        ++vecIter;
    }
}

void GroupedRuleSorter::reduceByDestPort(vector<GroupedRule>& groupedRules)
{
    vector<GroupedRule>::iterator primeIter = groupedRules.begin();
    vector<GroupedRule>::iterator secondIter;
    while(primeIter != groupedRules.end())
    {
        secondIter = groupedRules.begin();
        while(secondIter != groupedRules.end())
        {
            if(primeIter != secondIter)
            {   
                
                if(reduceConsecutiveDstPort((*primeIter), (*secondIter)))
                {
                    groupedRules.erase(secondIter);
                    secondIter = groupedRules.begin();
                    primeIter = groupedRules.begin();
                }
                else 
                {
                    ++secondIter;
                }
            }
            else
            {
                ++secondIter;
            }
        }
        ++primeIter;
    }
}

bool GroupedRuleSorter::reduceConsecutiveDstPort(GroupedRule& _prime, GroupedRule& _second)
{
    if((_prime.returnProt() == _second.returnProt()) && (_prime.GenericReturn(Field::srcportstart) == _second.GenericReturn(Field::srcportstart)) 
    && (_prime.GenericReturn(Field::srcportend) == _second.GenericReturn(Field::srcportend)))
    {
            int tempPrimeUpper = _prime.GenericReturn(Field::dstportend);
            int tempPrimeLower = _prime.GenericReturn(Field::dstportstart);
            int tempSecondUpper = _second.GenericReturn(Field::dstportend);
            int tempSecondLower = _second.GenericReturn(Field::dstportstart);
            
            if((tempSecondLower - tempPrimeUpper) == 1)
            {
                _prime.GenericSet(Field::dstportend, tempSecondUpper);
                return true;
            }
            
            else if ((tempPrimeLower - tempSecondUpper) == 1)
            {
                _prime.GenericSet(Field::dstportstart, tempSecondLower);
                return true;
            }
            else
            {
                return false;
                
            }
    }
    else 
    {
        return false;
    }
    
}

void GroupedRuleSorter::reduceBySrcPort(vector<GroupedRule>& groupedRules)
{
    vector<GroupedRule>::iterator primeIter = groupedRules.begin();
    vector<GroupedRule>::iterator secondIter;
    
    while(primeIter != groupedRules.end())
    {
        secondIter = groupedRules.begin();
        while(secondIter != groupedRules.end())
        {
            if(primeIter != secondIter)
            {
                if(reduceConsecutiveSrcPort((*primeIter), (*secondIter)))
                {
                    groupedRules.erase(secondIter);
                }
                else 
                {
                    ++secondIter;
                }
            }
            else
            {
                ++secondIter;
            }
        }
        ++primeIter;
    }
}

bool GroupedRuleSorter::reduceConsecutiveSrcPort(GroupedRule& _prime, GroupedRule& _second)
{
    if((_prime.returnProt() == _second.returnProt()) && (_prime.GenericReturn(Field::dstportstart) == _second.GenericReturn(Field::dstportstart))
    && (_prime.GenericReturn(Field::dstportend) == _second.GenericReturn(Field::dstportend)))
    {
            int tempPrimeUpper = _prime.GenericReturn(Field::srcportend);
            int tempPrimeLower = _prime.GenericReturn(Field::srcportstart);
            int tempSecondUpper = _second.GenericReturn(Field::srcportend);
            int tempSecondLower = _second.GenericReturn(Field::srcportstart);
            
            if((tempSecondLower - tempPrimeUpper) == 1)
            {
                _prime.GenericSet(Field::srcportend, tempSecondUpper);
                return true;
            }
            
            else if ((tempPrimeLower - tempSecondUpper) == 1)
            {
                _prime.GenericSet(Field::srcportstart, tempSecondLower);
                return true;
            }
            else
            {
                return false;
                
            }
    }
    else 
    {
        return false;
    }
    
}
