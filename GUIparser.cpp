#include "GUIparser.h"

GUIparser::GUIparser()
{
    string temp;
    while(temp != "accept" || temp != "drop")
    {
    cout << "Please enter action:" << endl;
    cin >> temp;
    }
    action = temp;
    
    while(temp != "in" || temp != "out")
    {
        cout << "Please enter direction (in or out): " << endl;
        cin >> temp;
    }
    direction = temp;
    
    cout << "Please enter ip address: " << endl;
    cin >> temp;
    ip = temp;
    cout <<
}

GUIparser::~GUIparser()
{
}

