#ifndef USERMACHINE_H
#define USERMACHINE_H


#include <vector>
#include "GroupedRule.h"
#include "BDDBuilder.h"
#include "RuleReturner.h"
#include "XMLParserIn.h"
#include "XMLParserOut.h"
#include "GroupedRuleSorter.h"

using namespace std;

class UserMachine
{
public:
    UserMachine(string& _username);
    ~UserMachine();
    
    bool addRule(vector<GroupedRule>& );
    bool deleteRule(GroupedRule&);
	bool groupedRuleEquivalence(GroupedRule rule1, GroupedRule rule2);
private:
    string username;
    vector<GroupedRule> inRules;
	vector<GroupedRule> outRules;
};

#endif // USERMACHINE_H
