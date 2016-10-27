#include "UserMachine.h"

UserMachine::UserMachine(string& _username)
{
    username = _username;
    string UserRulesFile = username+"-Rules-File.xml";
    XMLParserIn inparser(UserRulesFile);
    inparser.buildInOutRules(inRules, outRules);
}

UserMachine::~UserMachine()
{
    vector<GroupedRule> inoutRules;
    if(!inRules.empty())
    {
        inoutRules.insert(inoutRules.end(), inRules.begin(), inRules.end());
    }
    if(!outRules.empty())
    {
        vector<GroupedRule> temp;
        for(auto i : outRules)
        {
            i.setDirection(Direction::out);
            temp.push_back(i);
            
        }
        inoutRules.insert(inoutRules.end(),temp.begin(),temp.end());
    }
	string UserRulesFile = username+"-Rules-File.xml";

	XMLParserOut out;
    out.parseOutGroupedRules(inoutRules, username);
}

bool UserMachine::addRule(vector<GroupedRule>& _rule)
{
	
	
    if(_rule.at(0).returnDirection() == Direction::in)
    {
		for(auto i: _rule)
		{
			if(inRules.empty() && i.returnActionEnum() == Action::deny)
			{
				return false;
			}
			else
			{
				RangeHelper helper;
				vector<GroupedRule> expandedRequestedRule = helper.returnRangedRules(i);
				for(auto k: expandedRequestedRule)
				{
					vector<string> temp = k.returnRangedBinRule();
					for(auto j: temp)
					{
						GroupedRule tempGrule(i.returnDirection(), j, i.returnPriority(), i.returnActionEnum());
						inRules.push_back(tempGrule);
					}
					temp.clear();
				}
			}
		}
				BDDBuilder builder(inRules);
				if(builder.buildBDD())
				{
					RuleReturner returner(builder.returnHead(), Direction::in);
					vector<GroupedRule> temp;
					temp = returner.returnRules();
					inRules = temp;
					GroupedRuleSorter sorter(inRules);
					inRules = sorter.sortRules();
				}
				else
				{
					inRules.clear();
				}
				
				return true;
	}
	
    else if(_rule.at(0).returnDirection() == Direction::out)
    {
		for(auto i: _rule)
		{
			if(outRules.empty() && i.returnActionEnum() == Action::deny)
			{
				return false;
			}
			else
			{
				RangeHelper helper;
				vector<GroupedRule> expandedRequestedRule = helper.returnRangedRules(i);
				for(auto k: expandedRequestedRule)
				{
					vector<string> temp = k.returnRangedBinRule();
					for(auto j: temp)
					{
						GroupedRule tempGrule(i.returnDirection(), j, i.returnPriority(), i.returnActionEnum());
						outRules.push_back(tempGrule);
					}
					temp.clear();
				}
			}
		}
				BDDBuilder builder(outRules);
				if(builder.buildBDD())
				{
					RuleReturner returner(builder.returnHead(), Direction::in);
					vector<GroupedRule> temp;
					temp = returner.returnRules();
					outRules = temp;
					GroupedRuleSorter sorter(outRules);
					outRules = sorter.sortRules();
				}
				else
				{
					outRules.clear();
				}
    }
    return true;
}

bool UserMachine::deleteRule(GroupedRule& rule)//Might also need to consider a multi delete function
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
				cout<<"true equal"<<endl;
				
				if(rule.returnDirection()== Direction::in)
				{
					cout<<"true in"<<endl;
					inRules.erase(iterBegin);
				}
                else
				{
					cout<<"true out"<<endl;
					outRules.erase(iterBegin);
				}
				return true;
            }
            else ++iterBegin;
        }
		
		return false;
}

bool UserMachine::groupedRuleEquivalence(GroupedRule rule1, GroupedRule rule2)
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