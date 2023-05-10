#ifndef combat_f
#define combat_f

#include <iostream>
#include <math.h>
#include "Randomize.h"
#include "data_structures.h"
#include "constants.h"

using namespace std;

int variateLevelups(int stats) {
    return stats * (base_levelup_ratio + (getRand(1, 6) * levelup_mult));
}

string boss_text(){
    int rng = getRand(1, 100);
    if (rng >= 1 && rng <= 35) return "\"Resistence is futile, this world is fated to end.\"";
    else if (rng > 35 && rng <= 60) return "\"This shall be your tomb.\"";
    else if (rng > 60 && rng <= 80) return "\"Why are you so desperate? fighting for these worthless subspecies.\"";
    else if (rng > 80 && rng <= 95) return "\"You should've let them all die.\"";
    else return "Everything will end.";
}

void battleText(int roll, int role) {
    switch (roll) {
    case 1: {
        switch (role) {
        case role::warrior : cout << "You swing your sword but it only grazes the enemy."; break;
        case role::archer : cout << "The arrow hit them in their limbs, they flinched."; break;
        case role::rogue : cout << "The first swing missed, and so you were forced to deal a blunt blow with the hilt of your blade."; break;
        }
    }break;

    case 2: {
        switch (role) {
        case role::warrior: cout << "You dealt a hefty blow to the enemy, carving out a decent chunk of their flesh."; break;
        case role::archer: cout << "The arrow flew straight and hit them in their torso, blood started dripping out of the wound."; break;
        case role::rogue: cout << "Your first strike slashed them, and the follow up strike stabbed deep into their abdomen."; break;
        }
    }break;

    case 3: {
        switch (role) {
        case role::warrior: cout << "You muster all your strength and managed to cut off one of their limbs, blood poured out of the open wound."; break;
        case role::archer: cout << "The arrow struck them on the stomach and shattered, scrambling their intestines."; break;
        case role::rogue: cout << "Your managed to stun the enemy by slamming the hilt onto their temples, you follow up with a series of rapid strikes."; break;
        }
    }break;

    case 4: {
        cout << "You threw one of your daggers at the enemy's throat, cleaving through it like butter\nWhile they're stunned, you unleash your sure-kill technique: \"Death by Darkness\"\nThe enemy was cut into millions of tiny pieces.";
    }break;
    }
}

int DetermineDamage(playerData &p)
{
    int roles;
    if (p.role == "Warrior") roles = warrior;
    else if (p.role == "Archer") roles = archer;
    else roles = rogue;

    int die = getRand(1, 6);
    if (p.role == "Rogue") die++;

    cout << "You rolled a " << die << endl;

    if ((die == 1) || (die == 2)) battleText(1, roles);
    else if ((die == 3) || (die == 4)) battleText(2, roles);
    else if ((die == 5) || (die == 6)) battleText(3, roles);
    else if (die == 7) battleText(4, roles);

    return die;
}

int variateEnemyDMG(int dmg) {
    int die = getRand(1, 4);
    return dmg * (base_enemydmg_ratio + (enemy_dmg_mult * die));
}

int fetch_exp(int level){
    int max_xp = base_exp_cap;
    return max_xp * pow(xp_multiplier, level);
}

/*int determine damage(int initial damage){
	pake function di randomize.h buat hasilin angka dari 1-6 secara acak
	skrg, klo:
		return initial damage * (0.9 + (0.05 * angka yang dihasilkan))
		harus returnnya integer, nanti error
}

int resolve_defense (int enemy_dmg, int your_def){
	pake fungsi penghasil random number buat aduin dua angka x sama y
	klo x>y return enemy_dmg
	klo x<=y return enemy_dmg - your_def
}

int fetch exp(int level){
	buat algoritma tsrh sih, yg penting klo level makin tinggi returnnya makin tinggi. nilainya jgn tinggi kali, kisarannya mungkin ratusan-ribuan klo level ud tinggi
}

*/


#endif