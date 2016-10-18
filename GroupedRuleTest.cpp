#include "GroupedRule.h"
#include "cudd.h"
#include "BDDBuilder.h"
#include "RuleReturner.h"
#include "GroupedRuleSorter.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

int main()
{ 
    Direction direction = Direction::in;
    Protocol protocol = Protocol::icmp;
    Action action = Action::accept;
    int priority = 500;
    int srcPortStart = 490;
    int srcPortEnd = 500;
    int destPortStart = 490;
    int destPortEnd = 500;
    
    int ip1 = 192;
    int ip2 = 168;
    int ip3 = 1;
    int ip4 = 18;

    GroupedRule tester(protocol, srcPortStart,srcPortEnd,destPortStart,destPortEnd,ip1,ip2,ip3,ip4,priority,direction,action);
    
    priority = 500;
    srcPortStart = 480;
    srcPortEnd = 490;
    destPortStart = 480;
    destPortEnd = 480;
    
    ip1 = 192;
    ip2 = 168;
    ip3 = 1;
    ip4 = 25;
    
    GroupedRule tester3(protocol, srcPortStart,srcPortEnd,destPortStart,destPortEnd,ip1,ip2,ip3,ip4,priority,direction,action);
    
     priority = 500;
    srcPortStart = 400;
    srcPortEnd = 410;
    destPortStart = 420;
    destPortEnd = 430;
    
    ip1 = 192;
    ip2 = 168;
    ip3 = 1;
    ip4 = 25;
    
    GroupedRule tester4(protocol, srcPortStart,srcPortEnd,destPortStart,destPortEnd,ip1,ip2,ip3,ip4,priority,direction,action);
    
    vector<GroupedRule> rules;
    rules.push_back(tester);
    rules.push_back(tester3);
     rules.push_back(tester4);
    BDDBuilder bddbuilder(rules);
    bddbuilder.buildBDD();
    
    RuleReturner rulereturner(bddbuilder.returnHead(), Direction::in);
    rulereturner.startRuleReturn();
    string lekker = "MattWakeUp";
    bddbuilder.printBDD(lekker);
    
    vector<GroupedRule> test;
    vector<string> rulez;
    test = rulereturner.returnRules();
    //cout<<test.size()<<endl;
    vector<string> retVal;
    
    vector<GroupedRule> tester2Ret;
    for(auto i:test)
    {
        rulez=i.returnBinRule();
        for(auto j:rulez)
        {
        GroupedRule temp(Direction::in, j);
        tester2Ret.push_back(temp);
        }
    }

    
    GroupedRuleSorter sorted(tester2Ret);
    
    
/*        for(auto j:tester2Ret)
    {
        cout<< "srcportstart: "<<j.returnSrcPort()<<" srcportend: "<<j.returnSrcPortEnd()<<" destportstart: "<<j.returnDestPort()<<" destportend: "<<j.returnDestPortEnd()<<endl;
    }
    */
    sorted.groupByIP();
   // sorted.sortBySrcPort();
   
    
    
    sorted.groupByDstPort();
    
    vector<vector<GroupedRule>> testeing = sorted.returnGroup();
    cout<<"The size of testeing is: "<<testeing.size()<<endl;
    cout<<"The size of the one ip vector is: "<<testeing[0].size()<<endl;
    cout<<"The size of the other ip vector is: "<<testeing[1].size()<<endl;
    testeing[0][0].debugReturnEnglishRule();
    testeing[0][1].debugReturnEnglishRule();
    testeing[1][0].debugReturnEnglishRule();
    
    //cout << retVal.size() << endl;
    return 0;
}