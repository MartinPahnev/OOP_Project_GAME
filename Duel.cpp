#include "Duel.h"

void Duel::setup(Army* living, Army* undead) {
    livingArmy = living;
    undeadArmy = undead;
}

void Duel::fight() {
    if (undeadArmy->isAllGhosts())
    {
        result = 1;
        return;
    }
    undeadTurn();
    if (livingArmy->isArmyEmpty())
    {
        result = 2;
        return;
    }


    livingTurn();
    if (undeadArmy->isArmyEmpty()) {
        result = 1;
        return;
    }


    resurrectionPhase();

    finalLivingAttack();
    undeadArmy->removeDeadUnits();
    livingArmy->removeDeadUnits();  
    if (undeadArmy->isArmyEmpty()) {
        result = 1;
        return;
    }
    result = 0;
    return;
}

uint16_t Duel::getResult()
{
    uint16_t temp = result;
    result = 0;
    return temp;
}


void Duel::undeadTurn() {
    useAbilities(undeadArmy, livingArmy);
    attack(undeadArmy, livingArmy);
}

void Duel::livingTurn() {
    useAbilities(livingArmy, undeadArmy);
    attack(livingArmy, undeadArmy);
}

void Duel::resurrectionPhase() {
    std::vector<Unit*> deadUnits = livingArmy->getDeadUnits();
    undeadArmy->ressurectUnits(deadUnits);  
    for (Unit* unit : deadUnits) {
        delete unit;  
    }
}

void Duel::finalLivingAttack() {
    attack(livingArmy, undeadArmy);
}

void Duel::useAbilities(Army* army, Army* enemyArmy) {
    army->useAllAbilities(enemyArmy);  
}

void Duel::attack(Army* attackers, Army* defenders) {
    attackers->attack(defenders);  
}