#include "UserMachine.h"

UserMachine::UserMachine(string _username)
{
    username = _username;
    string UserRulesFile = username+"-rules.xml";
    XMLParserIn inparser(UserRulesFile);
    inparser.buildInOutRules(inRules, outRules);
}

UserMachine::~UserMachine()
{
}

bool UserMachine::addRule(GroupedRule& _rule)
{
    if(_rule.returnDirection() == Direction::in)
    {
        inRules.push_back(_rule);
        BDDBuilder builder(inRules);
        builder.buildBDD();
        
        RuleReturner returner(builder.returnHead(), Direction::in);
        inRules = returner.returnRules();
        
        GroupedRuleSorter sorter(inRules);
        inRules = sorter.sortRules();
        
        XMLParserOut out;
		username = "user2";
        out.parseOutGroupedRules(inRules, username);
    }
    
    else if(_rule.returnDirection() == Direction::out)
    {
        outRules.push_back(_rule);
        BDDBuilder builder(outRules);
        builder.buildBDD();
        
        RuleReturner returner(builder.returnHead(), Direction::out);
        outRules = returner.returnRules();
        
		
        GroupedRuleSorter sorter(outRules);
        outRules = sorter.sortRules();
        
        XMLParserOut out;
		username = "user2";
        out.parseOutGroupedRules(outRules, username);
    }
}

