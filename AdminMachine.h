#include "GroupedRule.h"
#include <algorithm>
#include "XMLParserIn.h"
#include "XMLParserOut.h"


#ifndef ADMINMACHINE_H
#define ADMINMACHINE_H

class AdminMachine
{
public:
    AdminMachine();
    ~AdminMachine();
    
    bool addRule(GroupedRule&);
    bool deleteRule(GroupedRule&);
    void startLogin(string& username, string& hashedPassword);
    void populateRules();
private:
//Maybe need to consider a sort by priority?
	void removeRedundancy(vector<vector<GroupedRule>>& _rules);
    void reduceByIP(vector<GroupedRule>& );
	vector<GroupedRule> rebuildRules(vector<vector<GroupedRule>>& rules);
	void removeCopies(vector<GroupedRule>& rules);
	bool groupedRuleEquivalence(GroupedRule& rule1, GroupedRule& rule2);
    vector<GroupedRule> inRules;
    vector<GroupedRule> outRules;
    vector<vector<GroupedRule>> groupByPriority(vector<GroupedRule>&);
    bool loggedIn = true;
};

#endif // ADMINMACHINE_H
