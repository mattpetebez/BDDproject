#include "GroupedRule.h"
#include 



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
    void reduceByIP(vector<GroupedRule>& );
    vector<GroupedRule> inRules;
    vector<GroupedRule> outRules;
    vector<vector<GroupedRule>> groupByPriority(vector<GroupedRule>&)
    bool loggedIn = true;
};

#endif // ADMINMACHINE_H
