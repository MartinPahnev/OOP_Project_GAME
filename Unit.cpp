#include "Unit.h"

Unit::Unit(
	int16_t health, int16_t maxHealth,	
	int16_t attackDamage,
	int16_t armour, ArmourType armourType,
	Faction faction,
	UnitType unitType)
	:
	_health(health), _maxHealth(maxHealth),	
	_attackDamage(attackDamage),
	_armour(armour), _armourType(armourType),
	_faction(faction), _unitType(unitType)
{
}

void Unit::changeHealth(int16_t value)
{
	if (value == 0) return;
	if (value < 0)
	{
		if (_health < -value)
		{
			_health = 0;
			return;
		}
	}
	else
	{
		if (_health + value > _maxHealth)
		{
			_health = _maxHealth;
			return;
		}
	}
	
}

void Unit::takeDamage(int16_t amount)
{
	if (amount >= _health) _health = 0;
	_health -= amount;
}

int16_t Unit::calculateDamage(Unit* otherUnit, int16_t amount) const
{
	if (otherUnit->getArmourType() == ArmourType::UNARMOURED || otherUnit->getCurrentArmour() == 0) return amount;
	float reduction = static_cast<int16_t>(otherUnit->getArmourType()) * 0.25f;
	float finalDamage = std::floor(amount * (1.0f - reduction));
	otherUnit->reduceArmour();
	return static_cast<int16_t>(std::max(1.0f, finalDamage));//preventing 0 dmg
}

void Unit::attack(Unit* otherUnit)
{
	if (otherUnit->getUnitType() == UnitType::GHOST) throw std::logic_error("attempting to attack a ghost!");
	int16_t calculatedAmount = calculateDamage(otherUnit,_attackDamage);
	otherUnit->takeDamage(calculatedAmount);

}

UnitType getUnitTypeFromString(std::string s)
{
	if (s == "SKELETON") return UnitType::SKELETON;
	else if (s == "GHOUL") return UnitType::GHOUL;
	else if (s == "NECROMANCER") return UnitType::NECROMANCER;
	else if (s == "ZOMBIE") return UnitType::ZOMBIE;
	else if (s == "DIBBUK") return UnitType::DIBBUK;
	else if (s == "REVENANT") return UnitType::REVENANT;
	else if (s == "GHOST") return UnitType::GHOST;

	else if (s == "INFANTRY") return UnitType::INFANTRY;
	else if (s == "ARCHER") return UnitType::ARCHER;
	else if (s == "KNIGHT") return UnitType::KNIGHT;
	else if (s == "HEALER") return UnitType::HEALER;
	else if (s == "WIZARD") return UnitType::WIZARD;

	else if (s == "PALADIN") return UnitType::PALADIN;
	else if (s == "UNDEADHUNTER") return UnitType::UNDEADHUNTER;
	else if (s == "BLADEDANCER") return UnitType::BLADEDANCER;
	else if (s == "LICH") return UnitType::LICH;
	else if (s == "DEATHKNIGHT") return UnitType::DEATHKNIGHT;
	else if (s == "DARKLORD") return UnitType::DARKLORD;
	else return UnitType::NONE;
}
