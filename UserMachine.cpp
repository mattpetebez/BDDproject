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
            
            RangeHelper helper;
            helper.returnVectorRangedRules(inRules);
    }
    
    else if(_rule.returnDirection() == Direction::in)
    {
        
    }
}

