#include "AdminMachine.h"

AdminMachine::AdminMachine()
{
    string filename = "Admin-Rules";
    XMLParserIn inparser(filename);
    inparser.buildInOutRules(inRules, outRules);
    reverse(inRules.begin(),inRules.end()); 
    reverse(outRules.begin(),outRules.begin());
}

AdminMachine::~AdminMachine()
{
    vector<GroupedRule> inoutRules;
    inoutRules.insert(inoutRules.end(), inRules.begin(), inRules.end());
    inoutRules.insert(inoutRules.end(),outRules.begin(),outRules.end());
    XMLParserOut printAdminRules(inoutRules);

}

bool AdminMachine::addRule(GroupedRule& _rule)
{
    if(!loggedIn)
    {
        cout << "You need to be logged in as administrator to add rules to the firewall" << endl;
        return false;
    }
    else
    {
        if(_rule->returnDirection() == Direction::in)
        {
            inRules.push_back(_rule);
            auto tempVec = groupByPriority(inRules);
            removeRedundancy(tempVec);
            inRules = rebuildRules(tempVec);
            return true;
        }
        else 
        {
            outRules.push_back(_rule);
            auto tempVec = groupByPriority(outRules);
            removeRedundancy(tempVec);
            removeCopies(tempVec);
            outRules = rebuildRules(tempVec);
            return true;
        }
    }
}

vector<vector> AdminMachine::groupByPriority(vector<GroupedRule>& _rules)
{
    if(_rules.isEmpty)
    {
        cout << "The vector you're trying to group by priorty is empty." << endl;
        return NULL;
    }
    else
    {
        vector<vector<GroupedRule> returnVec;
        returnVec.clear();
        while(!_rules).empty())
        {
            auto it = _rules.begin();
            int tempIdentifier = it->returnPriority();
            vector<GroupedRule> tempVec;
            while(it != _rules.end())
            {
                if(it->returnPriority() == tempIdentifier)
                {
                    GroupedRule temp = (*it);
                    tempVec.push_back(temp);
                    _rules.erase(it);
                }
                else ++it;
            }
            returnVec.push_back(tempVec);
            tempVec.clear() //Need to check whether this deletes everything in returnVec?
        }
        
        return returnVec;
    }
}

void AdminMachine::removeRedundancy(vector<vector<GroupedRule>>& _rules)
{
    auto iter = _rules.begin();
    
    while(iter != _rules.end())
    {
        reduceByIP((*iter));
        ++iter;
    }
}
/*            if(_rule.GenericReturn(Field::ip1Upper) <= iter->GenericReturn(Field::ip1Upper) &&
               _rule.GenericReturn(Field::ip1Lower) >= iter->GenericReturn(Field::ip1Lower) &&
               _rule.GenericReturn(Field::ip2Upper) <= iter->GenericReturn(Field::ip2Upper) &&
               _rule.GenericReturn(Field::ip2Lower) >= iter->GenericReturn(Field::ip2Lower) &&
               _rule.GenericReturn(Field::ip3Upper) <= iter->GenericReturn(Field::ip3Upper) &&
               _rule.GenericReturn(Field::ip3Lower) >= iter->GenericReturn(Field::ip3Lower) &&
               _rule.GenericReturn(Field::ip4Upper) <= iter->GenericReturn(Field::ip4Upper) &&
               _rule.GenericReturn(Field::ip4Lower) >= iter->GenericReturn(Field::ip4Lower) &&
               _rule.GenericReturn(Field::protocolLower) >= iter->GenericReturn(Field::protocolLower) &&
               _rule.GenericReturn(Field::protocolUpper) >= iter->GenericReturn(Field::protocolUpper) &&
               _rule.returnAction() == iter->returnAction())*/
               
void AdminMachine::reduceByIP(vector<GroupedRule>& rules)
{
    auto iter1 = rules.begin();
    auto iter2 = rules.begin();
    GroupedRule temp = (*iter);
    while(iter1 != rules.end())
    {
        while(iter2 != rules.end())
        {
            if(iter1 == iter2)
            {
                ++iter2;
            }
            else if ((*iter1)->GenericReturn(Field::protocolUpper) == (*iter2)->GenericReturn(Field::protocolUpper) &&
                     (*iter1)->GenericReturn(Field::protocolLower) == (*iter2)->GenericReturn(Field::protocolLower) &&
                     (*iter1)->GenericReturn(Field::ip1Upper) == (*iter2)->GenericReturn(Field::ip1Upper) &&
                     (*iter1)->GenericReturn(Field::ip1Lower) == (*iter2)->GenericReturn(Field::ip1Lower) &&
                     (*iter1)->GenericReturn(Field::ip2Upper) == (*iter2)->GenericReturn(Field::ip2Upper) &&
                     (*iter1)->GenericReturn(Field::ip2Lower) == (*iter2)->GenericReturn(Field::ip2Lower) &&
                     (*iter1)->GenericReturn(Field::ip3Upper) == (*iter2)->GenericReturn(Field::ip3Upper) &&
                     (*iter1)->GenericReturn(Field::ip3Lower) == (*iter2)->GenericReturn(Field::ip3Lower) &&
                     (*iter1)->GenericReturn(Field::srcportstart) == (*iter2)->GenericReturn(Field::srcportstart) &&
                     (*iter1)->GenericReturn(Field::srcportend) == (*iter2)->GenericReturn(Field::srcportend) &&
                     (*iter1)->GenericReturn(Field::dstportstart) == (*iter2)->GenericReturn(Field::dstportstart) &&
                     (*iter1)->GenericReturn(Field::dstportend) == (*iter2)->GenericReturn(Field::dstportend))
                     {
                        int iter1Upper = iter1->GenericReturn(Field::ip4Upper);
                        int iter1Lower = iter1->GenericReturn(Field::ip4Lower);
                        int iter2Upper = iter2->GenericReturn(Field::ip4Upper);
                        int iter2Lower = iter2->GenericReturn(Field::ip4Lower);
                        
                        if(iter1Upper >= iter2Lower && iter1Lower <= iter2Upper)
                        {
                            iter1->GenericSet(Field::ip4Upper, iter2Upper);
                            rules.erase(iter2);
                            iter2 = rules.begin();
                            iter1 = rules.begin();
                        }
                        
                        else if(iter2Lower <= iter1Upper && iter2Lower >= iter2Lower)
                        {
                            iter1->GenericReturn(Field::ip4Lower, iter2Lower);
                            rules.erase(iter2);
                            iter2 = rules.begin();
                            iter1 = rules.begin();
                        }
                        else if(iter1Upper >= iter2Upper && iter1Lower <= iter2Lower)
                        {
                            rules.erase(iter2);
                            iter2 = rules.begin();
                            iter1 = rules.begin();
                        }
                        else if(iter1Upper <= iter2Upper && iter1Lower >= iter2Upper)
                        {
                            rules.erase(iter1);
                            iter1 = rules.begin();
                            iter2 = rules.begin();
                        }
                        
                        else if ((iter1Upper+1) == iter2Lower)
                        {
                            iter1Upper.GenericSet(Field::ip4Upper, iter2Upper);
                            rules.erase(iter2);
                            iter2 = rules.begin();
                            iter1 = rules.begin();
                        }
                        else if((iter1Lower - 1) == iter2Upper)
                        {
                            iter1Upper.GenericSet(Field::ip4Lower, iter2Lower);
                            rules.erase(iter2);
                            iter2 = rules.begin();
                            iter1 = rules.begin();
                        }
                     }
        }
    }
}

vector<GroupedRule> AdminMachine::rebuildRules(vector<vector<GroupedRule>>& rules)
{
    if(rules.empty())
    {
        cout << "No rules in the grouped by priority vectors of admin machine." << endl;
        return NULL;
    }
    else
    {
        vector<GroupedRule> returnVec;
        
        auto iter = rules.begin();
        
        while(iter != rules.end())
        {
            returnVec.insert(returnVec.end(), (*iter).begin(), (*iter).end());
        }
        rules.clear();
        return tempVec;
    }
}

void AdminMachine::removeCopies(vector<GroupedRule>& rules)
{
    if(rules.empty())
    {
        cout << "No rules in remove copies called in AdminMachine." << endl;
    }
    auto outerIt = rules.begin();
    
    auto innerIt = rules.begin();
    
    while(outerIt != rules.end())
    {
        while(innerIt != rules.end())
        {
            if(innerIt == outerIt)
            {
                ++innerIt;
            }
            else
            {
                if((*innerIt) == (*outerIt))
                {
                    rules.erase(innerIt);
                }
                else ++innerIt;
            }
        }
        ++outerIt;
        innerIt = rules.begin();
    }
}

bool AdminMachine::deleteRule(GroupedRule& rule)//Might also need to consider a multi delete function
{
    if(rules.empty())
    {
        cout << "Error: no rules contained in Admin machine rule file, or file not instanitiated into memory." << endl;
        return false;
    }
    
    else
    {
        auto iter = rules.begin();
        while(iter != rules.end())
        {
            if((*iter) == rule)
            {
                rules.erase(iter);
                return true;
            }
            else ++iter;
        }
    }
}