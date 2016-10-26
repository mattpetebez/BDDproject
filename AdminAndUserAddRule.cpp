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
	cout<<"running"<<endl;
	HTMLBuilder builder; 
	
    if(argc == 1)
    {
		cout<<"Lekker man";
        return (int)response::noArgs;
    }
    
    else
    {
		cout<<"we are here"<<endl;
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
	
		requestedRule.debugReturnEnglishRule();
        ifstream infile;
        infile.open("Userlist");
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
                infile >> _username >> _password >> _priority;
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
                string userFile = username + "-Rules-File.xml";
                string adminFile = "Admin-Rules-File.xml";
				
				cout<<"made user and admin"<<endl;
				AdminMachine admin;
				
				
				UserMachine user(username);
				if(username == "Admin")
				{
					admin.addRule(requestedRule);
				}
				else
				{
					
					vector<GroupedRule> temp = admin.ruleAllowed(username, password, requestedRule);
					if(!temp.empty())
					{
						user.addRule(temp);
						XMLParserIn parser(username);
						vector<GroupedRule> inRules,outRules;
						parser.buildInOutRules(inRules, outRules);
						inRules.insert(inRules.end(), outRules.begin(), outRules.end());
						builder.allowedRules(inRules, username);
						
					}
					else
					{
						builder.allowedRules(temp,username);
					}
				}
				
                return (int)response::builtRulesSuccessfully;
            }
        }
    }
}

