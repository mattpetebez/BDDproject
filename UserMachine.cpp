#include "UserMachine.h"

UserMachine::UserMachine(string _username)
{
    username = _username;
    string UserRulesFile = username+"-rules.xml";
    XMLParserIn inparser(username);
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
        out.parseOutGroupedRules(inRules);
    }
    
    else if(_rule.returnDirection() == Direction::out)
    {
        outRules.push_back(_rule);
        BDDBuilder builder(outRules);
        builder.buildBDD();
        
        RuleReturner returner(builder.returnHead(), Direction::in);
        outRules = returner.returnRules();
        
        GroupedRuleSorter sorter(inRules);
        outRules = sorter.sortRules();
        
        XMLParserOut out;
        out.parseOutGroupedRules(outRules);
    }
}

