#include "RangeHelper.h"

RangeHelper::RangeHelper()
{

}

RangeHelper::~RangeHelper()
{
}

vector<GroupedRule> RangeHelper::returnRangedRules(GroupedRule rangedRule)
{
    rangedRules.push_back(rangedRule);
    populateRangedRules(rangedRules);
    return rangedRules;
}

void RangeHelper::populateRangedRules(vector<GroupedRule>& _rangedRules)
{
    int i = (int)Field::ip1Upper;
    
    int end = (int)Field::protocolUpper;
    
    int ranger = (int)Field::ip1Range;
    
    for (i; i <=end; i+2)
    {
        auto it = _rangedRules.begin();
        while(it != _rangedRules.end())
        {
            if((*it).GenericReturn((Field)ranger) > 0)
            {
                for(int j = (*it).GenericReturn((Field)(i+1)); j < (*it).GenericReturn((Field)(i)); j++)
                {
                    GroupedRule temp = (*it);
                    temp.GenericSet((Field)ranger, j);
                    _rangedRules.push_back(temp);
                }
                _rangedRules.erase(it);
            }
            ++it;
        }
        ranger++;
    }
}