#pragma once
#include "Army.h"
#include <iostream>


class Duel {
public:
    void setup(Army* living, Army* undead);

    void fight();

 
    uint16_t getResult();
private:
    Army* livingArmy = nullptr;
    Army* undeadArmy = nullptr;

    uint16_t result = 0;

    void undeadTurn();
    void livingTurn();
    void resurrectionPhase();
    void finalLivingAttack();

    void useAbilities(Army* army, Army* otherArmy);
    void attack(Army* attackers, Army* defenders);
};
