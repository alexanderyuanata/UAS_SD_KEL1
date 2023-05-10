#ifndef ENTITY
#define ENTITY

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

class Entity{
public:
    string name;
    int max_hp;
    int hp;
    int dmg;
    int spd;
};


class Enemy : public Entity
{
public:
    int expDrop;
    int goldDrop;

    Enemy(int spd)
    {
        this->spd = spd;
    };

    Enemy(string name, int max_hp, int baseDamage, int spd, int expDrop, int goldDrop)
    {
        this->name = name;
        this->max_hp = max_hp;
        this->hp = this->max_hp;
        this->dmg = baseDamage;
        this->spd = spd;
        this->expDrop = expDrop;
        this->goldDrop = goldDrop;
    };

    int attack()
    {
        return rand() % this->dmg + 1;
    }

    void takeDamage(int damage)
    {
        this->hp -= damage;
    }
};

#endif
