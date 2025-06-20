#include "Knight.h"

Knight::Knight()
    : AliveUnit(KNIGHTHEALTH, KNIGHTHEALTH, KNIGHTATTACKDAMAGE,
        KNIGHTARMOUR, KNIGHTARMOURTYPE, KNIGHTFACTION, KNIGHTUNITTYPE)
{}


std::string Knight::getName() const
{
    return std::string("KNIGHT");
}
