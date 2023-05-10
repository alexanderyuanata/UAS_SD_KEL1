#pragma once

#include <iostream>
using namespace std;

typedef struct {
    int days;
    int day_quota;
    bool finish;
}dayData;

typedef struct {
    int max_hp;
    int hp;
    int level;
    int xp;
    int dmg;
    int gold;
    string name;
    string role;
}playerData;

typedef struct {
    string name;
    int dmg;
    int hp;
    int gold;
    int xp;
}enemy;

//ignores cin buffer until newline
void ignoreLine() {
    cin.ignore(9000000, '\n');
}

//gets integer for input, repeats until valid
int getInputInt() {
    while (true) {
        //gets input
        cout << "\n>> ";
        int inputInt;
        cin >> inputInt;
        //if fail to extract then repeat and flush cin
        if (!cin) {
            cin.clear();
            ignoreLine();
            cerr << "Invalid input, please retry again!!\n";
        }
        //if not then return input
        else {
            ignoreLine();
            return inputInt;
        }
    }
}

