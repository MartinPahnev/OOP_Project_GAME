#include "UndeadUnit.h"

UndeadUnit::UndeadUnit(
	int16_t health,int16_t maxHealth,
	int16_t attackDamage,
	int16_t armour, ArmourType armourType,
	Faction faction, UnitType unitType)
	:Unit(health, maxHealth,
		attackDamage,
		armour, armourType,
		faction, unitType) {}
