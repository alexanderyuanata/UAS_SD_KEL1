#pragma once

#include "data_structures.h"

//enum for tavern
enum tavern {
	rent = 1,
	homeless = 2,
	deny = 3,
};

//structure for enemies
enemy enemys[]{
	{"Goblin",75, 500, 250, 150, },
	{"Skeleton", 85, 1000, 300, 325},
	{"Ogre", 50, 2500, 350, 250},
	{"Hellagur", 150, 1750, 650, 650},
	{"Lich", 200, 2500, 875, 1000},
	{"Satanael", 500, 4500, 100000, 50000},
};

//enemy damage variables
const float base_enemydmg_ratio = 0.9;
const float enemy_dmg_mult = 0.05;

//enums for enemies index
enum enemy_index {
	GOBLIN = 0,
	SKELETON = 1,
	OGRE = 2,
	HELLAGUR = 3,
	LICH = 4,
	SATANAEL = 5
};

//enums for item access
enum items {
	potion = 0,
	elixir = 1,
	tear = 2,
};

//days needed to fail the game
const int day_length = 25;

//healing from potions
const int heal_potion = 150;
const int heal_elixir = 450;

//levelups
const int base_exp_cap = 400;
const float xp_multiplier = 1.1;
const float base_levelup_ratio = 0.9;
const float levelup_mult = 0.05;
const int double_growth_chance = 20;

const int dmgper_level = 20;
const int rogue_bonus = 15;
const int hpper_level = 150;
const int warrior_bonus = 75;

//for loading delays and repeat
const int loading_delay = 200;
const int loading_repeat = 2;
const int ignore_amount = 9000000;

//damage calculations
const float base_dmg = 0.75;
const float damage_multiplier = 0.1;
const int base_crit = 30;
const int archer_crit = 10;
const float crit_multiplier = 1.5;
const float warrior_def = 1.5;
const float def_crit = 1.2;
const float base_def = 0.2;
const float counter_multiplier = 0.1;
const int warrior_crit = 25;
const float warrior_buff = 1.5;
const int def_crit_chance = 20;
const float base_def_red = 0.6;
const float red_multiplier = 0.1;
const float esc_multiplier = 1.2;
const float def_multiplier = 1.2;

//file names
const string save_file{ "save.txt" };
const string item_file{ "item.txt" };
const string bounty_file{ "bounty.txt" };
const string day_file{ "day.txt" };

//quota for potions
const int dayta_quota = 3;

//enum for roles
enum role {
	warrior = 1,
	archer = 2,
	rogue = 3,
};

//new game stats for all class
enum starting {
	level = 0,
	xp = 1,
	gold = 2,
};
const int loot[3]{ 1,0,200 };

//initial class stats
enum stats {
	initial_max_hp = 0,
	initial_dmg = 1,
};

int initial_class[3][2] = { {800, 150},{500, 220},{400, 285} };

//initial time related stats
enum times {
	days_passed = 0,
	daily_quota = 3,
};

//initial bounties and items held
int initial_item[3]{ 0 };
int initial_bounty[6]{ 0 };

//tavern consts
const int base_rent_cost = 20;
const int rentcost_perhp = 0.8;

//shop consts
const int potion_cost = 200;
const int elixir_cost = 500;
const int tear_cost = 1000;
