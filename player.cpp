#include "player.h"
#include <iostream>
#include <cstdlib>

Player::Player(std::string playerName, int hp, int pots, int dmg) {
    name = playerName;
    health = hp;
    maxHealth = hp; 
    potions = pots;
    baseDamage = dmg;
}

void Player::TakeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

void Player::Heal() {
    if (potions > 0) {
        health += 40;
        if (health > maxHealth) health = maxHealth; 
        potions--;
        std::cout << "\nYou drink a potion. Health restored to " << health << "!\n";
        std::cout << "Potions remaining: " << potions << "\n";
    } else {
        std::cout << "\nYou are out of potions!\n";
    }
}

int Player::GetAttackDamage() {
    return baseDamage + (rand() % 10);   // Default random damage. It has a 10% modifier. Wizard has 16% dmg chance.
}