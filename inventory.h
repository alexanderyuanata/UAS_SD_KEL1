#include<iostream>

enum items {
	health = 0,
	mana = 1,
	poison = 2,
};

const int add_health = 100;
const int give_poison = 150;

void heal(int heal_amount) {
	player.hp += heal_amount;
	if (player.hp > player.max_hp) player.hp = player.max_hp;

	cout<<"Your health is increased by : "<<heal_amount<<"\n";
	cout<<"Your current health 		   : "<<player.hp<<"\n";
	system("pause");
}

bool checkItem(int i) {
	if (items[i] > 0){
		items[i]--;
		return true;
	}
	else {
		return false;
	}
}

void inventory (){
	system("cls");
	cout<<"Items in your iventory : \n";
	cout<<"1. Health Potion : " << items[health] << " bottle(s)\n";
	cout<<"2. Poison Potion : " << items[poison] << " bottle(s)\n";
	cout<<"3. Super Potion : " << items[super] << " bottle(s)\n";
	cout<<"4. Return\n";
	cout<<"Any item you want to use?";
	int inventory_select = getInputInt();

	if (checkItem(inventory_select-1)){
		switch (inventory_select) {
			case 1 : heal(add_health); break;
			case 2 : heal(give_poison); break;
			case 3 : player.hp = player.max_hp; break;
			case 4 : break;
		}
	}
}
