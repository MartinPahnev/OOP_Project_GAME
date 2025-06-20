#pragma once
#include "AliveUnit.h"
#include "ManaPool.h"
#include "BossNameManager.h"
#include "BossSaveInterface.h"

class UndeadHunter :
    public AliveUnit, public ManaPool, public BossSaveInterface
{
public:

	UndeadHunter();

	UndeadHunter(std::string newName, int16_t health, int16_t damage, int16_t armourDurability, int16_t mana, ArmourType armourType = UNDEADHUNTERARMOURTYPE,
		Faction faction = UNDEADHUNTERFACTION, UnitType unitType = UNDEADHUNTERUNITTYPE,
		int16_t abilityCost = UNDEADHUNTERABILITYCOST);

	void saveToFile(std::ofstream& ofs) const override;

	std::string getName() const override;

	// Inherited via ManaPool
	void castAbility(Unit* target) override;

	void resetToMaxStats() override;

private:

	static constexpr int16_t UNDEADHUNTERHEALTH = 2000;
	static constexpr int16_t UNDEADHUNTERMANA = 1500;
	static constexpr int16_t UNDEADHUNTERABILITYCOST = 1000;
	static constexpr int16_t UNDEADHUNTERATTACKDAMAGE = 75;
	static constexpr ArmourType UNDEADHUNTERARMOURTYPE = ArmourType::HEAVY;
	static constexpr int16_t UNDEADHUNTERARMOUR = 17;
	static constexpr Faction UNDEADHUNTERFACTION = Faction::ALIVE;
	static constexpr UnitType UNDEADHUNTERUNITTYPE = UnitType::UNDEADHUNTER;

	std::string name;

};
