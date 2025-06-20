#pragma once
#include "UndeadUnit.h"
class Zombie :
    public UndeadUnit
{
public:
	Zombie();

	// Inherited via UndeadUnit
	std::string getName() const override;

	static constexpr uint16_t ZOMBIEGOLDCOST = 300;

protected:
	Zombie(int16_t health);
	
private:
	static constexpr int16_t ZOMBIEHEALTH = 250;
	static constexpr int16_t ZOMBIEATTACKDAMAGE = 15;
	static constexpr ArmourType ZOMBIEARMOURTYPE = ArmourType::UNARMOURED;
	static constexpr int16_t ZOMBIEARMOUR = 0;
	static constexpr Faction ZOMBIEFACTION = Faction::UNDEAD;
	static constexpr UnitType ZOMBIEUNITTYPE = UnitType::ZOMBIE;
};