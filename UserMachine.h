#ifndef USERMACHINE_H
#define USERMACHINE_H


#include <vector>
#include "GroupedRule.h"
#include "BDDBuilder.h"
#include "RuleReturner.h"
class UserMachine
{
public:
    UserMachine();
    ~UserMachine();
    
    bool addRule(GroupedRule&);
    bool deleteRule(GroupedRule&);
private:
    vector<GroupedRule>

};

#endif // USERMACHINE_H
