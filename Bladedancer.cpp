#include "Bladedancer.h"

Bladedancer::Bladedancer()
    :AliveUnit(BLADEDANCERHEALTH, BLADEDANCERHEALTH, BLADEDANCERATTACKDAMAGE,
        BLADEDANCERARMOUR, BLADEDANCERARMOURTYPE, BLADEDANCERFACTION, BLADEDANCERUNITTYPE)    
{
    name = BossNameManager::getInstance().getNextName(BLADEDANCERUNITTYPE);

}

Bladedancer::Bladedancer(std::string newName, int16_t health, int16_t damage, int16_t armourDurability,
    ArmourType armourType,
    Faction faction, UnitType unitType)
    : AliveUnit(health, BLADEDANCERHEALTH, damage, armourDurability, armourType, faction, unitType)
{
    name = newName;
}

void Bladedancer::saveToFile(std::ofstream& ofs) const
{
    ofs << static_cast<int>(_unitType) << ' '
        << _health << ' '
        << _maxHealth << ' '
        << _attackDamage << ' '
        << static_cast<int>(_armour) << ' '
        << '"' << name << '"' << '\n';
}

std::string Bladedancer::getName() const
{
    return name;
}

void Bladedancer::resetToMaxStats()
{
    _health = BLADEDANCERHEALTH;
    _armour = BLADEDANCERARMOUR;
}

