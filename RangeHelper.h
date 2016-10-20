#include <memory>
#include "GroupedRule.h"

#ifndef RANGEHELPER_H
#define RANGEHELPER_H

using namespace std;

using shared = std::shared_ptr<GroupedRule>;

class RangeHelper
{
public:
    RangeHelper();
    ~RangeHelper();
    
    vector<GroupedRule> returnRangedRules(GroupedRule&);
    void returnVectorRangedRules(vector<GroupedRule>& _rules);
    
private:
    void populateRangedRules();
    void checkRange(Field, Field, Field);
    void checkIP2();
    void checkIP3();
    void checkIP4();
    void checkProtocol();
    vector<std::shared_ptr<GroupedRule>> rangedRules;
    vector<std::shared_ptr<GroupedRule>> rangedIP2;
    vector<GroupedRule> grpReturn;
};

#endif // RANGEHELPER_H
