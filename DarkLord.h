#pragma once
#include "UndeadUnit.h"
#include "ManaPool.h"
#include "BossNameManager.h"
#include "BossSaveInterface.h"

class DarkLord :
    public UndeadUnit, public ManaPool, public BossSaveInterface
{
public:

	DarkLord();

	DarkLord(std::string newName, int16_t health, int16_t damage, int16_t armourDurability, int16_t mana, ArmourType armourType = DARKLORDARMOURTYPE,
		Faction faction = DARKLORDFACTION, UnitType unitType = DARKLORDUNITTYPE,
		int16_t abilityCost = DARKLORDABILITYCOSTNECROMANCER);

	void saveToFile(std::ofstream& ofs) const override;

	std::string getName() const override;

	// Inherited via ManaPool
	void castAbility(Unit* target) override;

	static constexpr int16_t DARKLORDABILITYCOSTNECROMANCER = 400;
	static constexpr int16_t DARKLORDABILITYCOSTGHOUL = 500;

	void resetToMaxStats() override;

private:

	static constexpr int16_t DARKLORDHEALTH = 3000;
	static constexpr int16_t DARKLORDMANA = 2000;
	static constexpr int16_t DARKLORDATTACKDAMAGE = 200;
	static constexpr ArmourType DARKLORDARMOURTYPE = ArmourType::HEAVY;
	static constexpr int16_t DARKLORDARMOUR = 20;
	static constexpr Faction DARKLORDFACTION = Faction::UNDEAD;
	static constexpr UnitType DARKLORDUNITTYPE = UnitType::DARKLORD;

	std::string name;

};
