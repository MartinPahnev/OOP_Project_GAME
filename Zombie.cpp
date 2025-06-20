#include "Zombie.h"

Zombie::Zombie()
    : UndeadUnit(ZOMBIEHEALTH, ZOMBIEHEALTH, ZOMBIEATTACKDAMAGE,
    ZOMBIEARMOUR, ZOMBIEARMOURTYPE, ZOMBIEFACTION, ZOMBIEUNITTYPE)
{}


std::string Zombie::getName() const
{
    return std::string("Zombie");
}

Zombie::Zombie(int16_t health)
    : UndeadUnit(health, health, ZOMBIEATTACKDAMAGE,
        ZOMBIEARMOUR, ZOMBIEARMOURTYPE, ZOMBIEFACTION, ZOMBIEUNITTYPE)
{}
