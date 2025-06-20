#pragma once
#include "AliveUnit.h"
#include "ManaPool.h"
#include "BossNameManager.h"
#include "BossSaveInterface.h"
class Paladin : 
    public AliveUnit, public ManaPool, public BossSaveInterface
{
public:

	Paladin();

	Paladin(std::string newName, int16_t health, int16_t damage, int16_t armourDurability,  int16_t mana, ArmourType armourType = PALADINARMOURTYPE,
		Faction faction = PALADINFACTION, UnitType unitType = PALADINUNITTYPE,
		int16_t abilityCost = PALADINABILITYCOST);

	void saveToFile(std::ofstream& ofs) const override;

	std::string getName() const override;

	// Inherited via ManaPool
	void castAbility(Unit* target) override;

	void resetToMaxStats() override;

private:

	static constexpr int16_t PALADINHEALTH = 5000;
	static constexpr int16_t PALADINMANA = 3000;
	static constexpr int16_t PALADINABILITYCOST = 500;
	static constexpr int16_t PALADINATTACKDAMAGE = 250;
	static constexpr ArmourType PALADINARMOURTYPE = ArmourType::HEAVY;
	static constexpr int16_t PALADINARMOUR = 20;
	static constexpr Faction PALADINFACTION = Faction::ALIVE;
	static constexpr UnitType PALADINUNITTYPE = UnitType::PALADIN;

	std::string name;
};

