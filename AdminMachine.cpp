#include "AdminMachine.h"
//Lekker
AdminMachine::AdminMachine()
{
    string filename = "/home/tyron/Admin-Rules.xml";
    XMLParserIn inparser(filename);
    inparser.buildInOutRules(inRules, outRules);
    reverse(inRules.begin(),inRules.end()); 
    reverse(outRules.begin(),outRules.begin());
}

AdminMachine::~AdminMachine()
{
    vector<GroupedRule> inoutRules;
    inoutRules.insert(inoutRules.end(), inRules.begin(), inRules.end());
	vector<GroupedRule> temp;
	for(auto i : outRules)
	{
		i.setDirection(Direction::out);
		temp.push_back(i);
	}
    inoutRules.insert(inoutRules.end(),temp.begin(),temp.end());

	XMLParserOut out;
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

			//removeCopies(inRules);
            auto tempVec = groupByPriority(inRules);			
            removeRedundancy(tempVec);
            inRules = rebuildRules(tempVec);
            return true;
        }
        else 
        {
            outRules.push_back(_rule);
			//removeCopies(outRules);
            auto tempVec = groupByPriority(outRules);
            removeRedundancy(tempVec);
            outRules = rebuildRules(tempVec);	
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
        reduceUsingBDD((*iter));
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
               
/*void AdminMachine::reduceByIP(vector<GroupedRule>& rules)
{
	cout<<"rules.size(): "<<rules.size()<<endl;
    auto iter1 = rules.begin();
    auto iter2 = rules.begin();
    while(iter1 != rules.end() && rules.size()>1)
    {
        while(iter2 != rules.end())
        {
            if(iter1 == iter2)
            {
				cout<<"iter1 == iter2"<<endl;
                ++iter2;
            }
             if ((iter1)->GenericReturn(Field::protocolUpper) == (iter2)->GenericReturn(Field::protocolUpper) &&
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
//						cout<<"iter1Upper: "<<iter1Upper<<endl;
//						cout<<"iter1Lower: "<<iter1Lower<<endl;
//						cout<<"iter2Upper: "<<iter2Upper<<endl;
//						cout<<"iter2Lower: "<<iter2Lower<<endl;
                        if(iter1Upper >= iter2Lower && iter1Lower <= iter2Upper)
                        {
							cout<<"set ip4Upper"<<endl;
							iter2->GenericSet(Field::ip4Upper, iter2Upper);
                            //rules.erase(iter1);
                            iter2 = rules.begin();
                            iter1 = rules.begin();
							++iter2;
							
                        }
                        
                        else if(iter2Lower <= iter1Upper && iter2Lower >= iter2Lower)
                        {
							cout<<"set ip4Lower"<<endl;
                            iter1->GenericSet(Field::ip4Lower, iter2Lower);
                            rules.erase(iter2);
                            iter2 = rules.begin();
                            iter1 = rules.begin();
                        }
                        else if(iter1Upper >= iter2Upper && iter1Lower <= iter2Lower)
                        {
							cout<<"erase only one"<<endl;
                            rules.erase(iter2);
                            iter2 = rules.begin();
                            iter1 = rules.begin();
                        }
                        else if(iter1Upper <= iter2Upper && iter1Lower >= iter2Upper)
                        {
							cout<<"erase only two"<<endl;
                            rules.erase(iter1);
                            iter1 = rules.begin();
                            iter2 = rules.begin();
                        }
                        
                        else if ((iter1Upper+1) == iter2Lower)
                        {
							cout<<"set ip4Upper for consecutive range"<<endl;
                            iter1->GenericSet(Field::ip4Upper, iter2Upper);
                            rules.erase(iter2);
                            iter2 = rules.begin();
                            iter1 = rules.begin();
                        }
                        else if((iter1Lower - 1) == iter2Upper)
                        {
							cout<<"set ip4lower for consecutive range"<<endl;
                            iter1->GenericSet(Field::ip4Lower, iter2Lower);
                            rules.erase(iter2);
                            iter2 = rules.begin();
                            iter1 = rules.begin();
                        }
                     }
					 else
					 {
						 ++iter2;
						 cout<<"iter2 increment"<<endl;
					 }
		}
		++iter1;
		cout<<"iter1 increment"<<endl;
    }
	cout<<"Size before print loop: "<<rules.size()<<endl;
}*/

void AdminMachine::reduceUsingBDD(vector<GroupedRule>& rules)
{
	if(rules.empty())
    {
		vector<GroupedRule> nullVec;
        cout << "No rules in the grouped by priority vectors of admin machine." << endl;
        return;
    }
	else
	{
		BDDBuilder BDDin(rules);
		BDDin.buildBDD();
		Direction direction = rules.at(0).returnDirection();
		RuleReturner inRuleReturner(BDDin.returnHead(), Direction::in, rules.at(0).returnPriority());
		rules = inRuleReturner.returnRules();
	}
}
vector<GroupedRule> AdminMachine::rebuildRules(vector<vector<GroupedRule>>& rules)
{
    if(rules.empty())
    {
		vector<GroupedRule> nullVec;
        cout << "No rules in the grouped by priority vectors of admin machine." << endl;
        return nullVec;
    }
    else
    {
        vector<GroupedRule> returnVec;
        
        auto iter = rules.begin();
        
        while(iter != rules.end())
        {
            returnVec.insert(returnVec.end(), (*iter).begin(), (*iter).end());
			++iter;
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
            if(innerIt == outerIt)
            {
                ++innerIt;
            }
            else
            {
                if(groupedRuleEquivalence((*innerIt),(*outerIt)))
                {
                    rules.erase(innerIt);
					innerIt = rules.begin();
					outerIt = rules.begin();
                }
                else 
				{
						++innerIt;
				}
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
			iterBegin = inRules.begin();
			iterEnd = inRules.end();
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
			
			iterBegin = outRules.begin();
			iterEnd = outRules.end();
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

bool AdminMachine::groupedRuleEquivalence(GroupedRule rule1, GroupedRule rule2)
{
/*	cout<<(rule1).GenericReturn(Field::protocolUpper)<<" == "<<(rule2).GenericReturn(Field::protocolUpper)<<endl<<
				    (rule1).GenericReturn(Field::protocolLower) <<
				   " == "<< (rule2).GenericReturn(Field::protocolLower)<<endl<<
                     (rule1).GenericReturn(Field::ip1Upper)<< " == " <<(rule2).GenericReturn(Field::ip1Upper) <<endl<<
                     (rule1).GenericReturn(Field::ip1Lower)<< " == " << (rule2).GenericReturn(Field::ip1Lower) <<endl<<
                     (rule1).GenericReturn(Field::ip2Upper) << " == " << (rule2).GenericReturn(Field::ip2Upper) <<endl<<
                     (rule1).GenericReturn(Field::ip2Lower) << " == " << (rule2).GenericReturn(Field::ip2Lower) <<endl<<
                     (rule1).GenericReturn(Field::ip3Upper) << " == " << (rule2).GenericReturn(Field::ip3Upper) <<endl<<
                     (rule1).GenericReturn(Field::ip4Upper) << " == " << (rule2).GenericReturn(Field::ip4Upper) <<endl<<
                     (rule1).GenericReturn(Field::ip3Lower) << " == " << (rule2).GenericReturn(Field::ip3Lower) <<endl<<
                     (rule1).GenericReturn(Field::ip4Lower) << " == " << (rule2).GenericReturn(Field::ip4Lower) <<endl<<
                     (int)(rule1).returnDirection() << " == " << (int)(rule2).returnDirection() <<endl<<
                     (rule1).returnPriority() << " == " << (rule2).returnPriority() <<endl<<
                     (rule1).GenericReturn(Field::srcportstart) << " == " << (rule2).GenericReturn(Field::srcportstart) <<endl<<
                     (rule1).GenericReturn(Field::srcportend) << " == " << (rule2).GenericReturn(Field::srcportend) <<endl<<
                     (rule1).GenericReturn(Field::dstportstart) << " == " << (rule2).GenericReturn(Field::dstportstart) <<endl<<
                     (rule1).GenericReturn(Field::dstportend) << " == " << (rule2).GenericReturn(Field::dstportend) <<endl<<endl;*/
					 
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

bool AdminMachine::ruleAllowed(string user, string password, GroupedRule _rule)
{
	int priority;
	vector<GroupedRule>::iterator iterBegin;
	vector<GroupedRule>::iterator iterEnd;
	RangeHelper helper;
	
	if(username == "Barry")
	{
		priority = BarryPriorityLevel;
	}
	else if(username == "Larry")
	{
		priority = LarryPriorityLevel;
	}
	
	
	if(_rule.returnDirection() == Direction::in)
	{
		iterBegin = inRules.begin();
		iterEnd = inRules.end();
	}
	else
	{
		iterBegin = outRules.begin();
		iterEnd = outRules.end();
	}
	
	while(iterBegin != iterEnd)
	{
		if(iterBegin->returnPriority() > priority)
		{
			if(groupedRuleEquivalence((*iterBegin),_rule))
			{
				return false;
			}
		}
		
		++iterBegin;
	}
		return true;
	}