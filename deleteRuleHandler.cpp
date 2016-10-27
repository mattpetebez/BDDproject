#include <fstream>
#include <iostream>
#include <vector>

#include "GroupedRule.h"
#include "XMLParserIn.h"
#include "HTMLBuilder.h"


using namespace std;

enum class returnVal
{
    noArgs = 1,
    NoUser,
    incorrectPassword,
    noUserFile,
    success
};
int main(int argc, char* argv[])
{
    //First need to check if username and password match
    ofstream errorLog;
    errorLog.open("/usr/lib/cgi-bin/errorLogDeleteRule");
    
    if(argc != 1)
    {
        cout << "No arguments passed to function." << endl;
        errorLog.close();
        return (int)returnVal::noArgs;
    }
    else
    {
        string username, password;
        username = argv[1];
        password = argv[2];
        
        ifstream infile;
        infile.open("/usr/lib/cgi-bin/Userlist");
        {
            if(!infile)
            {
                cout << "No Userlist file to read username and password from." << endl;
                errorLog.close();
                return (int)returnVal::noUserFile;
            }
            else
            {
                cout << "We are in file motherfucker." << endl;
                string _username, _password, _priority;
                bool foundUser = false;
                bool correctPassword = false;
                while(!infile.eof())
                {
                    infile >> _username >> _priority >> _password;
                    if(username == _username)
                    {
                        foundUser = true;
                        cout << _username << " " << _password << endl;
                        if(password == _password)
                        {
                            correctPassword = true;
                        }
                        break;
                    }
                }
                
                if(!foundUser)
                {
                    cout << "User does not exist." << endl;
                    errorLog.close();
                    return (int)returnVal::NoUser;
                }
                else
                {
                    if(!correctPassword )
                    {
                        cout << "Incorrect password used." << endl;
                    }
                    else 
                    {
                        cout << "Username: " << username << " Password: " << password << endl;
                        //Now need to build html containing username
                        
                        vector<GroupedRule> inRules, outRules;
                        string filename = "/usr/lib/cgi-bin/"+username+"-Rules-File.xml";
                        XMLParserIn inparser(filename);
                        inparser.buildInOutRules(inRules, outRules);
                        vector<GroupedRule> allRules = inRules;
                        allRules.insert(allRules.end(), outRules.begin(), outRules.end());
                        if(allRules.empty())
                        {
                            errorLog << "Rules file for user "+username+" is empty. cannot build rules." << endl;
                            errorLog.close();

                            return -1;
                        }
                        else
                        {
                            cout << "In htmlbuilder part." << endl;
                            HTMLBuilder deleteRulesPage(username, HTMLType::deleteRule, allRules);
                            deleteRulesPage.buildHTML();
                            cout << "Built the html." << endl;
                            return (int)returnVal::success;
                        }
                    }
                }
            }
        }
    }
}