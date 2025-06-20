#pragma once
#include "UndeadUnit.h"
#include "ManaPool.h"
class Necromancer :  public UndeadUnit, public ManaPool
{
public:
	Necromancer();

	// Inherited via AliveUnit
	std::string getName() const override;

	// Inherited via ManaPool
	void castAbility(Unit* target) override;

	static constexpr uint16_t NECROMANCERGOLDCOST = 400;

private:
	static constexpr int16_t NECROMANCERHEALTH = 300;
	static constexpr int16_t NECROMANCERMANA = 200;
	static constexpr int16_t NECROMANCERABILITYCOST = 150;
	static constexpr int16_t NECROMANCERATTACKDAMAGE = 4;
	static constexpr ArmourType NECROMANCERARMOURTYPE = ArmourType::UNARMOURED;
	static constexpr int16_t NECROMANCERARMOUR = 0;
	static constexpr Faction NECROMANCERFACTION = Faction::UNDEAD;
	static constexpr UnitType NECROMANCERUNITTYPE = UnitType::NECROMANCER;
};

