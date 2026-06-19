#include "Wizard.h"
#include <cstdlib>

// Less HP, more potions, stronger magic
Wizard::Wizard(std::string playerName) : Player(playerName, 85, 5, 18) {}   

int Wizard::GetAttackDamage() {
    return baseDamage + (rand() % 16);   // Higher damage variance
}