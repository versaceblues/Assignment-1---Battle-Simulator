#ifndef ENEMY_H
#define ENEMY_H

#include <string>

struct Enemy {
    std::string name;
    int health;
    int attackDamage;
};

Enemy SpawnRandomEnemy();

#endif // ENEMY_H