#include "Necromancer.h"

Necromancer::Necromancer()    
    : UndeadUnit(NECROMANCERHEALTH, NECROMANCERHEALTH, NECROMANCERATTACKDAMAGE,
        NECROMANCERARMOUR, NECROMANCERARMOURTYPE, NECROMANCERFACTION, NECROMANCERUNITTYPE),
    ManaPool(NECROMANCERMANA, NECROMANCERMANA, NECROMANCERABILITYCOST)
{}

std::string Necromancer::getName() const
{
    return std::string("Necromancer");
}

void Necromancer::castAbility(Unit* target)
{
    _mana -= getAbilityCost();
}
