#pragma once
#include "AliveUnit.h"
class Archer :  public AliveUnit
{
public:

	Archer();

	// Inherited via AliveUnit
	std::string getName() const override;

	static constexpr uint16_t ARCHERGOLDCOST = 300;

private:
	static constexpr int16_t ARCHERHEALTH = 535;
	static constexpr int16_t ARCHERATTACKDAMAGE = 10;
	static constexpr ArmourType ARCHERARMOURTYPE = ArmourType::MEDIUM;
	static constexpr int16_t ARCHERARMOUR = 3;
	static constexpr Faction ARCHERFACTION = Faction::ALIVE;
	static constexpr UnitType ARCHERUNITTYPE = UnitType::ARCHER;
};

