#include <iostream>
#include <vector>
#include "TwoRanger.h"

using namespace std;

int main()
{
    
    string one = "111222";
    string two = "222000";
    string three = "00010000000";

    
    vector<string> test{one, two, three};
    TwoRanger ranger(test);
    test = ranger.returnNewRules();
    for(auto i: test)
    {
        cout << i << endl;
    }
        cout << "Test vec size: " << test.size() << endl;

}