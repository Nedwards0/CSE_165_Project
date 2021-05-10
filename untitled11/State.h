#ifndef STATE_H
#define STATE_H
#include <string>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class state{
public:
    int cases;//Amount of cases in state
    string name;//Name of State
    state(string name_s, int amount){//Constructor
        this->cases=amount;
        this->name=name_s;

    }
    state(){//Default constructor
        this->cases=INT_MAX;//This is done for making sorting easier
        this->name="<UNK>";
    }
};

#endif // STATE_H
