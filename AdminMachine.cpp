#include "AdminMachine.h"
//Lekker
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
	
	XMLParserOut out;
    string username = "Admin";
    out.parseOutGroupedRules(inoutRules, username);

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
        if(_rule.returnDirection() == Direction::in)
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
            outRules = rebuildRules(tempVec);
			removeCopies(outRules);
            return true;
        }
    }
}

vector<vector<GroupedRule>> AdminMachine::groupByPriority(vector<GroupedRule>& _rules)
{
    if(_rules.empty())
    {
		vector<vector<GroupedRule>> nullVec;
        cout << "The vector you're trying to group by priorty is empty." << endl;
        return nullVec;
    }
    else
    {
        vector<vector<GroupedRule>> returnVec;
        returnVec.clear();
        while(!_rules.empty())
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
            tempVec.clear(); //Need to check whether this deletes everything in returnVec?
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
    //GroupedRule temp = (*iter);
    while(iter1 != rules.end())
    {
        while(iter2 != rules.end())
        {
            if(iter1 == iter2)
            {
                ++iter2;
            }
            else if ((iter1)->GenericReturn(Field::protocolUpper) == (iter2)->GenericReturn(Field::protocolUpper) &&
                     (iter1)->GenericReturn(Field::protocolLower) == (iter2)->GenericReturn(Field::protocolLower) &&
                     (iter1)->GenericReturn(Field::ip1Upper) == (iter2)->GenericReturn(Field::ip1Upper) &&
                     (iter1)->GenericReturn(Field::ip1Lower) == (iter2)->GenericReturn(Field::ip1Lower) &&
                     (iter1)->GenericReturn(Field::ip2Upper) == (iter2)->GenericReturn(Field::ip2Upper) &&
                     (iter1)->GenericReturn(Field::ip2Lower) == (iter2)->GenericReturn(Field::ip2Lower) &&
                     (iter1)->GenericReturn(Field::ip3Upper) == (iter2)->GenericReturn(Field::ip3Upper) &&
                     (iter1)->GenericReturn(Field::ip3Lower) == (iter2)->GenericReturn(Field::ip3Lower) &&
                     (iter1)->GenericReturn(Field::srcportstart) == (iter2)->GenericReturn(Field::srcportstart) &&
                     (iter1)->GenericReturn(Field::srcportend) == (iter2)->GenericReturn(Field::srcportend) &&
                     (iter1)->GenericReturn(Field::dstportstart) == (iter2)->GenericReturn(Field::dstportstart) &&
                     (iter1)->GenericReturn(Field::dstportend) == (iter2)->GenericReturn(Field::dstportend))
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
                            iter1->GenericSet(Field::ip4Lower, iter2Lower);
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
                            iter1->GenericSet(Field::ip4Upper, iter2Upper);
                            rules.erase(iter2);
                            iter2 = rules.begin();
                            iter1 = rules.begin();
                        }
                        else if((iter1Lower - 1) == iter2Upper)
                        {
                            iter1->GenericSet(Field::ip4Lower, iter2Lower);
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
		vector<GroupedRule> nullVec;
        cout << "No rules in the grouped by priority vectors of admin machine." << endl;
        return nullVec;;
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
        return returnVec;
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
            if(groupedRuleEquivalence((*innerIt),(*outerIt)))
            {
                ++innerIt;
            }
            else
            {
                if(groupedRuleEquivalence((*innerIt),(*outerIt)))
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
	vector<GroupedRule>::iterator iterBegin;
	vector<GroupedRule>::iterator iterEnd;
	
	if(rule.returnDirection() == Direction::in)
	{
		if(inRules.empty())
		{
			cout << "Error: no rules contained in Admin machine rule file, or file not instanitiated into memory." << endl;
            return false;
		}
		else
		{
			iterBegin == inRules.begin();
			iterEnd == inRules.end();
		}
	}
	else
	{
		if(outRules.empty())
		{
			cout << "Error: no rules contained in Admin machine rule file, or file not instanitiated into memory." << endl;
            return false;
		}
		else
		{
			iterBegin == outRules.begin();
			iterEnd == outRules.end();
		}
	}

        while(iterBegin != iterEnd)
        {
            if(groupedRuleEquivalence((*iterBegin),rule))
            {
				if(rule.returnDirection()== Direction::in)
				{
					 inRules.erase(iterBegin);
				}
                else
				{
					outRules.erase(iterBegin);
				}
				return true;
            }
            else ++iterBegin;
        }
		
		return false;
}

bool AdminMachine::groupedRuleEquivalence(GroupedRule& rule1, GroupedRule& rule2)
{
	if((rule1).GenericReturn(Field::protocolUpper) == (rule2).GenericReturn(Field::protocolUpper) &&
                     (rule1).GenericReturn(Field::protocolLower) == (rule2).GenericReturn(Field::protocolLower) &&
                     (rule1).GenericReturn(Field::ip1Upper) == (rule2).GenericReturn(Field::ip1Upper) &&
                     (rule1).GenericReturn(Field::ip1Lower) == (rule2).GenericReturn(Field::ip1Lower) &&
                     (rule1).GenericReturn(Field::ip2Upper) == (rule2).GenericReturn(Field::ip2Upper) &&
                     (rule1).GenericReturn(Field::ip2Lower) == (rule2).GenericReturn(Field::ip2Lower) &&
                     (rule1).GenericReturn(Field::ip3Upper) == (rule2).GenericReturn(Field::ip3Upper) &&
                     (rule1).GenericReturn(Field::ip4Upper) == (rule2).GenericReturn(Field::ip4Upper) &&
                     (rule1).GenericReturn(Field::ip3Lower) == (rule2).GenericReturn(Field::ip3Lower) &&
                     (rule1).GenericReturn(Field::ip4Lower) == (rule2).GenericReturn(Field::ip4Lower) &&
                     (rule1).returnDirection() == (rule2).returnDirection()&&
                     (rule1).returnPriority() == (rule2).returnPriority()&&
                     (rule1).GenericReturn(Field::srcportstart) == (rule2).GenericReturn(Field::srcportstart) &&
                     (rule1).GenericReturn(Field::srcportend) == (rule2).GenericReturn(Field::srcportend) &&
                     (rule1).GenericReturn(Field::dstportstart) == (rule2).GenericReturn(Field::dstportstart) &&
                     (rule1).GenericReturn(Field::dstportend) == (rule2).GenericReturn(Field::dstportend))
					 {
						 return true;
					 }
					 else
					 {
						 return false;
					 }
}