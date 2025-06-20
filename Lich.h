#pragma once
#include "UndeadUnit.h"
#include "ManaPool.h"
#include "BossNameManager.h"
#include "BossSaveInterface.h"


class Lich : public UndeadUnit, public ManaPool, public BossSaveInterface
{
public:

	Lich();

	Lich(std::string newName, int16_t health, int16_t damage, int16_t armourDurability, int16_t mana, ArmourType armourType = LICHARMOURTYPE,
		Faction faction = LICHFACTION, UnitType unitType = LICHUNITTYPE,
		int16_t abilityCost = LICHABILITYCOST);

	void saveToFile(std::ofstream& ofs) const override;

	std::string getName() const override;

	// Inherited via ManaPool
	void castAbility(Unit* target) override;

	void resetToMaxStats() override;

private:

	static constexpr int16_t LICHHEALTH = 1500;
	static constexpr int16_t LICHMANA = 1000;
	static constexpr int16_t LICHABILITYCOST = 750;
	static constexpr int16_t LICHATTACKDAMAGE = 100;
	static constexpr ArmourType LICHARMOURTYPE = ArmourType::HEAVY;
	static constexpr int16_t LICHARMOUR = 15;
	static constexpr Faction LICHFACTION = Faction::UNDEAD;
	static constexpr UnitType LICHUNITTYPE = UnitType::LICH;

	std::string name;
	
};

