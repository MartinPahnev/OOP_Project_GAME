#pragma once
#include "AliveUnit.h"
#include "BossNameManager.h"
#include "BossSaveInterface.h"
class Bladedancer :
    public AliveUnit, public BossSaveInterface
{
public:

	Bladedancer();

	Bladedancer(std::string newName, int16_t health, int16_t damage, int16_t armourDurability,
		ArmourType armourType = BLADEDANCERARMOURTYPE,
		Faction faction = BLADEDANCERFACTION,
		UnitType unitType = BLADEDANCERUNITTYPE);

	
	void saveToFile(std::ofstream& ofs) const override;

	std::string getName() const override;

	void resetToMaxStats() override;

private:

	static constexpr int16_t BLADEDANCERHEALTH = 2000;
	static constexpr int16_t BLADEDANCERATTACKDAMAGE = 75;
	static constexpr ArmourType BLADEDANCERARMOURTYPE = ArmourType::MEDIUM;
	static constexpr int16_t BLADEDANCERARMOUR = 17;
	static constexpr Faction BLADEDANCERFACTION = Faction::ALIVE;
	static constexpr UnitType BLADEDANCERUNITTYPE = UnitType::BLADEDANCER;

	std::string name;

};


