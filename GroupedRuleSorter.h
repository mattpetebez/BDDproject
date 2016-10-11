#include <iostream>
#include "GroupedRule.h"
#include <vector>


#ifndef GROUPEDRULESORTER_H
#define GROUPEDRULESORTER_H

class GroupedRuleSorter
{
public:
    GroupedRuleSorter(vector<GroupedRule>& _rules);
    ~GroupedRuleSorter();
    
    void groupByIP();
    
    void sortBySrcPort();
    void sortByDstPort();
    
    void reduceRules();
    vector<vector<GroupedRule>> returnGroup();
private: 
    vector<GroupedRule> rules;
    vector<vector<GroupedRule>> grpedByIP;

};

#endif // GROUPEDRULESORTER_H
