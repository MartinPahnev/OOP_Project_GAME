#include "DeathKnight.h"

int16_t DeathKnight::deathKnightCount = 0;

DeathKnight::DeathKnight()
    :UndeadUnit(DEATHKNIGHTHEALTH, DEATHKNIGHTHEALTH, DEATHKNIGHTATTACKDAMAGE,
        DEATHKNIGHTARMOUR, DEATHKNIGHTARMOURTYPE, DEATHKNIGHTFACTION, DEATHKNIGHTUNITTYPE),
    ManaPool(DEATHKNIGHTMANA, DEATHKNIGHTMANA,DEATHKNIGHTABILITYCOST)
{
    name = BossNameManager::getInstance().getNextName(DEATHKNIGHTUNITTYPE);
    deathKnightCount++;
}

DeathKnight::DeathKnight(std::string newName, int16_t health, int16_t damage, int16_t armourDurability,  int16_t mana, ArmourType armourType,
    Faction faction, UnitType unitType, int16_t abilityCost)
    :UndeadUnit(health, DEATHKNIGHTHEALTH, damage, armourDurability, armourType, faction, unitType), ManaPool(mana,DEATHKNIGHTMANA, abilityCost)
{
    name = newName;
    deathKnightCount++; 
}
DeathKnight::~DeathKnight()
{
    deathKnightCount--;
}

void DeathKnight::saveToFile(std::ofstream& ofs) const
{
    ofs << static_cast<int>(_unitType) << ' '
        << _health << ' '
        << _maxHealth << ' '
        << _attackDamage << ' '
        << static_cast<int>(_armour) << ' '
        << _mana << ' '
        << '"' << name << '"' << '\n';;
}

std::string DeathKnight::getName() const
{
    return name;
}

void DeathKnight::castAbility(Unit* target)
{
    //no value for heal in dk's description...
    target->changeHealth(500);
}

void DeathKnight::resetToMaxStats()
{
    _health = DEATHKNIGHTHEALTH;
    _armour = DEATHKNIGHTARMOUR;
    _maxMana = DEATHKNIGHTMANA;
}
