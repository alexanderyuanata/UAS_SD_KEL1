#ifndef save_load
#define save_load

#include <iostream>
#include "data_structures.h"
#include "constants.h"
#include <fstream>
#include <string>

using namespace std;


//displays loading message
void loading() {
	for (int i = 0; i < loading_repeat; i++) {
		system("cls");
		cout << "Loading";
		for (int j = 0; j < 3; j++) {
			Sleep(loading_delay);
			cout << ".";
		}
	}
}

void rewrite(	int max_hp, int hp, int level, int xp, int dmg, int gold, string name,
				string role, int days, int day_quota, bool finish, int *items, int* current_bounty) {
	ofstream save{ save_file };
	if (!save) {
		cerr << "CANNOT OPEN FILE FOR SAVING\n";
		exit(1);
	}

	//save player data
	save << max_hp << ' ';
	save << hp << ' ';
	save << level << ' ';
	save << xp << ' ';
	save << dmg << ' ';
	save << gold << ' ';
	save << name << ' ';
	save << role << ' ';

	//save time data
	save << days << ' ';
	save << day_quota << ' ';
	save << finish << ' ';

	//save item held
	for (int i = 0; i < 3; i++) save << items[i] << ' ';

	//save bounties
	for (int i = 0; i < 6; i++) save << current_bounty[i] << ' ';

	save.close();
}

void resetSave() {
    loading();
	system("cls");
	ofstream save{ save_file };
	cout << "Greetings, adventurer! In this land of magic and mystery, I must know the name of the brave soul who has entered our realm. Speak thy name so that it may be recorded in the annals of our history and forever remembered.\n";
	Sleep(1500);
	cout << "What name do you want the world to remember you by?: ";
	string temp_name;
	//have to use cin since save data is separated by whitespaces
	cin >> temp_name;
	//if player enters a name with whitespace, immediately flush out since it will cause an error in save data
	ignoreLine();
	loading();
	system("cls");

	cout << "Brave adventurer, before we embark on our quest, we must first determine the path you will play in this grand adventure:\n\n";
	cout << "1. The Path of Destruction\nChoose the path of Destruction if you seek to unleash devastating attacks upon your foes! These characters specialize in dealing high damage and are also known for their incredible survivability, making them a formidable force on the battlefield. With the ability to withstand even the toughest of blows, Destruction path characters can last longer in combat, enabling them to deliver higher sustained damage over time.\n\n";
	Sleep(2500);
	cout << "2. The Path of Nihility\nEmbark on the Nihility path and become a master of debuffs! Nihility path characters possess the ability to apply debilitating effects to their enemies, reducing their combat capabilities and making them vulnerable to attacks. With the enemy's defenses weakened, your character's hits will become more powerful and easier to land, while also increasing their survivability on the battlefield. Nihility path characters are adept at controlling the flow of combat, making them an indispensable asset.\n\n";
	Sleep(2500);
	cout << "3. The Path of Erudition\nJoin the ranks of the Erudition path and become a master of area-of-effect destruction! These characters specialize in unleashing devastating attacks that deal high damage to multiple targets at once, often leaving their enemies with debilitating damage-over-time effects. Their prowess in handling large groups of enemies makes them a valuable asset in encounters with multiple waves of foes. With their high area-of-effect damage and ability to take out multiple targets at once, Erudition path characters are the ideal choice for those seeking to clear hordes of enemies in a flash. \n\n";
	Sleep (2500);
	cout << "Speak your choice: ";
	int temp_role = getInputInt();
	loading();
	system("cls");

	switch (temp_role) {
	//class hp, level 1, 0 xp, class dmg, starting gold, input name, days passed, potions allowed to buy, has the game been defeated, number of items, bounties collected
	case 1: rewrite(initial_class[role::warrior - 1][initial_max_hp], initial_class[role::warrior - 1][initial_max_hp], loot[starting::level], loot[starting::xp], initial_class[role::warrior - 1][initial_dmg], loot[starting::gold], temp_name, "Destruction", days_passed, daily_quota, false, initial_item, initial_bounty); break;
	case 2: rewrite(initial_class[role::archer - 1][initial_max_hp], initial_class[role::archer - 1][initial_max_hp], loot[starting::level], loot[starting::xp], initial_class[role::archer - 1][initial_dmg], loot[starting::gold], temp_name, "Nihility" , days_passed, daily_quota, false, initial_item, initial_bounty); break;
	case 3: rewrite(initial_class[role::rogue - 1][initial_max_hp], initial_class[role::rogue - 1][initial_max_hp], loot[starting::level], loot[starting::xp], initial_class[role::rogue - 1][initial_dmg], loot[starting::gold], temp_name, "Erudition"  , days_passed, daily_quota, false, initial_item, initial_bounty); break;
	default: {
		cerr << "ERROR INVALID INPUT!";
		//exits game just incase it corrupts save
		exit(0);
	}break;
	}

	//intro
	loading();
	system("CLS");
	cout << "Step forth into the mystical and perilous world of Aincrad, brave adventurer. A realm shrouded in darkness and danger, where the scars of past wars run deep and the fate of entire civilizations hangs in the balance. Here, battles rage on endlessly, with armies of creatures and monsters clashing in epic struggles that shake the very foundations of the earth. Amidst this chaos, you stand as a lone warrior, your destiny intertwined with the fates of countless others. Welcome to Aincrad, a world both beautiful and deadly, where every step you take could lead to glory or to doom.\n\n";
	system("pause");
	loading();
	system("cls");
}

void save(playerData &p, dayData &d, int* items, int* bounties) {
	rewrite(p.max_hp, p.hp, p.level, p.xp, p.dmg, p.gold, p.name, p.role, d.days, d.day_quota, d.finish, items, bounties);

	for (int i=0; i<2; i++){
		system("cls");
		cout<<"Saving";
		Sleep(500);
		cout<<".";
		Sleep(500);
		cout<<".";
		Sleep(500);
		cout<<".";
	}
}

void loadSave(playerData &p, dayData &d, int* items, int* bounties) {
	ifstream save{ save_file };

	if (!save) {
		cerr << "ERROR, file unreadable!\n";
		exit(1);
	}

	save >> p.max_hp;
	save >> p.hp;
	save >> p.level;
	save >> p.xp;
	save >> p.dmg;
	save >> p.gold;
	save >> p.name;
	save >> p.role;

	save >> d.days;
	save >> d.day_quota;
	save >> d.finish;

	for (int i = 0; i < 3; i++) save >> items[i];

	for (int i = 0; i < 6; i++) save >> bounties[i];

	save.close();
}

#endif
