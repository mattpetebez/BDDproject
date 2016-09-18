#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int main(int argc, char **argv)
{
	
	string user,password,sourceip,destip,sourceport,destport,inout,protocol,priority,acceptreject;
/*	cout<<"Please enter User"<< endl;
	cin >> user;*/
/*	cout<<"Please enter Source IP address"<< endl;
	cin >> sourceip;*/
/*	cout<<"Please enter Destination IP address"<< endl;
	cin >> destip;*/
/*	cout<<"Please enter Source Port"<< endl;
	cin >> sourceport;*/
/*	cout<<"Please enter Destination Port"<< endl;
	cin >> destport;
	cout<<"Please enter Protocol"<< endl;
	cin >> protocol;
	cout<<"Please enter whether the traffic is incoming or outgoing or both"<< endl;
	cin >> inout;
	cout<<"Please enter the rule's Priority"<< endl;
	cin >> protocol;
	cout<<"Please enter if the traffic must be accepted or rejected"<< endl;
	cin >> acceptreject;*/
	string filelocation ="/home/tyron/Documents/BDD/RuleInserter/larry-rules.xml";
	acceptreject ="accept";
	inout ="in";
	protocol = "tcp";
	destport = "80";
	priority ="200";
	string ruleaction = " <rule action=";
	string singlequote = "'";
	string prior = " priority=";
	string direction = " direction=";
	string nextline = "\n";
	string portstart = "<tcp dstportstart=";
	string endtag = "/>";
	string endarr =">";
	string endrule= " </rule>";
	string xmlrule = ruleaction+singlequote+acceptreject+singlequote+direction+singlequote+inout+singlequote+prior+singlequote+
					 priority+singlequote+endarr+nextline+portstart+singlequote+destport+singlequote+endtag+nextline+endrule;
	string filter = "</filter>";
	string existingrules;
	string newrules;
	ifstream infile;
	infile.open ("/home/tyron/Documents/BDD/RuleInserter/larry-rules.xml");
        while(getline(infile,existingrules)) // To get you all the lines.
        { // Saves the line in STRING.
			if(existingrules!="</filter>")
			{
	        newrules =newrules +existingrules+nextline; // Prints our STRING.
			}
        }
	infile.close();
  
	newrules = newrules+xmlrule+nextline+filter;
	//cout << newrules;
    ofstream myfile ("/home/tyron/Documents/BDD/RuleInserter/larry-rules.xml");
	if (myfile.is_open())
	{
		myfile << newrules;
		myfile.close();
	}
	else cout << "Unable to open file";
  
	return 0;
}
