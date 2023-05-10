#ifndef BATTLE
#define BATTLE

#include <queue>
#include <algorithm>

#include "randomize.h"
#include "entity.h"

using namespace std;

bool compareSpd(const Entity& m, const Entity& n){
    return m.spd > n.spd;
}

void insertionSort(std::vector<Entity>& vec, bool(*comp)(const Entity&, const Entity&)) {
    for (size_t i = 1; i < vec.size(); ++i) {
        Entity temp = vec[i];
        int j = i - 1;
        while (j >= 0 && comp(temp, vec[j])) {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = temp;
    }
}

void startBattle(vector<Entity>participants){
    //battle order sort by speed
    insertionSort(participants, compareSpd);
    queue<Entity> battleOrder;

    for (auto& elements : participants){
        battleOrder.push(elements);
    }

    while(!battleOrder.empty()){
        Entity currentTurn = battleOrder.front();
        cout << typeid(currentTurn).name() << " " << currentTurn.spd << endl;
        battleOrder.pop();
    }
    
}



#endif