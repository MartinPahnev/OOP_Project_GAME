#include "Ghoul.h"

Ghoul::Ghoul() : UndeadUnit(GHOULHEALTH, GHOULHEALTH, GHOULATTACKDAMAGE,
    GHOULARMOUR, GHOULARMOURTYPE, GHOULFACTION, GHOULUNITTYPE)
{}

std::string Ghoul::getName() const
{
    return std::string("Ghoul");
}
