#pragma once
#include "UndeadUnit.h"
class Ghoul :  public UndeadUnit
{
public:

	Ghoul();

	// Inherited via UndeadUnit
	std::string getName() const override;

	static constexpr uint16_t GHOULGOLDCOST = 250;

private:
	static constexpr int16_t GHOULHEALTH = 400;
	static constexpr int16_t GHOULATTACKDAMAGE = 12;
	static constexpr ArmourType GHOULARMOURTYPE = ArmourType::HEAVY;
	static constexpr int16_t GHOULARMOUR = 6;
	static constexpr Faction GHOULFACTION = Faction::UNDEAD;
	static constexpr UnitType GHOULUNITTYPE = UnitType::GHOUL;

};
