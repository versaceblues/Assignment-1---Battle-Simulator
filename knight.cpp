#include "Knight.h"
#include <cstdlib>

// Takes more damage, and has fewer potions. Damage is more consistent, but lower on average than the wizard.
Knight::Knight(std::string playerName) : Player(playerName, 120, 2, 15) {}  

int Knight::GetAttackDamage() {
    return baseDamage + (rand() % 8);    // More consistent damage
}