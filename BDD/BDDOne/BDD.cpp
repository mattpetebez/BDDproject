#include "BDD.h"

node::node(int _lvl)
{
    lvl = _lvl;
    cout << "Making node of level " << lvl << endl;
}

node::~node()
{
    cout << "Destroying node of rank " << lvl << endl;
}

const int node::getRank()
{
    return lvl;
}

void node::setlow(shared_ptr<node> _low)
{
    cout << "Setting node low" << endl;
    low = _low;
}

void node::sethigh(shared_ptr<node> _high)
{
    cout << "Setting node high" << endl;
    high = _high;
}

shared_ptr<node> node::getLow()
{
    cout << "Getting node low" << endl;
    shared_ptr<node> temp = low;
    return std::move(temp);
}

shared_ptr<node> node::getHigh()
{
    cout << "Getting node high" << endl;
    shared_ptr<node> temp = high;
    return std::move(temp);
}

BDD::BDD(const string& _rule, const bool _ACCEPT)
{
    rule = _rule;
    ACCEPT = _ACCEPT;
    accept = make_shared<node>(node(105));
    reject = make_shared<node>(node(106));
    head = NULL;
    
    if( ACCEPT == true )
    {
        term = accept;
        genTerm = reject;
    }
    else if (ACCEPT == false)
    {
        term = reject;
        genTerm = accept;
    }
}

BDD::BDD(const string& _rule, const bool _ACCEPT, shared_ptr<node>&& ownerAccept, shared_ptr<node>&& ownerDeny)
{
    rule = _rule;
    ACCEPT = _ACCEPT;
    accept = ownerAccept;
    reject = ownerDeny;
        if(ACCEPT == true)
    {
        term = accept;
        genTerm = reject;
    }
}

bool BDD::makeBDD()
{
    string::iterator iter = rule.begin();
    
    head = move(makeBranch(iter, 0));
    return true;
} 

shared_ptr<node> BDD::makeBranch(string::iterator& iter, int Lvl)
{
    cout << "Lekker Man" << endl;
    shared_ptr<node> curr = make_shared<node>(node(Lvl));
    
    if(iter != --rule.end())
    {
        if(*iter == '0')
        {
            //cout << Lvl << endl;
            curr->setlow(makeBranch(++iter, Lvl+1));
            curr->sethigh(genTerm);
        }
        else if (*iter == '1')
        {
            cout << Lvl << endl;
            curr->sethigh(makeBranch(++iter, Lvl+1));
            curr->setlow(genTerm);
        }
        
        
    }
    
    else if (iter == --rule.end())
    {
        cout << "Inside the terminating branch" << endl;
        cout << *iter << endl;
        if(*iter == '0')
        {
            curr->setlow(term);
            curr->sethigh(genTerm);
        }
        else if (*iter == '1')
        {
            curr->sethigh(term);
            curr->setlow(genTerm);
        }
        
    }
    cout << "returning node of rank " << curr->getRank() << endl;
    return curr;
}

bool BDD::checkPacket(string& rule)
{
    cout << "Checking" << endl;
    shared_ptr<node> iter = head;
    string::iterator ruleIt = rule.begin();
    
    while(iter->getRank() < 105 && ruleIt != rule.end())
    {
        cout << "Inside loop one" << endl;
        if(*ruleIt == '0')
        {
            iter = (iter)->getLow();
        }
        else if (*ruleIt == '1')
        {
            iter = (iter)->getHigh();
        }
        ++ruleIt;
    }
    
    if(iter->getRank() == 105)
    {
        cout << "Your packet was accepted." << endl;
        return true;
    }    
    
    else if (iter->getRank() == 106)
    {
        cout << "Your packet was rejected." << endl;
        return false;
    }
    else return false;
}

/*void BDD::terminateNodes()
{
    
}*/