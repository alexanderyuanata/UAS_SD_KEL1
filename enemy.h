#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

class Enemy
{
private:
    string name;
    int hp;
    int baseDamage;
    int expDrop;
    int goldDrop;

public:
    Enemy(string name, int hp, int baseDamage, int expDrop, int goldDrop, std::vector<std::string> itemDrop)
    {
        this->name = name;
        this->hp = hp;
        this->baseDamage = baseDamage;
        this->expDrop = expDrop;
        this->goldDrop = goldDrop;
    };

    void attack()
    {
        int damage = rand() % baseDamage + 1;
        cout << name << "Attacks For " << damage << "pt\n";
    }

    void takeDamage(int damage)
    {
        hp -= damage;
        cout << name << "takes" << damage << "pt, HP remaining : " << hp << "pt.\n";
    }

    void dropLoot()
    {
        cout << "Enemy drops : " << expDrop << " EXP, " << goldDrop << " Gold \n";
    }
};
