#pragma once
#include "ManaPool.h"
#include "AliveUnit.h"
class Wizard : public AliveUnit, public ManaPool
{

public:
	Wizard();
	// Inherited via AliveUnit
	std::string getName() const override;

	// Inherited via ManaPool
	void castAbility(Unit* target) override;

	static constexpr uint16_t WIZARDGOLDCOST = 250;

private:
	static constexpr int16_t WIZARDHEALTH = 325;
	static constexpr int16_t WIZARDMANA = 200;
	static constexpr int16_t WIZARDABILITYCOST = 50;
	static constexpr int16_t WIZARDATTACKDAMAGE = 10;
	static constexpr ArmourType WIZARDARMOURTYPE = ArmourType::LEATHER;
	static constexpr int16_t WIZARDARMOUR = 3;
	static constexpr Faction WIZARDFACTION = Faction::ALIVE;
	static constexpr UnitType WIZARDUNITTYPE = UnitType::WIZARD;
};
