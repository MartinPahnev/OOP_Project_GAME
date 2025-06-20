#pragma once
#include "UndeadUnit.h"
#include "ManaPool.h"
#include "BossNameManager.h"
#include "BossSaveInterface.h"

class DeathKnight :
    public UndeadUnit, public ManaPool, public BossSaveInterface
{
public:

	DeathKnight();

	DeathKnight(std::string newName,int16_t health, int16_t damage, int16_t armourDurability, int16_t mana,ArmourType armourType = DEATHKNIGHTARMOURTYPE,
		Faction faction = DEATHKNIGHTFACTION, UnitType unitType = DEATHKNIGHTUNITTYPE,
		int16_t abilityCost = DEATHKNIGHTABILITYCOST);

	~DeathKnight();

	void saveToFile(std::ofstream& ofs) const override;

	std::string getName() const override;

	// Inherited via ManaPool
	void castAbility(Unit* target) override;

	void resetToMaxStats() override;

	static int16_t deathKnightCount;
private:

	static constexpr int16_t DEATHKNIGHTHEALTH = 2500;
	static constexpr int16_t DEATHKNIGHTMANA = 1000;
	static constexpr int16_t DEATHKNIGHTABILITYCOST = 350;
	static constexpr int16_t DEATHKNIGHTATTACKDAMAGE = 150;
	static constexpr ArmourType DEATHKNIGHTARMOURTYPE = ArmourType::HEAVY;
	static constexpr int16_t DEATHKNIGHTARMOUR = 15;
	static constexpr Faction DEATHKNIGHTFACTION = Faction::UNDEAD;
	static constexpr UnitType DEATHKNIGHTUNITTYPE = UnitType::DEATHKNIGHT;

	std::string name;

};