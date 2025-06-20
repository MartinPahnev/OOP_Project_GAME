#include "DarkLord.h"

DarkLord::DarkLord()
    :UndeadUnit(DARKLORDHEALTH, DARKLORDHEALTH, DARKLORDATTACKDAMAGE,
        DARKLORDARMOUR, DARKLORDARMOURTYPE, DARKLORDFACTION, DARKLORDUNITTYPE),
    ManaPool(DARKLORDMANA,DARKLORDMANA, DARKLORDABILITYCOSTNECROMANCER)
{
    name = BossNameManager::getInstance().getNextName(DARKLORDUNITTYPE);
}

DarkLord::DarkLord(std::string newName, int16_t health, int16_t damage, int16_t armourDurability,  int16_t mana, ArmourType armourType,
    Faction faction, UnitType unitType,
    int16_t abilityCost)
    :UndeadUnit(health,DARKLORDHEALTH, damage, armourDurability, armourType, faction, unitType), ManaPool(mana, DARKLORDMANA, abilityCost)
{
    name = newName;
}

void DarkLord::saveToFile(std::ofstream& ofs) const
{
    ofs << static_cast<int>(_unitType) << ' '
        << _health << ' '
        << _maxHealth << ' '
        << _attackDamage << ' '
        << static_cast<int>(_armour) << ' '
        << _mana << ' '
        << '"' << name << '"' << '\n';;
}

std::string DarkLord::getName() const
{
    return name;
}

void DarkLord::castAbility(Unit* target)
{
    if (target->getUnitType() == UnitType::NECROMANCER)
    {
        _mana -= DARKLORDABILITYCOSTNECROMANCER;
        return;
    }
    else if (target->getUnitType() == UnitType::GHOUL)
    {
        _mana -= DARKLORDABILITYCOSTGHOUL;
        return;
    }
    throw std::runtime_error("Failed to summon correct unit from DarkLord");

}

void DarkLord::resetToMaxStats()
{
    _health = DARKLORDHEALTH;
    _armour = DARKLORDARMOUR;
    _maxMana = DARKLORDMANA;
}
