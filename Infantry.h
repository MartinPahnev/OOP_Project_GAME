#pragma once
#include "AliveUnit.h"
class Infantry : public AliveUnit
{
public:

	Infantry();

	// Inherited via AliveUnit
	std::string getName() const override;

	static constexpr uint16_t INFANTRYGOLDCOST = 250;

private:
	static constexpr int16_t INFANTRYHEALTH = 420;
	static constexpr int16_t INFANTRYATTACKDAMAGE = 7;
	static constexpr ArmourType INFANTRYARMOURTYPE = ArmourType::MEDIUM;
	static constexpr int16_t INFANTRYARMOUR = 8;
	static constexpr Faction INFANTRYFACTION = Faction::ALIVE;
	static constexpr UnitType INFANTRYUNITTYPE = UnitType::INFANTRY;

};

