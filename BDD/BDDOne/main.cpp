#include <stdio.h>
#include "BDD.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	string rule;
    bool accept;
    cout << "Enter 8 bit rule" << endl;
    cin >> rule;
    cout << rule << endl;
    cout << "Enter accept or reject" << endl;
    cin >> accept;
    cout << accept << endl;
    
    BDD test(rule, accept);
    test.makeBDD();
    cout << "\nEnter the same digits for a packet test" << endl;
    cin >> rule;
    cout << "Break" << endl;
    cout << test.checkPacket(rule) << endl;
    
}
