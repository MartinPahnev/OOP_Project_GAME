#include "Infantry.h"

Infantry::Infantry()
    : AliveUnit(INFANTRYHEALTH, INFANTRYHEALTH, INFANTRYATTACKDAMAGE,
                INFANTRYARMOUR, INFANTRYARMOURTYPE, INFANTRYFACTION, INFANTRYUNITTYPE)
{}

std::string Infantry::getName() const
{
    return std::string("INFANTRY");
}
