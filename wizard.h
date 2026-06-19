#ifndef WIZARD_H
#define WIZARD_H

#include "Player.h"
#include <string>

class Wizard : public Player {
public:
    Wizard(std::string playerName);
    int GetAttackDamage() override;
};

#endif