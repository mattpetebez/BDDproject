#include <iostream>

#include "AdminMachine.h"
#include "UserMachine.h"
#include "XMLParserOut.h"
#include "GroupedRule.h"

using namespace std;

int main()
{
    GroupedRule one(Protocol::tcp, 80,80,80,80,196,44,24,35,500,Direction::in,Action::accept);
    GroupedRule two(Protocol::tcp, 80,89,80,80,10,10,1,2,500,Direction::in,Action::accept);
    GroupedRule three(Protocol::tcp, 80,80,80,80,10000,1000,100,1,500,Direction::in,Action::accept);
    
    one.GenericSet(Field::ip4Lower, 1);
    one.GenericSet(Field::ip4Upper, 100);
//    
//    two.GenericSet(Field::ip4Lower, 1);
//    two.GenericSet(Field::ip4Upper, 8);
//    
//    three.GenericSet(Field::ip4Lower, 1);
//    three.GenericSet(Field::ip4Upper, 8);
	
	AdminMachine admin;
	
	//admin.addRule(one);

//	string username = "/home/matt/Admin";
	string usern = "Larry";
	string password = "1234";
    vector<GroupedRule> temp;
	temp.push_back(one);
    UserMachine user(usern);
	//user.addRule(temp);
	if(one.returnActionEnum() == Action::accept)
	{
    vector<GroupedRule> temp2 = admin.ruleAllowed(usern, password, one);
    if(!temp2.empty())
    {
		cout<<"true"<<endl;
		user.addRule(temp2);
    }
    else
    {
        cout<<"no rules were allowed"<<endl;
	}
	}
	else
	{
		user.addRule(temp);
	}
	return 0;
	
}