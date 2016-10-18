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
    vector<GroupedRule> sortRules();
    
private: 
    void groupByIP();
    void sortBySrcPort(Field);
    void sortByDstPort();
    void sortIP(Field field, vector<GroupedRule>& unsorted);
    void groupByDstPort();
    void reduceRules();
    
    void reduceByDestPort(vector<GroupedRule>&);
    void reduceBySrcPort(vector<GroupedRule>&);
    void rebuildRules();
    bool reduceConsecutiveSrcPort(GroupedRule& _prime, GroupedRule& _second);
    vector<vector<GroupedRule>> returnGroup();
    bool reduceConsecutiveDstPort(GroupedRule& _prime, GroupedRule& _second);
    vector<GroupedRule> rules;
    vector<vector<GroupedRule>> grpedByIP;
};

#endif // GROUPEDRULESORTER_H
