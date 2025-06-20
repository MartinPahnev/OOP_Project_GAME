#pragma once
#include "AliveUnit.h"
class Knight : public AliveUnit
{
public:
    Knight();

    // Inherited via AliveUnit
    std::string getName() const override;

    static constexpr uint16_t KNIGHTGOLDCOST = 700;

private:
    static constexpr int16_t KNIGHTHEALTH = 835;
    static constexpr int16_t KNIGHTATTACKDAMAGE = 45;
    static constexpr ArmourType KNIGHTARMOURTYPE = ArmourType::HEAVY;
    static constexpr int16_t KNIGHTARMOUR = 10;
    static constexpr Faction KNIGHTFACTION = Faction::ALIVE;
    static constexpr UnitType KNIGHTUNITTYPE = UnitType::KNIGHT;
};

