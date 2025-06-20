#pragma once
#include "Unit.h"
class UndeadUnit : public Unit
{
public:
    
    UndeadUnit( int16_t health, int16_t maxHealth,
                int16_t attackDamage,
                int16_t armour, ArmourType armourType,
                Faction faction,
                UnitType unitType);

    // Inherited via Unit
    std::string getName() const = 0;
};