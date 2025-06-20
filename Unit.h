#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <new>
#include <ctime>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <chrono>
#include <iostream>

//This could beheld in a simple bool, but then future "expansions" with new factions would call for a very sizeable code rework
enum class Faction : uint16_t
{
	NONE = 0,
	ALIVE = 1,
	UNDEAD = 2
};

enum class ArmourType : uint16_t
{
	UNARMOURED = 0,
	LEATHER = 1,
	MEDIUM = 2,
	HEAVY = 3
};

//Having the different units as non-boss under 100 and boss above 100 lets use double-use the field for both saving a "name"
//and being able to have a pseudo "isBoss" field for future logic
enum class UnitType :uint16_t
{
	NONE = 0,

	SKELETON = 1,
	GHOUL = 2,
	NECROMANCER = 3,
	ZOMBIE = 4,
	DIBBUK = 5,
	REVENANT = 6,
	GHOST = 7,

	INFANTRY = 10,
	ARCHER = 11,
	KNIGHT = 12,
	HEALER = 13,
	WIZARD = 14,

	LICH = 100, 
	DARKLORD = 101,
	DEATHKNIGHT = 102,

	UNDEADHUNTER = 110,
	BLADEDANCER = 111,
	PALADIN = 112	
};

UnitType getUnitTypeFromString(std::string s);

class Unit
{
public:

	Unit() = delete;

	Unit(int16_t health, int16_t maxHealth,
		 int16_t attackDamage,
		 int16_t armour, ArmourType armourType,
		 Faction faction,		
		 UnitType unitType);

	Unit(const Unit& other) = default;
	Unit& operator=(const Unit& other) = default;

	/*Unit(Unit&& other);
	Unit& operator=(Unit&& other);*/

	virtual ~Unit() = default;

public:

	inline bool isBoss() const { return static_cast<uint16_t>(_unitType) >= 100; }
	static inline bool isBossStatic(UnitType type) { return static_cast<uint16_t>(type) >= 100; };

	void changeHealth(int16_t value);
	inline int16_t getCurrentHealth() const { return _health; }
	int16_t getMaxHealth() const { return _maxHealth; }
	
	int16_t getAttackDamage() const { return _attackDamage; }

	int16_t getCurrentArmour() const { return _armour; }
	inline void reduceArmour() { if(_armour > 0) --_armour; }

	inline ArmourType getArmourType() const { return _armourType; }
	
	UnitType getUnitType() const { return _unitType; }
	Faction getFaction() const { return _faction; }
	
	virtual std::string getName() const = 0;
	//override in ghost
	virtual bool isAlive() const { return _health > 0; }

	virtual void attack(Unit* otherUnit);

	//used when resetting bosses
	virtual void resetToMaxStats() {};

protected:
	
	void takeDamage(int16_t amount);
	int16_t calculateDamage(Unit* otherUnit, int16_t amount) const;

	int16_t _health, _maxHealth;	
	int16_t _attackDamage;
	int16_t _armour;
	ArmourType _armourType;
	Faction _faction;
	UnitType _unitType;
};
