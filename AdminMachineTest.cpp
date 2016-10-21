#include <iostream>

#include "AdminMachine.h"
#include "UserMachine.h"
#include "XMLParserOut.h"
#include "GroupedRule.h"

using namespace std;

int main()
{
    GroupedRule one(Protocol::tcp, 80,80,80,80,192,168,1,11,500,Direction::out,Action::accept);
    GroupedRule two(Protocol::tcp, 80,89,80,80,10,10,1,2,500,Direction::in,Action::accept);
    GroupedRule three(Protocol::tcp, 80,80,80,80,10000,1000,100,1,500,Direction::in,Action::accept);
//    
//    one.GenericSet(Field::ip4Lower, 16);
//    one.GenericSet(Field::ip4Upper, 19);
//    
    two.GenericSet(Field::ip4Lower, 1);
    two.GenericSet(Field::ip4Upper, 8);
    
    three.GenericSet(Field::ip4Lower, 1);
    three.GenericSet(Field::ip4Upper, 8);
    
	
	AdminMachine admin;
	
	admin.deleteRule(one);
//	string username = "/home/tyron/user";
//	
//	UserMachine user(username);
	
	//user.addRule(one);
	


	return 0;
	
}