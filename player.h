#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    std::string name;
    int health;
    int maxHealth;
    int potions;
    int baseDamage;

    Player(std::string playerName, int hp, int pots, int dmg);
    virtual ~Player() = default;

    void TakeDamage(int damage);
    void Heal();
    virtual int GetAttackDamage();
};

#endif