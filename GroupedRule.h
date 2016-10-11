#ifndef GROUPEDRULE_H
#define GROUPEDRULE_H
#include <iostream>
#include <string>
#include <vector>

#include "binDecConverter.h"

#define DEFAULT_PRIORITY 500
enum class Accept_Deny
{
    accept,
    deny
};

enum class Direction
{
    in,
    out
};
enum class Protocol
{
    tcp=1,
    udp,
    icmp
};
/*struct BinGroupedRule{
    BinGroupedRule();
 BinGroupedRule(Accept_Deny _accept_deny, int _priority, Direction _direction, string _binRule);
 int returnPriority(); 
private:
  Accept_Deny accept_deny;
  Direction direction;
  int priority;
  string binRule;
};*/

using namespace std;

class GroupedRule
{
public:
    GroupedRule();//Not sure if needed
    ~GroupedRule();
    
    GroupedRule(Protocol _protocol, int _srcPortStart,int _srcPortEnd,int _destPortStart,int _destPortEnd,
    int _ip1,int _ip2,int _ip3, int _ip4,int _priority, Direction _direction, Accept_Deny accept_deny); //Used for parser in
    
    GroupedRule(Direction _direction, string _binRule);//Needed for parser out
    
    GroupedRule(Accept_Deny accept_deny, int _priority, Direction _direction, string wholeBinRule);//Not sure of needed;
    
    const Direction returnDirection();
    const int returnPriority();
    const string returnProt();
    const int returnSrcPort();
    const int returnDestPort();
    const int returnSrcPortEnd();
    const int returnDestPortEnd();

    const string returnWholeIP();
    
    const vector<string> returnBinRule();

    bool isRanged();
    const vector<string> returnRangedBinRule();
private:
    void createBinRule();
    void extractRule(string& rule);
    void checkForTwoRange(int&, int&, string&);
    
    const string returnIp1();
    const string returnIp2();
    const string returnIp3();
    const string returnIp4();
    
    int srcPortStart;
    int srcPortEnd;
    int destPortStart;
    int destPortEnd;
    int ip1;
    int ip2;
    int ip3;
    int ip4;
    int priority;
    
    Protocol protocol;
    Accept_Deny action;
    vector<string> binRule;
    Direction direction;
    
    binDecConverter converter;
};

#endif // GROUPEDRULE_H