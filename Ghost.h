#pragma once
#include "UndeadUnit.h"
#include "ManaPool.h"
class Ghost :
    public UndeadUnit, public ManaPool
{
public:
	Ghost();

	// Inherited via UndeadUnit
	std::string getName() const override;
	virtual bool isAlive() const override;

	// Inherited via ManaPool
	void castAbility(Unit* target) override;

	static constexpr uint16_t GHOSTGOLDCOST = 500;



private:
	bool hasSuicided = false;
	static constexpr int16_t GHOSTHEALTH = 0;
	static constexpr int16_t GHOSTMANA = 0;
	static constexpr int16_t GHOSTABILITYCOST = 0;
	static constexpr int16_t GHOSTATTACKDAMAGE = 0;
	static constexpr ArmourType GHOSTARMOURTYPE = ArmourType::UNARMOURED;
	static constexpr int16_t GHOSTARMOUR = 0;
	static constexpr Faction GHOSTFACTION = Faction::UNDEAD;
	static constexpr UnitType GHOSTUNITTYPE = UnitType::GHOST;
};

