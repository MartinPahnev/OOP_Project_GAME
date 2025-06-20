#pragma once
#include "UndeadUnit.h"
class Skeleton :
    public UndeadUnit
{
public:
	Skeleton();

	// Inherited via UndeadUnit
	std::string getName() const override;

	static constexpr uint16_t SKELETONGOLDCOST = 100;

private:
	static constexpr int16_t SKELETONHEALTH = 500;
	static constexpr int16_t SKELETONATTACKDAMAGE = 5;
	static constexpr ArmourType SKELETONARMOURTYPE = ArmourType::MEDIUM;
	static constexpr int16_t SKELETONARMOUR = 8;
	static constexpr Faction SKELETONFACTION = Faction::UNDEAD;
	static constexpr UnitType SKELETONUNITTYPE = UnitType::SKELETON;

};

