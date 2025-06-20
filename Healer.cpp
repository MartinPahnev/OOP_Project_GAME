#include "Healer.h"

Healer::Healer()
    : AliveUnit(HEALERHEALTH, HEALERHEALTH, HEALERATTACKDAMAGE,
                HEALERARMOUR, HEALERARMOURTYPE, HEALERFACTION, HEALERUNITTYPE),
      ManaPool(HEALERMANA, HEALERMANA, HEALERABILITYCOST)
{}

std::string Healer::getName() const
{
    return std::string("HEALER");
}

void Healer::castAbility(Unit* target)
{
    _mana -= getAbilityCost();
    target->changeHealth(100);
}
