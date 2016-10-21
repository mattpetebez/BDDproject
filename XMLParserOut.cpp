#include "XMLParserOut.h"

XMLParserOut::XMLParserOut()
{
}

void XMLParserOut::parseOutGroupedRules(vector<GroupedRule> _rules, string& username)
{
    outRules = _rules;
    expandRangedRules();
    sortAscendingIP();
    sortIP(Field::ip4Upper, outRules);
    ruleCreater();
    printoutputRule(username);
}

void XMLParserOut::sortIP(Field field, vector<GroupedRule>& unsorted)
{
        for(auto m:unsorted)
        {
            GroupedRule temp = m;
            int j;
            int limit = unsorted.size();
            for(int i =0; i<limit; i++)
            {
                j=i;
                while(j>0 && unsorted[j].GenericReturn(field) < unsorted[j-1].GenericReturn(field))
                {
                    temp = unsorted[j];
                    unsorted[j]=unsorted[j-1];
                    unsorted[j-1]=temp;
                    j--;
                }
            }
        }

}

void XMLParserOut::expandRangedRules()
{
    vector<GroupedRule> tempVec1;
    vector<GroupedRule> tempVec2;
    auto it = outRules.begin();
    auto itEnd = outRules.end();
    while(it != itEnd)
    {
        if(it->isRanged())
        {
            RangeHelper ranger;
            tempVec2.clear();
            tempVec2 = ranger.returnRangedRules((*it));
            tempVec1.insert(tempVec1.end(), tempVec2.begin(), tempVec2.end());
            tempVec2.clear();
            it = outRules.erase(it);
            itEnd = outRules.end();
            if(it == itEnd)
            {
                break;
            }
        }
        
        else ++it;
    }
    outRules.insert(outRules.end(), tempVec1.begin(), tempVec1.end());
}

XMLParserOut::~XMLParserOut()
{
    
}

void XMLParserOut::ruleCreater()
{
    string wholerule = "";

    string ruleaction = "<rule action='accept'";
    
	string prior =" priority=";
    string priority="";
	string direct = " direction=";
 

	string endrule= "</rule>";
    string srcip = " srcipaddr=";
    string dstip =" dstipaddr=";
    string ip = "";
    string protocol="";

    string dstportstart = " dstportstart=";
    string dstportend = " dstportend=";
    string srcportstart = " srcportstart=";
    string srcportend =" srcportend=";

    /*
     *  <rule action='accept' direction='in' priority='400'>
        <tcp srcipaddr='196.44.24.27' dstipaddr='192.168.1.16' srcipmask='16' dstportstart='80' dstportend='100' srcportstart='80' srcportend='100'/>
        </rule>
     * iprange ??
     */
    vector<GroupedRule>::iterator iter = outRules.begin();
    
    while(iter != outRules.end())
    {
        GroupedRule currRule = (*iter);
		
		priority = prior + "'" +to_string(currRule.returnPriority())+"'";
        if(iter->GenericReturn(Field::ip1Upper) != MASKED_VALUE && iter->GenericReturn(Field::ip2Upper) != MASKED_VALUE
        && iter->GenericReturn(Field::ip3Upper) != MASKED_VALUE && iter->GenericReturn(Field::ip4Upper) != MASKED_VALUE)
        {
        ip = currRule.returnWholeIP();
        if(currRule.returnDirection() == Direction::in)
        {
            ip = srcip + ip;
        
            direct += "'in'";
            //cout<<"Direction "<<(int)currRule.returnDirection()<<endl;
        }
        else
        {
            ip = dstip + ip;
            direct += "'out'";
             //  cout<<"Direction "<<(int)currRule.returnDirection()<<endl;
        }
        }
        else
        {
           if(currRule.returnDirection() == Direction::in)
        {
            direct += "'in'";
        }
        else
        {
            direct += "'out'";
        } 
        }
        protocol=currRule.returnProt();
        
        string destportstart = "''";
        if(iter->GenericReturn(Field::dstportstart) != MASKED_VALUE)
        {
         destportstart = "'"+to_string(iter->GenericReturn(Field::dstportstart))+"'";//currRule.returnDestPort();
        }
        string destportend = "''";
        if(iter->GenericReturn(Field::dstportend) != MASKED_VALUE)
        {
         destportend = "'"+to_string(iter->GenericReturn(Field::dstportend))+"'";//no range implementation yet
        }
        string sourceportstart = "''"; 
        if(iter->GenericReturn(Field::srcportend) != MASKED_VALUE)
        {
         sourceportstart = "'"+to_string(iter->GenericReturn(Field::srcportend))+"'";//no range implementation yet
        }
        
        string sourceportend = "''";//no range implementation yet
        if(iter->GenericReturn(Field::srcportend) != MASKED_VALUE)
        {
        sourceportend = "'"+to_string(iter->GenericReturn(Field::srcportend))+"'";//no range implementation yet
        }
        
        wholerule = ruleaction+direct+priority+">\n<"+protocol+ip+dstportstart+destportstart
        +dstportend+destportend+srcportstart+sourceportstart+srcportend+sourceportend+"/"+">\n"+endrule;
        xmlrules.push_back(wholerule);
        
        direct = " direction=";
        ++iter;
    }
} 

void XMLParserOut::printoutputRule(string& username)
{
    ofstream xmlOutputRules("/home/tyron/" + username + "-rules.xml");
	if (xmlOutputRules.is_open())
	{
		xmlOutputRules << "<filter name='"+username+"-rules' chain='root'>\n";
        for(auto i: xmlrules)
        {
            xmlOutputRules <<"\t" << i << "\n";
        }
        xmlOutputRules << "<rule action='reject' direction='inout' priority='100'/>\n";
        xmlOutputRules << "</filter>";
		xmlOutputRules.close();
	}
    else cerr << "Could not open file!" << endl;
}

void XMLParserOut::sortAscendingIP()
{
    sortIP(Field::ip1Upper, outRules);
    vector<vector<GroupedRule>> ip1Vec;
    
    while(!outRules.empty())
    {
        vector<GroupedRule> tempVecIP123;
        auto it = outRules.begin();
        int ip1 = it->GenericReturn(Field::ip1Upper);
        int ip2 = it->GenericReturn(Field::ip2Upper);
        int ip3 = it->GenericReturn(Field::ip3Upper);
        while(it != outRules.end())
        {
            if(it->GenericReturn(Field::ip1Upper) == ip1 && it->GenericReturn(Field::ip2Upper) == ip2 && it->GenericReturn(Field::ip3Upper) == ip3)
            {
                GroupedRule tmpGrp = (*it);
                tempVecIP123.push_back(tmpGrp);
                outRules.erase(it);
            }
            else it++;
        }
        ip1Vec.push_back(tempVecIP123);
    }
    auto it1 = ip1Vec.begin();
    while(it1 != ip1Vec.end())
    {
        sortIP(Field::ip4Upper, (*it1));
        ++it1;
    }
    auto it2 = ip1Vec.begin();
    
    while(!ip1Vec.empty())
    {
        outRules.insert(outRules.end(), (*it2).begin(), (*it2).end());
        ip1Vec.erase(it2);
    }
}

//Lekker