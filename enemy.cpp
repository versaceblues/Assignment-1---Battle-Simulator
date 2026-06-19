#include "enemy.h"
#include <cstdlib>

Enemy SpawnRandomEnemy() {
    Enemy e;
    int roll = rand() % 3;

    if (roll == 0) {
        e.name = "Goblin";
        e.health = 35;
        e.attackDamage = 12;
    } else if (roll == 1) {
        e.name = "Skeleton";
        e.health = 50;
        e.attackDamage = 17;
    } else {
        e.name = "Ogre";
        e.health = 70;
        e.attackDamage = 23;
    }
    return e;
}