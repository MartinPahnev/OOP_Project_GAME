#include "Archer.h"

Archer::Archer()
    : AliveUnit(ARCHERHEALTH, ARCHERHEALTH, ARCHERATTACKDAMAGE,
        ARCHERARMOUR, ARCHERARMOURTYPE, ARCHERFACTION, ARCHERUNITTYPE)
{}

std::string Archer::getName() const
{
    return std::string("ARCHER");
}
