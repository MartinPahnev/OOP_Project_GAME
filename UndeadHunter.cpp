#include "UndeadHunter.h"

UndeadHunter::UndeadHunter()
    :AliveUnit(UNDEADHUNTERHEALTH, UNDEADHUNTERHEALTH, UNDEADHUNTERATTACKDAMAGE,
        UNDEADHUNTERARMOUR, UNDEADHUNTERARMOURTYPE, UNDEADHUNTERFACTION, UNDEADHUNTERUNITTYPE),
    ManaPool(UNDEADHUNTERMANA,UNDEADHUNTERMANA, UNDEADHUNTERABILITYCOST)
{
    name = BossNameManager::getInstance().getNextName(UNDEADHUNTERUNITTYPE);
}

UndeadHunter::UndeadHunter(std::string newName, int16_t health, int16_t damage, int16_t armourDurability,  int16_t mana, ArmourType armourType,
    Faction faction, UnitType unitType, int16_t abilityCost)
    :AliveUnit(health, UNDEADHUNTERHEALTH, damage, armourDurability, armourType, faction, unitType), ManaPool(mana,UNDEADHUNTERMANA, abilityCost)
{
    name = newName;
}

void UndeadHunter::saveToFile(std::ofstream& ofs) const
{
    ofs << static_cast<int>(_unitType) << ' '
        << _health << ' '
        << _maxHealth << ' '
        << _attackDamage << ' '
        << static_cast<int>(_armour) << ' '
        << _mana << ' '
        << '"' << name << '"' << '\n';;
}

std::string UndeadHunter::getName() const
{
    return name;
}

void UndeadHunter::castAbility(Unit* target)
{
    //guarantees oneshot regardless of armour
    target->changeHealth(-32768);
}

void UndeadHunter::resetToMaxStats()
{
    _health = UNDEADHUNTERHEALTH;
    _armour = UNDEADHUNTERARMOUR;
    _maxMana = UNDEADHUNTERMANA;
}
