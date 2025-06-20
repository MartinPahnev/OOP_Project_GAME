#include "Paladin.h"

Paladin::Paladin()
    :AliveUnit(PALADINHEALTH, PALADINHEALTH, PALADINATTACKDAMAGE,
        PALADINARMOUR, PALADINARMOURTYPE, PALADINFACTION, PALADINUNITTYPE),
    ManaPool(PALADINMANA, PALADINMANA, PALADINABILITYCOST)
{
    name = BossNameManager::getInstance().getNextName(PALADINUNITTYPE);
}

Paladin::Paladin(std::string newName, int16_t health, int16_t damage, int16_t armourDurability, int16_t mana, ArmourType armourType,
    Faction faction, UnitType unitType, int16_t abilityCost)
    :AliveUnit(health, PALADINHEALTH, damage, armourDurability, armourType, faction, unitType), ManaPool(mana,PALADINMANA, abilityCost)
{
    name = newName;
}

void Paladin::saveToFile(std::ofstream& ofs) const
{
    ofs << static_cast<int>(_unitType) << ' '
        << _health << ' '
        << _maxHealth << ' '
        << _attackDamage << ' '
        << static_cast<int>(_armour) << ' '
        << _mana << ' '
        << '"' << name << '"' << '\n';;
}

std::string Paladin::getName() const
{
    return name;
}

void Paladin::castAbility(Unit* target)
{
    _mana -= getAbilityCost();
    target->changeHealth(1000);
}

void Paladin::resetToMaxStats()
{
    _health = PALADINHEALTH;
    _armour = PALADINARMOUR;
    _maxMana = PALADINMANA;
}
