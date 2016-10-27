#include <iostream>
#include <vector>
#include <fstream>

#include "GroupedRule.h"
#include "XMLParserIn.h"
#include "XMLParserOut.h"

using namespace std;

int main(int argc, char* argv[])
{
    //groupedrulenumber=7&Larry=Submit
    ofstream errorLog;
    errorLog.open("/usr/lib/cgi-bin/deleteRuleFinalErrorLog");
    
    if(argc != 3)
    {
        errorLog << "No arguments or incorrect arguments passed:\nReceived "<< argc << " arguments, as seen below:" << endl;
        for(int i = 0; i <= argc; i++)
        {
            errorLog << argv[i] << " ";
        }
        errorLog << endl;
        errorLog.close();
        return 0;
    }
    else
    {
        string user = argv[1];
        string deleteIndex = argv[2];
        string filename = "/usr/lib/cgi-bin/"+user+"-Rules-File.xml";
        vector<GroupedRule> inRule, outRule, allRules;
        XMLParserIn parserin(filename);
        parserin.buildInOutRules(inRule, outRule);
        allRules = inRule;
        allRules.insert(allRules.end(), outRule.begin(), outRule.end());
        
        if(outRule.empty())
        {
            errorLog << "No grouped rules to delete from." << endl;
            errorLog.close();
            return 0;
        }
        else
        {
            int deleteIndexInt = atoi(deleteIndex.c_str());
            deleteIndexInt -= 1;
            
            auto it = allRules.begin();
            for(int i = 0; i <= deleteIndexInt; i++)
            {
                ++it;
            }
            cout << "Selected the rule: ";
            it->debugReturnEnglishRule();
            
            allRules.erase(it);
            cout << "Got to xml parser out" << endl;
            XMLParserOut parserout;
            parserout.parseOutGroupedRules(allRules, user);
        }
    }
}
    
