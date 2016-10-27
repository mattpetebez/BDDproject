#include <iostream>
#include <fstream>
#include <vector>
#include "XMLParserIn.h"
#include "GroupedRule.h"
#include "UserMachine.h"
#include "AdminMachine.h"
#include "HTMLBuilder.h"
#include "string"
using namespace std;


enum class response
{
  builtRulesSuccessfully = 1,
  noArgs,
  incorrectPassword,
  noUser,
  noUserListFile
};

int main(int argc, char* argv[])
{
	HTMLBuilder builder; 
	
    if(argc == 1)
    {
        return (int)response::noArgs;
    }
    
    else
    {
        string username = argv[1];
        string password = argv[2];
        string dstportstart = argv[3];
		int dps = atoi(dstportstart.c_str());
        string dstportend = argv[4];
		int dpe = atoi(dstportend.c_str());
        string srcportstart = argv[5];
		int sps = atoi(srcportstart.c_str());
		string srcportend = argv[6];
		int spe = atoi(srcportend.c_str());
		
		string ipstart = argv[7];
		int ips1 = atoi(ipstart.c_str());		
		ipstart = argv[8];
		int ips2 = atoi(ipstart.c_str());
		ipstart = argv[9];
		int ips3 = atoi(ipstart.c_str());
		ipstart = argv[10];
		int ips4 = atoi(ipstart.c_str());
		
		string ipend = argv[11];
		int ipe1 = atoi(ipend.c_str());		
		ipend = argv[12];
		int ipe2 = atoi(ipend.c_str());
		ipend = argv[13];
		int ipe3 = atoi(ipend.c_str());
		ipend = argv[14];
		int ipe4 = atoi(ipend.c_str());
		
		string action = argv[15];
		Action act;
		if(action == "accept")
		{
			act = Action::accept;
		}
		else
		{
			act = Action::deny;
		}
		string priority = argv[16];
		int prior = atoi(priority.c_str());
		string direction = argv[17];
		Direction dir;
		if(direction == "in")
		{
			dir = Direction::in;
		}
		else
		{
			dir = Direction::out;
		}
		string protocol = argv[18];
		Protocol prot;
		if(protocol == "udp")
		{
			prot = Protocol::udp;
		}
		else if(protocol == "icmp")
		{
			prot = Protocol::icmp;
		}
		else if(protocol == "tcp")
		{
			prot = Protocol::tcp;
		}
		
		GroupedRule requestedRule(prot, sps, spe, dps, dpe,ips1,ips2,ips3,ips4, prior, dir, act);
		requestedRule.GenericSet(Field::ip4Lower,ips4);
		requestedRule.GenericSet(Field::ip4Upper,ipe4);

        ifstream infile;
        infile.open("/home/tyron/BDDproject/BDDproject/Userlist");
        if(!infile)
        {
            return (int)response::noUserListFile;
			cout<<"File not found"<<endl;
        }
        else
        {
            string _username, _password, _priority;
            bool userFound = false;
            bool correctPassword = false;
            while(!infile.eof())
            {
                infile >> _username >> _priority >> _password;
                if(username == _username)
                {
                    userFound = true;
                    if(password == password)
                    {
                        correctPassword = true;
                        break;
                    }
                }
            }
            if(!userFound)
            {
                return (int)response::noUser;
            }
            else if(userFound && !correctPassword)
            {
                return (int)response::incorrectPassword;
            }
            
            else 
            {
				
				cout<<"made user and admin"<<endl;
				AdminMachine admin;				
				if(username == "Admin" && password == _password)
				{
					admin.addRule(requestedRule);
					RangeHelper helper;
					vector<GroupedRule> expandedRequestedRule = helper.returnRangedRules(requestedRule);
					HTMLBuilder builder;
					builder.allowedRules(expandedRequestedRule, username);
				}
				else
				{
					UserMachine user(username);
					HTMLBuilder builder;
					if(requestedRule.returnActionEnum() == Action::accept)
					{
						vector<GroupedRule> temp = admin.ruleAllowed(username, password, requestedRule);
						vector<GroupedRule> temp2;
						if(!temp.empty())
						{
							user.addRule(temp);
							for(auto i: temp)
							{
								RangeHelper helper;
								vector<GroupedRule> expandedRequestedRule = helper.returnRangedRules(i);
								vector<GroupedRule> temp;
								for(auto k: expandedRequestedRule)
								{
									vector<string> tempstr = k.returnRangedBinRule();
									for(auto j: tempstr)
									{
										GroupedRule tempGrule(i.returnDirection(), j, i.returnPriority(), i.returnActionEnum());
										temp2.push_back(tempGrule);
									}
									tempstr.clear();
								}
							}
						
							builder.allowedRules(temp2, username);
						}
						else
						{
							vector<GroupedRule> emptyVec;
							builder.allowedRules(emptyVec, username);
							cout<<"no rules were allowed"<<endl;
						}
					}
						else
						{
							RangeHelper helper;
							vector<GroupedRule> expandedRequestedRule = helper.returnRangedRules(requestedRule);
							vector<GroupedRule> temp2;
							for(auto i: expandedRequestedRule)
							{
								vector<string> temp = i.returnRangedBinRule();
								for(auto j: temp)
								{
									GroupedRule tempGrule(requestedRule.returnDirection(), j, requestedRule.returnPriority(), requestedRule.returnActionEnum());
									temp2.push_back(tempGrule);
								}
								temp.clear();
							}
							builder.allowedRules(temp2, username);
							vector<GroupedRule> rr;
							rr.push_back(requestedRule);
							user.addRule(rr);
						}
				}
				
                return (int)response::builtRulesSuccessfully;
            }
        }
    }
}

