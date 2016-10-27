#include "HTMLBuilder.h"

HTMLBuilder::HTMLBuilder(string& _user, HTMLType _type, vector<GroupedRule> _rules)
{
    user = _user;
    type = _type;
    rules = _rules;
}

HTMLBuilder::~HTMLBuilder()
{
}

HTMLBuilder::HTMLBuilder()
{
	
}

void HTMLBuilder::buildHTML()
{
    switch(type)
    {
        case HTMLType::viewActualRules:
        {
            printActualRules();
            break;
        }
        case HTMLType::viewFileRules:
        {
            printFileRules();
        }
    }    
}

void HTMLBuilder::printFileRules()
{
    string html = "<!DOCTYPE html>\n<html>\n<title>"+user+" ViewFileRules</title>\n<h1>\nHello " + user
    +": your rules (as you have selected with no automatic redundancy checks) are as follows:\n</h1>\n\n<body>";
    
    for(auto i: rules)
    {
        html+= "<p>"+i.returnHTMLRule()+"</p>\n";
    }
    html+= "</body>\n\n</html>";
    
    ofstream outfile;
    outfile.open("/var/www/html/UserRulesFiles/"+user+"-FileRules.html");
    outfile << html;
    outfile.close();
}

void HTMLBuilder::printActualRules()
{
    string html = "<!DOCTYPE html>\n<html>\n<head>\n<h1>\nHello " + user
    +": your rules with all redundancy removed (actual rules used by the filter) are as follows:\n</h1>\n</head>\n\n<body>";
    
    for(auto i: rules)
    {
        html+= "<p>"+i.returnHTMLRule()+"</p>\n";
    }
    html+= "</body>\n\n</html>";
    
    ofstream outfile;
    outfile.open("/var/www/html/UserRulesFiles/"+user+"-ActualRules.html");
    outfile << html;
    outfile.close();
}

void HTMLBuilder::allowedRules(vector<GroupedRule> _allowedRules, string _user)
{
	string html = "<!DOCTYPE html>\n<html>\n<head>\n<h1>\nHello " + _user
    +": The rules successfully added to your rule list are \n</h1>\n</head>\n\n<body>";
    if(!_allowedRules.empty())
	{
		for(auto i: _allowedRules)
		{
			html+= "<p>"+i.returnHTMLRule()+"</p>\n";
		}
	}
	else
	{
		html+= "<p>No rules were allowed</p>\n";
	}
    html+= "</body>\n\n</html>";
    
    ofstream outfile;
    outfile.open("/var/www/html/"+_user+"-AllowedRules.html");
    outfile << html;
    outfile.close();
}