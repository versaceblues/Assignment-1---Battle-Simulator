#ifndef KNIGHT_H
#define KNIGHT_H

#include "Player.h"
#include <string>

class Knight : public Player {
public:
    Knight(std::string playerName);
    int GetAttackDamage() override;
};

#endif 