#include <iostream>
#include <fstream>
#include <vector>
#include "XMLParserIn.h"
#include "GroupedRule.h"
#include "HTMLBuilder.h"
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
    if(argc == 1)
    {
        return (int)response::noArgs;
    }
    
    else
    {
        

        string username = argv[1];
        string password = argv[2];
        
        ifstream infile;
        infile.open("Userlist");
        if(!infile)
        {
            return (int)response::noUserListFile;
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
                XMLParserIn parserIn(userFile);
                vector<GroupedRule> in, out;
                
                parserIn.buildInOutRules(in, out);
                infile.close();
                vector<GroupedRule> temp = in;
                temp.insert(temp.end(), out.begin(), out.end());
                
                HTMLBuilder builder(username, HTMLType::viewFileRules, temp);
                builder.buildHTML();
                return (int)response::builtRulesSuccessfully;
            }
        }
    }
}