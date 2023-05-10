#include <iostream>
#include <vector>

#include "randomize.h"
#include "entity.h"
#include "battle.h"


using namespace std;

int main(){
    vector<Entity> a;
    Enemy e1(5);
    Enemy e2(19);
    Enemy e3(1);

    a.push_back(e1);
    a.push_back(e2);
    a.push_back(e3);

    startBattle(a);
    return 0;
}


