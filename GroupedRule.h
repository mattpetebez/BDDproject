#ifndef GROUPEDRULE_H
#define GROUPEDRULE_H
#include <iostream>
#include <string>

#include "binDecConverter.h"

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
    GroupedRule();
    ~GroupedRule();
    //GroupedRule(int _prot,int _srcPort,int _destPort,int _ip1,int _ip2,int _ip3, int _ip4, Direction _direction);
    GroupedRule(Direction _direction, string _binRule);
    GroupedRule(Accept_Deny accept_deny, int _priority, Direction _direction, string wholeBinRule);
    Direction returnDirection();
    const int returnPriority();
    string returnProt();
    string returnSrcPort();
    string returnDestPort();
    string returnIp1();
    string returnIp2();
    string returnIp3();
    string returnIp4();
    string returnWholeIP();
    void extractRule();
    const string returnBinRule();
private:
    int prot;
    int srcPort;
    int destPort;
    int ip1;
    int ip2;
    int ip3;
    int ip4;
    int priority;
    Accept_Deny action;
    string binRule;
    Direction direction;
    binDecConverter converter;
};

#endif // GROUPEDRULE_H
