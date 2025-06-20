#include "Lich.h"

Lich::Lich()
    :UndeadUnit(LICHHEALTH, LICHHEALTH, LICHATTACKDAMAGE,
        LICHARMOUR, LICHARMOURTYPE, LICHFACTION, LICHUNITTYPE),
    ManaPool(LICHMANA, LICHMANA, LICHABILITYCOST)
{
    name = BossNameManager::getInstance().getNextName(LICHUNITTYPE);
}

Lich::Lich(std::string newName, int16_t health, int16_t damage, int16_t armourDurability, int16_t mana, ArmourType armourType,
    Faction faction, UnitType unitType, int16_t abilityCost)
    :UndeadUnit(health, LICHHEALTH, damage, armourDurability, armourType,faction,unitType), ManaPool(mana, LICHMANA, abilityCost)
{
    name = newName;
}

void Lich::saveToFile(std::ofstream& ofs) const
{
    ofs << static_cast<int>(_unitType) << ' '
        << _health << ' '
        << _maxHealth << ' '
        << _attackDamage << ' '
        << static_cast<int>(_armour) << ' '
        << _mana << ' '
        << '"' << name << '"' << '\n';;
}

std::string Lich::getName() const
{
    return name;
}

void Lich::castAbility(Unit* target)
{
    _mana -= getAbilityCost();
}

void Lich::resetToMaxStats()
{
    _health = LICHHEALTH;
    _armour = LICHARMOUR;
    _maxMana = LICHMANA;
}
