#include "GroupedRule.h"

#ifndef RANGEHELPER_H
#define RANGEHELPER_H

class RangeHelper
{
public:
    RangeHelper();
    ~RangeHelper();
    
    void manageTwosCreateGroupedRules();
    void populateRangedRules(vector<GroupedRule>&);
    
    vector<GroupedRule> returnRangedRules(GroupedRule);
private:
     vector<GroupedRule> rangedRules;
};

#endif // RANGEHELPER_H
