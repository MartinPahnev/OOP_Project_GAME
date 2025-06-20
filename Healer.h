#pragma once
#include "AliveUnit.h"
#include "ManaPool.h"
class Healer : public AliveUnit, ManaPool
{
public:

	Healer();

	// Inherited via AliveUnit
	std::string getName() const override;

	// Inherited via ManaPool
	void castAbility(Unit* target) override;

	static constexpr uint16_t HEALERGOLDCOST = 150;

private:
	static constexpr int16_t HEALERHEALTH = 290;
	static constexpr int16_t HEALERMANA = 200;
	static constexpr int16_t HEALERABILITYCOST = 100;
	static constexpr int16_t HEALERATTACKDAMAGE = 2;
	static constexpr ArmourType HEALERARMOURTYPE = ArmourType::UNARMOURED;
	static constexpr int16_t HEALERARMOUR = 0;
	static constexpr Faction HEALERFACTION = Faction::ALIVE;
	static constexpr UnitType HEALERUNITTYPE = UnitType::HEALER;
};

