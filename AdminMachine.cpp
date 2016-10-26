#include "AdminMachine.h"
//Lekker
AdminMachine::AdminMachine()
{
    string filename = "Admin-Rules-File.xml";
    XMLParserIn inparser(filename);
    inparser.buildInOutRules(inRules, outRules);
    reverse(inRules.begin(),inRules.end()); 
    reverse(outRules.begin(),outRules.begin());
}

AdminMachine::~AdminMachine()
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
	
//    

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
            //inRules.push_back(_rule);
            RangeHelper helper;
            vector<GroupedRule> expandedRequestedRule = helper.returnRangedRules(_rule);
            for(auto i: expandedRequestedRule)
            {
                vector<string> temp = i.returnRangedBinRule();
                for(auto j: temp)
                {
                    GroupedRule tempGrule(_rule.returnDirection(), j, _rule.returnPriority(), _rule.returnActionEnum());
                    inRules.push_back(tempGrule);
                }
                temp.clear();
            }
			//removeCopies(inRules);
            auto tempVec = groupByPriority(inRules);			
            removeRedundancy(tempVec);
            inRules = rebuildRules(tempVec);
            return true;
        }
        else 
        {
           // outRules.push_back(_rule);
			//removeCopies(outRules);
               RangeHelper helper;
               vector<GroupedRule> expandedRequestedRule = helper.returnRangedRules(_rule);
               for(auto i: expandedRequestedRule)
               {
                    vector<string> temp = i.returnRangedBinRule();
                    for(auto j: temp)
                    {
                        GroupedRule tempGrule(_rule.returnDirection(), j, _rule.returnPriority(), _rule.returnActionEnum());
                        outRules.push_back(tempGrule);
                    }
                    temp.clear();
            }
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

vector<GroupedRule> AdminMachine::ruleAllowed(string user, string password, GroupedRule _rule)
{
    ifstream infile;
    infile.open("Userlist");
    vector<GroupedRule> exceptedRules;
    if(!infile)
    {
        cout << "Error: userlist file not found in call AdminMachine, ruleAllowed." << endl;
        vector<GroupedRule> emptyVec;
        return emptyVec;
    }
    else
    {
        int priority;
        bool foundUser = false;
        string _user, _priority, _password;
        while(!infile.eof())
        {
            infile >> _user >> _priority >> _password;
            if(_user == user && password == _password)
            {
                priority = atoi(_priority.c_str());
                foundUser = true;
                break;
            }
        }
        
        if(!foundUser)
        {
            cout << "User name and password incorrect in AdminMachine, ruleAllowed call." << endl;
        }
        else
        {
			cout<<"Unexceptable about to be popultated"<<endl;
            vector<GroupedRule> UnExceptable;

            UnExceptable = populateUnExceptable(_rule.returnDirection(), priority);
			
			cout<<"Unexceptable popultated"<<endl;
			
            BDDnavigator navigator(_rule,UnExceptable);
						
            exceptedRules = navigator.returnExceptedRules();
            cout<<"Navigator finished"<<endl;
        }
        
        return exceptedRules;
    
//    BDDnavigator navigator(_rule, UnExceptable);
//    vector<GroupedRule> acceptedExceptions = navigator.returnExceptions();
//    BDDnavigator navigator();
//    acceptedExceptions = navigator.returnExceptions();
//    
//    cout<<"Your requested rule: "<<_rule<<endl;
//    cout<<"The accepted rules are as follows: "<<endl;
//    for(auto i: acceptedExceptions)
//    {
//        i.debugReturnEnglishRule();
//    }
//    
//    }
}
}

vector<GroupedRule> AdminMachine::populateUnExceptable(Direction _direction, int priority)
{
    vector<GroupedRule> temp;
    vector<GroupedRule> unallowable;
    
    if(_direction == Direction::in)
    {
        temp = inRules;
    }
    else
    {
        temp = outRules;
    }
    
    for(auto i: temp)
    {
        if(i.returnPriority() > priority)
        {
            unallowable.push_back(i);
        }
    }
    
    return unallowable;
}