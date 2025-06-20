#include "Base.h"

Base::Base()
    :_gold(BASESTARTINGGOLD)
{}

Base::Base(int32_t startingGold = 1000)
    : _gold(startingGold) {}

bool Base::hireUnit(UnitType type) {
    int32_t cost = getUnitGoldCost(type);
    if (_gold < cost)
        return false;

    Unit* unit = createUnitByType(type);
    if (!unit)
        return false;

    _gold -= cost;
    reserveUnits.push_back(unit);
    return true;
}
size_t Base::getUnitCount() const
{
    return reserveUnits.size();
}


bool Base::transferUnitToArmy(Unit* unit, Army& targetArmy) {
    auto it = std::find(reserveUnits.begin(), reserveUnits.end(), unit);
    if (it == reserveUnits.end())
        return false;

    reserveUnits.erase(it);
    targetArmy.addUnit(unit);
    return true;
}

bool Base::spendGold(int32_t amount) {
    if (_gold < amount)
        return false;
    _gold -= amount;
    return true;
}

void Base::addUnit(Unit* unit)
{
    if (unit)
        reserveUnits.push_back(unit);
}
Unit* Base::getUnit(size_t index) const
{
    if (index < reserveUnits.size())
        return reserveUnits[index];
    return nullptr;
}
void Base::addGold(int32_t amount) {
    _gold += amount;
}

const std::vector<Unit*>& Base::getReserveUnits() const {
    return reserveUnits;
}

void Base::saveBosses(std::ofstream& ofs) const
{
    std::cout << "Saving bosses, army size: " << reserveUnits.size() << std::endl;
    int bossCount = 0;
    for (Unit* u : reserveUnits) {
        if (u->isBoss()) ++bossCount;
    }
    std::cout << "Boss units found: " << bossCount << std::endl;
    for (Unit* u : reserveUnits)
    {
        if (u->isBoss())
        {
            const BossSaveInterface* boss = dynamic_cast<const BossSaveInterface*>(u);
            if (boss)
            {
                boss->saveToFile(ofs);
            }
            else throw std::logic_error("To save non-boss unit");

        }
    }
    ofs << "\nEND\n";
}

void Base::stripQuotes(std::string& s) {
    if (!s.empty() && s.front() == '"' && s.back() == '"') {
        s = s.substr(1, s.size() - 2);
    }
}

void Base::trim(std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(s[start])) ++start;

    size_t end = s.size();
    while (end > start && std::isspace(s[end - 1])) --end;

    s = s.substr(start, end - start);
}

void Base::loadBosses(std::ifstream& ifs)
{
    while (true) {
        int unitTypeInt;
        if (!(ifs >> unitTypeInt))
            break;

        if (unitTypeInt == -1)  // sentinel
            break;

        UnitType unitType = static_cast<UnitType>(unitTypeInt);

        int16_t health = 0, maxHealth = 0, attackDamage = 0;
        int armourInt = 0;
        int16_t mana = 0;
        std::string name;

        if (unitType == UnitType::BLADEDANCER) {
            if (!(ifs >> health >> maxHealth >> attackDamage >> armourInt))
                break;

            uint16_t armour = static_cast<uint16_t>(armourInt);

            ifs >> std::ws;
            std::getline(ifs, name);
            stripQuotes(name);
            trim(name);

            Unit* boss = new Bladedancer(name, health, attackDamage, armour);
            reserveUnits.push_back(boss);
        }
        else {
            if (!(ifs >> health >> maxHealth >> attackDamage >> armourInt >> mana))
                break;

            uint16_t armour = static_cast<uint16_t>(armourInt);

            ifs >> std::ws;
            std::getline(ifs, name);
            stripQuotes(name);
            trim(name);

            Unit* boss = nullptr;
            switch (unitType) {
            case UnitType::LICH:
                boss = new Lich(name, health, attackDamage, armour, mana);
                break;
            case UnitType::DEATHKNIGHT:
                boss = new DeathKnight(name, health, attackDamage, armour, mana);
                break;
            case UnitType::DARKLORD:
                boss = new DarkLord(name, health, attackDamage, armour, mana);
                break;
            case UnitType::PALADIN:
                boss = new Paladin(name, health, attackDamage, armour, mana);
                break;
            case UnitType::UNDEADHUNTER:
                boss = new UndeadHunter(name, health, attackDamage, armour, mana);
                break;
            default:
                throw std::runtime_error("Unknown boss unit type during loading");
            }

            reserveUnits.push_back(boss);
        }
    }
}


Unit* Base::createUnitByType(UnitType type) {
    if (!UnitCounter::tryRegisterUnit(type)) {
        throw std::runtime_error("Unit limit reached");
    }
    return UnitFactory::create(type);
}

void Base::deleteReserve() {
    for (Unit* unit : reserveUnits)
        delete unit;
    reserveUnits.clear();
}

void Base::reset() {
    std::vector<Unit*> survivingBosses;

    for (Unit* unit : reserveUnits) {
        if (unit->isBoss()) {
            unit->resetToMaxStats();
            survivingBosses.push_back(unit);
        }
        else {
            delete unit;
        }
    }

    reserveUnits = std::move(survivingBosses);

    _gold = BASESTARTINGGOLD;
}

void Base::emptyUnits()
{
    for (size_t i = 0; i < reserveUnits.size(); ++i) {
        delete reserveUnits[i];
    }
    reserveUnits.clear();
}
