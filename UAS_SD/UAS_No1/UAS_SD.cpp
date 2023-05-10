#include <iostream>
#include <Windows.h>
#include "data_structures.h"
#include "save_load.h"
#include "Randomize.h"
#include "combat_funcs.h"
#include "constants.h"

using namespace std;
/*
1. Correct/Working
2. Robust
3. Concise
4. Readable
5. Modifiable
6. Efficient
*/


playerData player{
	500,
	500,
	1,
	0,
	30,
	0,
	"error_shouldnt_pop_up",
	"role_error_check_save",
};

dayData dayta{
	0,
	3,
	false,
};

int items[3];
int current_bounty[6];


//checks if days passed = days to game over, if it is then game over
void checkGameover(bool check) {
	if (dayta.days >= day_length && !check) {
		system("CLS");
		cout << "Nothing is at is seems. You may grasp at the truth but you will grab hold of nothing.\n";
		cout << "The " << day_length << " trials have been completed and you have failed, the world will restart.\n";
		system("pause");
		system("CLS");
		resetSave();
		exit(0);
	}

	if (!check) {
		if (dayta.days < (day_length/4)) cout << "Rumors are circulating about the advent of Ragnar�k.";
		else if (dayta.days < (day_length/2)) cout << "Lately, monster sightings have been more commmon than before.\n Many villages have been trampled upon the Horde.";
		else if (dayta.days < (day_length/1.5)) cout << "The Kingdom of Valimar to the south has fallen to a Necromancer, many people have flocked here for refuge.\nThe streets are busier than ever these days.";
		else if (dayta.days < day_length) cout << "The sky is black, we cannot see the sun. May the Lord bless our souls.";
	}
	else {
		cout << "Peace has returned. Your journey is over.";
	}
	cout << endl;

}

//check if player has collected atleast 1 bounty on every enemy type
bool bossFight() {
	for (int i = 0; i < 5; i++) {
		if (current_bounty[i] < 1) return false;
	}
	return true;
}

//levels up player
void levelUp() {
	while (player.xp >= fetch_exp(player.level)) {
		cout << endl;
		//store current max hp and damage
		int temp_hp = player.max_hp;
		int temp_playerDmg = player.dmg;

		//reduces xp counter and increases level
		player.xp -= fetch_exp(player.level);
		player.level++;

		//player has leveled up, increase dmg and max hp
		cout << player.name << " has leveled up!\n";
		cout << "You are now at level " << player.level << '\n';

		player.dmg += variateLevelups(dmgper_level);
		if (player.role == "Rogue") {
			cout << "  Years of honing your skills with the blade has further improved your combat mastery.\n";
			player.dmg += variateLevelups(rogue_bonus);
		}
		if (getRand(1, 100) <= double_growth_chance) {
			cout << "  You have grasped the essence of combat! Your damage has grown further.\n";
			player.dmg += variateLevelups(dmgper_level);
		}
		cout << "  Your damage has grown by " << player.dmg - temp_playerDmg << ", you now deal roughly " << player.dmg << " damage.\n";

		player.max_hp += hpper_level;
		player.hp += hpper_level;
		if (player.role == "Warrior") {
			cout << "  The little sense of pain you had has further shrunk, allowing you to take more punishment.\n";
			player.max_hp += warrior_bonus;
			player.hp += warrior_bonus;
		}
		if (getRand(1, 100) <= double_growth_chance) {
			cout << "  Your aching body has reformed itself, better than ever. Your vitality has improved.\n";
			player.max_hp += variateLevelups(hpper_level);
			player.hp += variateLevelups(hpper_level);
		}

		cout << "  Your vitality has grown by " << player.max_hp - temp_hp << ", you now have " << player.hp << '/' << player.max_hp << " HP\n";
	}
}

//checks if player can buy count items with total price of price
bool buy(int price, int count) {
	//if more gold than cost and item bought is less or equal to quota then buy
	if ((player.gold >= price) && (count <= dayta.day_quota)) {
		player.gold -= price;
		dayta.day_quota -= count;
		cout << "You spent "<< price << " gold on " << count << " potions.\n";
		cout << "You have " << player.gold << " gold left.\n";
		system("pause");
		return true;
	}
	//if not then player cannot buy
	else {
		cout << "\"Sorry hun, can't sell you these.\"";
		system("pause");
		return false;
	}
}

//heals player, capped at max hp
void heal(int heal_amount) {
	player.hp += heal_amount;
	if (player.hp > player.max_hp) player.hp = player.max_hp;

	cout<<"Your health is increased by : "<<heal_amount<<"\n";
	cout<<"Your current health 		   : "<<player.hp<<"\n";
	system("pause");
}

//check if player can use an item
bool checkItem(int i) {
	if (items[i] > 0){
		items[i]--;
		return true;
	} else {
		return false;
	}
}

//starts the game
void startGame() {
	cout << "1. New Game\n2. Continue";
	int opt = getInputInt();

	switch (opt) {
	//starts a new game, resets save and asks for new initial save info
	case 1: resetSave();break;
	system("cls");
    loading();
    system("cls");

	//dont do anything
	case 2: {
		system("cls");
		loading();
		system("cls");
	}break;

	//alert false input
	default: {
		cerr << "Wrong input, please retry again!!\n";
		exit(2);
	}
	}
	//load data
	loadSave(player, dayta, items, current_bounty);
}

//displays enemy hp and damage
void enemyStats (int i){
	cout<<enemys[i].name<<" health : "<<enemys[i].hp<<"\n";
	cout<<enemys[i].name<<" damage : "<<enemys[i].dmg;\
}

//displays player hp and damage
void playerStats (){
	cout<<"health : "<<player.hp<<"\n";
	cout<<"damage : "<<player.dmg<<"\n";
}

//start a battle with a selected enemy
void fight (int i){
	//generate player's dice roll
	int die = DetermineDamage(player);

	//determine damage from player and enemy
	int temp_playerDmg = player.dmg * (base_dmg + (damage_multiplier * die));
	int temp_enemyDmg = variateEnemyDMG(enemys[i].dmg);

	//determine crit rate and rolled crit
	int crit_rate = base_crit;
	int crit = getRand(1, 100);

	//if player is an archer then add 10% crit chance every 2 pts
	if (player.role == "Archer") {
		int track = 0;
		while (track < die) {
			crit_rate += archer_crit;
			track += 2;
		}
		cout << "\nYour sharp eyesight has identified the opponent's vital points.";
	}

	//if crit successful then damage is multiplier by crit_multiplier
	if (crit <= crit_rate){
		cout<<"\nCRITICAL DAMAGE!!!";
		temp_playerDmg *= crit_multiplier;
	}

	//if the enemy is the final boss
	if (i == enemy_index::admin){
		//roll for player and boss dice
		int player_dice = getRand(1, 6);
		int enemy_dice = getRand(1, 6);

		//if player dice is less than boss dice (roughly 15/36)
		if (player_dice < enemy_dice) {
			//boss crits while player deals less damage
			temp_enemyDmg *= crit_multiplier;
			temp_playerDmg /= crit_multiplier;
			cout << '\n';
			cout<<enemys[i].name<<" altered reality to its will, you dealt less damage to the "<<enemys[i].name<<"\n";
			cout<<enemys[i].name<<" dealt more damage than usual.";
		}
		//resolve damage
		enemys[i].hp -= temp_playerDmg;
		if (enemys[i].hp > 0) player.hp -= temp_enemyDmg;
	} else {
		//for normal enemies just resolve damage
		enemys[i].hp -= temp_playerDmg;
		if (enemys[i].hp > 0) player.hp -= temp_enemyDmg;
	}
	//tell players about damage dealt and received
	cout << "\n\nYou dealt " << temp_playerDmg << " damage to " << enemys[i].name << endl;
	if ((enemys[i].hp > 0) && (i != enemy_index::admin)) cout << enemys[i].name << " dealt " << temp_enemyDmg << " damage to you.\n";
	if ((enemys[i].hp > 0) && (i == enemy_index::admin)) cout << enemys[i].name << " attempted to erase " << player.name << " from existence,\ndealing " << temp_enemyDmg << " damage.";
}

//for defense option
void defend (int i){
	//roll dice for player and enemy
	int player_dice = getRand(1, 6);
	int enemy_dice = getRand(1, 6);

	//Warriors get an advantage in defense
	if (player.role == "Warrior") player_dice++;

	//if the enemy is the admin then defenses dont do anything
	if (i == enemy_index::admin){
		cout<<"The administrator wills its attack through reality itself. Your defenses are futile.\n";
		cout<<"You have taken "<<enemys[i].dmg<<" damage";
		player.hp -= enemys[i].dmg;
	//if its a normal enemy
	}
	else {
		cout<<"If your rolled dice is bigger than the enemy dice, you will defend the enemy attack. Otherwise, be prepared!!!";
		cout<<"\nPress Enter to roll dice\n";
		system("pause");
		loading();
		cout<<"\nYour dice : "<<player_dice<<"\n";
		cout<<"Enemy dice : "<<enemy_dice<<"\n";
		//if player dice is greater or equal than enemy dice then counter
		if (player_dice >= enemy_dice) {
			//the greater the difference, higher counter damage
			int def_taken = player.dmg*(base_def + (counter_multiplier*(player_dice - enemy_dice)));
			cout << "Your defense staggered the enemy, you took the chance to counter attack.\n";

			//calculate counter crit, warriors have higher crit chance and damage
			if (player.role == "Warrior") {
				if (getRand(1, 100) <= warrior_crit) {
					def_taken *= warrior_buff;
					cout << "The warrior's bloodlust froze the enemy in place, allowing you to punch through them with ease.\n";
				}
			}
			else {
				if (getRand(1, 100) <= def_crit_chance) {
					def_taken *= def_multiplier;
					cout << "You strike them in their vitals while they're vulnerable, dealing more damage.\n";
				}
			}

			//display counter damage.
			cout << "The enemy takes "<<def_taken<<" damage in return\n";
			enemys[i].hp -= def_taken;
		}
		//if your dice loses then reduce damage, lower difference, lower damage
		else if (player_dice < enemy_dice) {
			int def_dmg = enemys[i].dmg*(base_def_red - (red_multiplier*(enemy_dice - player_dice)));
			cout<<"The enemy's attack pierced through your fragile defenses.\nYou have taken "<<def_dmg<<" damage.\n";
			player.hp -= def_dmg;
		}
	}
}

//display the amount of potions in your inventory and use one or cancel
void inventory (){
	system("cls");
	loading();
	cout<<"Items in your iventory : \n";
	cout<<"1. Potion of Healing : " << items[potion] << " bottle(s)\n";
	cout<<"2. Elixir of Life    : " << items[elixir] << " bottle(s)\n";
	cout<<"3. Angel's Tears     : " << items[tear] << " bottle(s)\n";
	cout<<"4. Return\n";
	cout<<"Any item you want to use?";
	int inventory_select = getInputInt();

	if (checkItem(inventory_select-1)){
		switch (inventory_select) {
			case 1 : heal(heal_potion); break;
			case 2 : heal(heal_elixir); break;
			case 3 : player.hp = player.max_hp; break;
			case 4 : break;
		}
	}
}


//try and escape
bool escape (int i){
	cout << "You attempted to escape..\n";
	Sleep(500);
	//if successful (66.7%) then return true
	if (getRand(1, 3) <= 2) {
		cout << "With scraped knees and clotting blood in your throat, you managed to escape\n";
		system("pause");
		cout << "Returning to main menu...";
		Sleep(2000);
		loading();
		return true;
	}
	//if not, take damage and return false
	else {
		int temp_playerDmg = variateEnemyDMG(enemys[i].dmg);
		cout << "But it was for naught as they managed to get one free hit before you started recovering your poise.\n";
		cout << "You took " << temp_playerDmg << " damage as you scrambled to get up.\n";
		player.hp -= temp_playerDmg;
		system("pause");
		return false;
	}
}

//if player won
void win (int i, int hp){
	system("cls");

	//track the bounty of the enemy you killed and display loot
	current_bounty[i]++;
	cout<<"Congratulations! You have slain the "<<enemys[i].name<<".\nYou have collected " << current_bounty[i] << " bounties on this monster.\n";
	cout<<"You collected : "<<enemys[i].gold<<" gold\n";
	cout<<"You earned    : "<<enemys[i].xp<<" experience\n";

	//add xp to counter, if xp is more than xp threshold then level up
	player.xp += enemys[i].xp;
	if (player.xp >= fetch_exp(player.level)) levelUp();

	//add gold to current gold
	player.gold += enemys[i].gold;

	//restore enemy hp for next encounter
	enemys[i].hp = hp;

	//return to main menu
	system("pause");
	loading();
}

//if player loses
void lose (int i, int hp){
	system("cls");

	cout<<"YOU DIED\n";
	system("pause");

	loading();
	//restore enemy hp for next encounter
	enemys[i].hp = hp;
	loadSave(player, dayta, items, current_bounty);
}


//display combat menu
void combat (){
	loading();
	system("cls");

	//display all enemies available
	cout<<"The hordes are marching towards Aincrad... : \n";
    for (int i=0; i<5; i++){
        cout<< i+1 <<". " << enemys[i].name <<"\n";
    }

	//if you've collected 1 bounty on each of the monster available, boss fight is now available
	if (bossFight()) {
		cout << enemys[enemy_index::admin].name << " has descended to the game fix the anomaly\n" << "6. THE WOöLD öNDS WööH YöU\n";
	}

	//receive input
	cout << "0. Return to Aincrad\n";
	cout<<"Which monster will you hunt?";
	int enemy_select = getInputInt();
	enemy_select = enemy_select-1;

	//if player selects boss fight but they havent collected bounty, reject battle
	if ((enemy_select == 5) && (!bossFight())){
		cout<<"Invalid input, please try again ... for now\n";
		system("pause");
		return;
	}
	else if (enemy_select == -1) {
		cout << "You went back to Aincrad, the city guards giving you a strange look as you retreated.\n";
		system("pause");
		return;
	}

	//store turn counter and enemy max_hp
	int turn = 1;
	int temp_hp = enemys[enemy_select].hp;
	cout<<"Preparing for combat..."; Sleep(500);

	//while enemy is still alive
	while (enemys[enemy_select].hp >= 0){

		system("cls");
		//display boss flavor text
		if (enemy_select == enemy_index::admin && turn <= 1) cout << "The sky shattered. A palace of red descends from the sky.\n\n";
		else if (enemy_select == enemy_index::admin && turn > 1) cout << boss_text() << "\n\n";
		//display turn counter
		cout<<"Turn "<<turn<<"\n";

		//display player and enemy stats
		cout<<"Combat Stats :\n";
		enemyStats(enemy_select);
		cout<<"\n\n";
		playerStats();
		cout<<"\n\n";

		//Combat options
		cout<<"Fight Option : \n";
		cout<<"1. Fight,  and relish in the violence\n2. Defend, and pray that they miss\n3. Items,  they do not bring salvation\n4. Escape, to live another day\n";
		cout<<"Choose your option : ";
		int choice_select = getInputInt();

		//check options
		switch (choice_select) {
			//fight the enemy
			case 1: fight(enemy_select);system("pause"); break;
			//defend against the enemy
			case 2: defend(enemy_select); system("pause"); break;
			//use an item
			case 3: inventory();break;
			//attempt an escape
			case 4: if (escape(enemy_select)) return;break;
		}

		//increase turn counter
		turn++;

		//if the enemy dies then display win dialogue
		if (enemys[enemy_select].hp <= 0){
			win(enemy_select, temp_hp);
			break;
		}
		//if the player dies then display death dialogue
		if (player.hp <= 0){
			lose(enemy_select, temp_hp);
			break;
		}
	}
}

//enter tavern dialogue
void tavern() {
	//price for one night
	int price = base_rent_cost + ((player.max_hp - player.hp)*rentcost_perhp);
	cout << "Rent a room? You currrently have " << player.gold << " gold.\n1. Yes ( " << price << " gold )\n2. Sleep on the front of the tavern\n3. No\n";
	int opt = getInputInt();

	switch (opt) {
	//if you rent a room
	case rent: {
		//if player can afford,
		if (player.gold >= price) {
			//reduce money by price
			player.gold -= 	price;

			//restore health to max hp
			player.hp = player.max_hp;

			//advance one day and restore potion quota
			dayta.days++;
			dayta.day_quota = dayta_quota;

			cout << "The innkeeper smiled as he slid the key across the table.\n\"Thank you for your patronage.\"\nYou went upstairs and rested your weary soul on the bed.\n";

			cout << endl;
			//check if its game over
			checkGameover(dayta.finish);
			cout << endl;

			//tell healing amount
			cout << "You healed for your maximum health, your health is now " << player.hp << " HP.\n";

			system("pause");
			system("cls");
			loading();
			return;
		}
		//if you dont have enough money, dont do anything
		else {
			cout << "\"That's not enough, buddy.\" He said as he retracted his arms.\n";
			system("pause");
			system("cls");
			loading();
			return;
		}

	}break;
	//advance a day, restore quota but dont heal
	case homeless: {
		dayta.days++;
		dayta.day_quota = dayta_quota;

		cout << "The cold wind whistled through your clothes, caressing you bruised and battered body.\nIn the morning, you still feel exhausted.\n";
		checkGameover(dayta.finish);
		cout << "Your health remains the same due to lack of sleep, your health is now at " << player.hp << " HP.\n";
		system("pause");
		system("cls");
		loading();
		return;
	}
	//dont do anything
	case deny: {
		return;
	}break;
	}
}

//open shop dialogue
void shop() {
	system("CLS");
	loading();
	system("CLS");
	cout << "\"Ah, an unfamiliar face.\" She giggled. Her wand pointed to a rack in the middle of the room.\nNumerous bottles filled with prismatic liquid were displayed and up for sale.\n\"You don't look like a magi, those might be more up your alley.\"";
	cout << "\nYou have " << dayta.day_quota << " daily quota(s) left.";

	//if you still have your potion quota, open buying dialogue
	if (dayta.day_quota > 0){
		cout << "\n1. Potion of Healing\n2. Elixir of Life\n3. Angel's Tear";
		int select = getInputInt();
		select--;
		switch (select) {
		//buy potions
		case potion: {
			cout << "A concoction of herbs, unknown ingredients and Gyarados' viscera. Disgusting but potentially lifesaving." << endl;
			cout << "\"200 gold a pop.\"She stated. (Heal 150 HP)\"\n";
			cout << "How many you want to buy?(fill with 0 to cancel)\n";
			cout << "Your gold : " << player.gold;

			//if you can buy potions then add them to your inv
			int potion_ct = getInputInt();
			if (buy(potion_ct * potion_cost, potion_ct)) items[potion] += potion_ct;
		}break;

		//buy elixirs
		case elixir: {
			cout << "A mermaid's fins and a purified undead's ashes. While it tastes better than potions, it certainly doesn't sound better.\n";
			cout << "\"500 gold each, but it's worth it.\" (Heal 450 HP)\"\n";
			cout << "How many you want to buy?(fill with 0 to cancel)\n";
			cout << "Your gold : " << player.gold;
			int elixir_ct = getInputInt();
			if (buy(elixir_ct * elixir_cost, elixir_ct)) items[elixir] += elixir_ct;
		}break;

		//buy tears
		case tear: {
			cout << "Harvested from a flower that is said to have grown out of an archangel's tears. Has incredible healing properties.\n";
			cout << "\"1000 gold, no haggling. (Heal to Max HP)\"\n";
			cout << "How many you want to buy?(fill with 0 to cancel)\n";
			cout << "Your gold : " << player.gold;
			int tear_ct = getInputInt();
			if (buy(tear_ct * tear_cost, tear_ct)) items[tear] += tear_ct;
		}
		}
	}
	//if you dont have potion quota then return
	else {
		cout << "\n\"Ah, sorry honey, we only sell 3 potions per day. Prevents monopolies.\"\n";
		system("pause");
	}
	system("cls");
	loading();
}

//exploration guild dialogue
void explore() {
	system("cls");
	loading();
	system("cls");
	cout << "\"Hey, you need an explorer?\" the short, stout man asked.\n";
	cout << "\"Or maybe intel? you look like someone who needs some intel.\"\n";
	cout << "\"Here's what we got.\"\n1. Gyarados\n2. P.E.K.K.A\n3. Abyss Herald\n4. Pudge\n5. Omen\n6. Administrator";
	int select = getInputInt();

	//tell the player monster stats and bounties collected
	switch (select) {
		case 1: {
			cout << "Those Gyarados are some wild beasts. They live in warm temperature water and are\nomnivorous with an appetite for humans.\n";
			cout << "HP  : " << enemys[gyardos].hp << endl;
			cout << "DMG : " << enemys[gyardos].dmg << endl;
			cout << "You have collected " << current_bounty[0] << " bounties from this enemy.";
		}break;
		case 2: {
			cout << "P.E.K.K.As are rumored to be the product of an ancient civilization. They attack\nhumans on sight, chop them down like firewood.\n";
			cout << "HP  : " << enemys[pekka].hp << endl;
			cout << "DMG : " << enemys[pekka].dmg << endl;
			cout << "You have collected " << current_bounty[1] << " bounties from this enemy.";
		}break;
		case 3: {
			cout << "Abyss Heralds come from the dark side of the moon. They can dance and use void magic,\nplus their ethereal body makes them tanky as all hell.\n";
			cout << "HP  : " << enemys[herald].hp << endl;
			cout << "DMG : " << enemys[herald].dmg << endl;
			cout << "You have collected " << current_bounty[2] << " bounties from this enemy.";
		}break;
		case 4: {
			cout << "Pudges are...something. They're necrotized avarice tissue from the land up north.\nThey eat anything that they can get their hands on.\n";
			cout << "HP  : " << enemys[pudge].hp << endl;
			cout << "DMG : " << enemys[pudge].dmg << endl;
			cout << "You have collected " << current_bounty[3] << " bounties from this enemy.";
		}break;
		case 5: {
			cout << "Omens are-or should i say, were once-humans. They were struck with black magic and\nhave lost their sanity.\n";
			cout << "HP  : " << enemys[omen].hp << endl;
			cout << "DMG : " << enemys[omen].dmg << endl;
			cout << "You have collected " << current_bounty[4] << " bounties from this enemy.";
		}break;
		case 6: {
			if (current_bounty[admin] == 0) {
				cout << "Error 404 not found. This page shouldn't be available\n";
				cout << "HP  : ???"<< endl;
				cout << "DMG : ???"<< endl;
				cout << "How did you get here?";
			} else {
				cout << "The Administrator......you know who you're fighting with\n";
				cout << "HP  : " << enemys[admin].hp << endl;
				cout << "DMG : " << enemys[admin].dmg << endl;
				cout << "You have collected " << current_bounty[5] << " bounties from this enemy.";
			}
		}break;
	}
	cout << endl;
	system("pause");
	loading();
}

//wandering through the town dialogue
void wander() {
	loading();

	while (true) {
		system("CLS");
		cout << "You wander through the streets of Aincrad. Death permeates the air.\nWar, famine and plague, all different events but they all lead to the same conclusions.\n";
		if (player.hp < (int)(player.max_hp / 3)) cout << "You dragged your limping, festering body across the cobbled streets, living to fight another day.\n";
		else cout << "Your pace is light but hopeful, your gaze rests ontop of several plaques above your eye level.\n";
		cout << "1. Tavern\n2. Explorer's Guild\n3. Illia's Shop of Wonders\n4. Return and Ponder Your Next Move";
		int select = getInputInt();
		switch (select) {
		case 1: {
			tavern();
		}break;

		case 2: {
			explore();
		}break;

		case 3: {
			shop();
		}break;

		case 4: {
			system("cls");
			loading();
			system("cls");
			return;
		}break;
		}
	}
	cout << endl;
	system("pause");
}

int main() {
	system("cls");
	//starts game, new game or load game
	startGame();

	//repeat until exit
	do {
		system("cls");
		//main dialogue
		cout << player.name << "'s Status\n---------------" << endl;
		cout << dayta.days << " days have passed." << endl;
		cout << "Level  : " << player.level << endl;
		cout << "Class  : " << player.role << endl;
		cout << "Gold   : " << player.gold << endl;
		cout << "XP     : " << player.xp << '/' <<  fetch_exp(player.level) << endl;
		cout << "Health : " << player.hp << '/' << player.max_hp << endl;
		cout << "\nChoose your action : \n1. Seek an Encounter\n2. Wander\n3. Inventory\n4. Save\n5. Quit\n";
		int select = getInputInt();

		switch (select) {
			case 1: combat(); break; //fight monsters
			case 2: wander(); break; //wander through town
			case 3: inventory(); break; //open inventory
			case 4: save(player, dayta, items, current_bounty); break; //save state
			case 5: {
				//end game
				system("CLS");
				cout << "Ending the journey...\n"; system("pause");
				save(player, dayta, items, current_bounty);
				exit(0);
			}break;
		}
	} while (true);
}
