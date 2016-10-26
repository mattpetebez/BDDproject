#include <iostream>
#include <memory>
#include <algorithm>
#include <fstream>

#include "GroupedRule.h"
#include "XMLParserIn.h"
#include "XMLParserOut.h"
#include "BDDBuilder.h"
#include "RuleReturner.h"
#include "BDDnavigator.h"

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
	void reduceUsingBDD(vector<GroupedRule>& rules);
	vector<GroupedRule> ruleAllowed(string user, string password, GroupedRule _rule);
private:
//Maybe need to consider a sort by priority?
	void removeRedundancy(vector<vector<GroupedRule>>& _rules);
	string username = "Admin";
   // void reduceByIP(vector<GroupedRule>& );
	vector<GroupedRule> rebuildRules(vector<vector<GroupedRule>>& rules);
	void removeCopies(vector<GroupedRule>& rules);
	bool groupedRuleEquivalence(GroupedRule rule1, GroupedRule rule2);
    vector<GroupedRule>  populateUnExceptable(Direction, int);
    vector<GroupedRule> inRules;
    vector<GroupedRule> outRules;
    vector<vector<GroupedRule>> groupByPriority(vector<GroupedRule>&);
    bool loggedIn = true;
	int BarryPriorityLevel = 500;
	int LarryPriorityLevel = 400;
};

#endif // ADMINMACHINE_H
