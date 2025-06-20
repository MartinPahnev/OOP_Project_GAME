#include "Army.h"

Army::~Army()
{
	clear();
}
void Army::addUnit(Unit* unit)
{
    if (unit)
        units.push_back(unit);
}

bool Army::removeUnit(Unit* unit)
{
    for (auto it = units.begin(); it != units.end(); ++it)
    {
        if (*it == unit)
        {
            units.erase(it);
            return true;
        }
    }
    return false;
}

size_t Army::getUnitCount() const
{
    return units.size();
}

Unit* Army::getUnit(size_t index) const
{
    if (index < units.size())
        return units[index];
    return nullptr;
}


void Army::reset()
{
    for (Unit* unit : units) {
        if (unit->isBoss()) {
            unit->resetToMaxStats();
        }
        else {
            removeUnit(unit);
        }
    }
}


void Army::clear()
{
    for (Unit* u : units)
    {
        delete u;
    }
    units.clear();
}

void Army::attack(Army* otherArmy)
{
    if (!otherArmy || otherArmy->getUnitCount() == 0) return;

    size_t enemySize = otherArmy->getUnitCount();

    std::vector<size_t> attackableIndexes;
    attackableIndexes.reserve(enemySize);
    for (size_t i = 0; i < enemySize; ++i) {
        Unit* enemy = otherArmy->getUnitAt(i);
        if (enemy && enemy->isAlive() && enemy->getUnitType() != UnitType::GHOST) {
            attackableIndexes.push_back(i);
        }
    }

    for (size_t i = 0; i < getUnitCount(); ++i) {
        Unit* attacker = getUnitAt(i);
        if (!attacker || !attacker->isAlive() || attacker->getUnitType() == UnitType::GHOST) continue;

        UnitType type = attacker->getUnitType();

        if (type == UnitType::WIZARD || type == UnitType::DIBBUK)
        {
            ManaPool* attackerWithMana = dynamic_cast<ManaPool*>(attacker);
            if (attackerWithMana && attackerWithMana->getCurrentMana() > attackerWithMana->getAbilityCost())
            {
                size_t tries = attackableIndexes.size();
                while (tries > 0)
                {
                    size_t randIdx = rand() % attackableIndexes.size();
                    Unit* target = otherArmy->getUnitAt(attackableIndexes[randIdx]);

                    if (target && target->isAlive() && target->getUnitType() != UnitType::GHOST)
                    {
                        attackerWithMana->castAbility(target);
                        break;
                    }
                    else
                    {
                        attackableIndexes.erase(attackableIndexes.begin() + randIdx);
                    }

                    --tries;
                }
                continue;
            }
            continue;  
        }

        while (!attackableIndexes.empty()) {
            size_t randIdx = rand() % attackableIndexes.size();
            size_t enemyIndex = attackableIndexes[randIdx];
            Unit* target = otherArmy->getUnitAt(enemyIndex);

            if (!target || !target->isAlive()) {
                attackableIndexes.erase(attackableIndexes.begin() + randIdx);
                continue;
            }

            if (target->getUnitType() == UnitType::GHOST) {
                attackableIndexes.erase(attackableIndexes.begin() + randIdx);
                continue;
            }

            attacker->attack(target);
            break;
        }
    }
}

void Army::useAllAbilities(Army* otherArmy)
{
    if (!otherArmy) return;

    size_t ownSize = getUnitCount();
    size_t enemySize = otherArmy->getUnitCount();

    std::vector<size_t> ownAliveIndexes;
    ownAliveIndexes.reserve(ownSize);
    for (size_t i = 0; i < ownSize; ++i) {
        Unit* unit = getUnitAt(i);
        if (unit && unit->isAlive())
            ownAliveIndexes.push_back(i);
    }

    std::vector<size_t> enemyAttackableIndexes;
    enemyAttackableIndexes.reserve(enemySize);
    for (size_t i = 0; i < enemySize; ++i) {
        Unit* unit = otherArmy->getUnitAt(i);
        if (unit && unit->isAlive() && unit->getUnitType() != UnitType::GHOST)
            enemyAttackableIndexes.push_back(i);
    }

    for (size_t i = 0; i < ownSize; ++i) {
        Unit* caster = getUnitAt(i);
        if (!caster || !caster->isAlive()) continue;

        ManaPool* casterWithMana = dynamic_cast<ManaPool*>(caster);
        if (!casterWithMana) continue;

        UnitType type = caster->getUnitType();

        if (type == UnitType::HEALER)
        {
            if (ownAliveIndexes.empty()) continue;

            size_t randIdx = rand() % ownAliveIndexes.size();
            Unit* target = getUnitAt(ownAliveIndexes[randIdx]);

            if (target && target->isAlive() && target->getCurrentHealth() < target->getMaxHealth())
                casterWithMana->castAbility(target);
        }
        else if (type == UnitType::PALADIN || type == UnitType::DEATHKNIGHT)
        {
            if (ownAliveIndexes.empty()) continue;

            size_t randIdx = rand() % ownAliveIndexes.size();
            Unit* target = getUnitAt(ownAliveIndexes[randIdx]);

            if (target && target->getCurrentHealth() < target->getMaxHealth())
                casterWithMana->castAbility(target);
        }
        else if (type == UnitType::DARKLORD)
        {
            if (casterWithMana->getCurrentMana() >= DarkLord::DARKLORDABILITYCOSTGHOUL)
            {
                if (UnitCounter::tryRegisterUnit(UnitType::GHOUL))
                {
                    Unit* ghoul = UnitFactory::create(UnitType::GHOUL);
                    casterWithMana->castAbility(ghoul);
                    addUnit(ghoul);
                    continue;
                }              
            }
            else if (casterWithMana->getCurrentMana() >= DarkLord::DARKLORDABILITYCOSTNECROMANCER)
            {
                if (UnitCounter::tryRegisterUnit(UnitType::NECROMANCER))
                {
                    Unit* necromancer = UnitFactory::create(UnitType::NECROMANCER);
                    casterWithMana->castAbility(necromancer);
                    addUnit(necromancer);
                    continue;
                }
            }
        }
        else if (type == UnitType::UNDEADHUNTER)
        {
            for (size_t i = 0; i < otherArmy->getUnitCount(); ++i)
            {
                Unit* enemy = otherArmy->getUnitAt(i);
                if (enemy && enemy->isAlive() && enemy->isBoss())
                {
                    casterWithMana->castAbility(enemy);
                    break; 
                }
            }
        }
        else if(type == UnitType::NECROMANCER || type == UnitType::LICH)
        {
            continue;
        }
    }

}

void Army::ressurectUnits(std::vector<Unit*>& deadUnits)
{
    if (deadUnits.empty()) return;

    bool lichHasCast = false;
    size_t revenantsResurrected = 0;

    for (auto it = deadUnits.begin(); it != deadUnits.end(); )
    {
        Unit* dead = *it;
        if (dead->getUnitType() == UnitType::KNIGHT)
        {
            if ((rand() % 100) /*< 25*/)
            {
                if (DeathKnight::deathKnightCount < 7) {
                    addUnit(UnitFactory::create(UnitType::DEATHKNIGHT));
                    it = deadUnits.erase(it);
                    continue;
                }
            }
        }
        ++it;
    }

    for (size_t i = 0; i < getUnitCount(); ++i)
    {
        Unit* unit = getUnitAt(i);
        if (!unit || !unit->isAlive() || unit->getUnitType() != UnitType::LICH)
            continue;

        ManaPool* lich = dynamic_cast<ManaPool*>(unit);
        if (!lich || lich->getCurrentMana() < lich->getAbilityCost())
            continue;

        for (auto it = deadUnits.begin(); it != deadUnits.end() && revenantsResurrected < 6; )
        {
            addUnit(UnitFactory::create(UnitType::REVENANT));
            it = deadUnits.erase(it);
            ++revenantsResurrected;
        }

        if (revenantsResurrected > 0)
        {
            lich->castAbility(nullptr);
            lichHasCast = true;
        }
        break; 
    }

    
    for (size_t i = 0; i < getUnitCount(); ++i)
    {
        Unit* unit = getUnitAt(i);
        if (!unit || !unit->isAlive() || unit->getUnitType() != UnitType::NECROMANCER)
            continue;

        size_t skeletonsResurrected = 0;
        ManaPool* necro = dynamic_cast<ManaPool*>(unit);
        if (!necro || necro->getCurrentMana() < necro->getAbilityCost()) continue;

        for (auto it = deadUnits.begin(); it != deadUnits.end() && skeletonsResurrected < 3; )
        {
            addUnit(UnitFactory::create(UnitType::SKELETON));
            it = deadUnits.erase(it);
            ++skeletonsResurrected;
        }

        if (skeletonsResurrected > 0)
        {
            necro->castAbility(nullptr);
        }
    }
}

std::vector<Unit*>& Army::getDeadUnits()
{
    deadUnits.clear(); 
    for (auto it = units.begin(); it != units.end(); )
    {
        if (!(*it)->isAlive())
        {
            deadUnits.push_back(*it);
            it = units.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return deadUnits;
}

void Army::removeDeadUnits()
{
    auto it = units.begin();
    while (it != units.end())
    {
        Unit* unit = *it;
        if (!unit->isAlive())
        {
            if (unit->isBoss())
            {
                BossNameManager::getInstance().returnName(unit->getUnitType(), unit->getName());
            }
            delete unit;
            it = units.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

bool Army::isAllGhosts() const
{
    if (getUnitCount() == 0)
        return true; 

    for (size_t i = 0; i < getUnitCount(); ++i) {
        Unit* unit = getUnitAt(i);
        if (!unit || !unit->isAlive())
            continue; 

        if (unit->getUnitType() != UnitType::GHOST) 
            return false; 
    }
    return true; 
}