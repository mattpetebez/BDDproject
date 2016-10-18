#include "RangeHelper.h"

RangeHelper::RangeHelper()
{

}

RangeHelper::~RangeHelper()
{
}

vector<GroupedRule> RangeHelper::returnRangedRules(GroupedRule& rangedRule)
{
    grpReturn.clear();
    auto temp = std::make_shared<GroupedRule>(rangedRule);
    rangedRules.push_back(temp);
    checkRange(Field::ip1Range, Field::ip1Upper, Field::ip1Lower);
    checkRange(Field::ip2Range, Field::ip2Upper, Field::ip2Lower);
    checkRange(Field::ip3Range, Field::ip3Upper, Field::ip3Lower);
    checkRange(Field::ip4Range, Field::ip4Upper, Field::ip4Lower);
    checkRange(Field::protocolRange, Field::protocolUpper, Field::protocolLower);
    populateRangedRules();
    return grpReturn;
    
}

void RangeHelper::populateRangedRules()
{
    for(auto i: rangedRules)
    {
        GroupedRule tempRule = *i;
        grpReturn.push_back(tempRule);
    }
}

void RangeHelper::checkRange(Field range, Field upper, Field lower)
{
    auto it = rangedRules.begin();
    vector<shared_ptr<GroupedRule>> tempVec;
    while(it != rangedRules.end())
    {
        if((*it)->GenericReturn(range) > 0)
        {
            int iEnd = (*it)->GenericReturn(upper);
            for(int i = (*it)->GenericReturn(lower); i <= iEnd; i++)
            {
                shared temp = std::make_shared<GroupedRule>(GroupedRule());
                (*temp) = (*it)->deepcopy();
                 
                (temp)->GenericSet(range, i);
                tempVec.push_back((temp));
               
            }
            rangedRules.erase(it);
        }
        else ++it;
    }
    rangedRules.insert(rangedRules.end(), tempVec.begin(), tempVec.end());
    tempVec.clear();
}
