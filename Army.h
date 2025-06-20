#pragma once
#include <vector>
#include "Unit.h"
#include "UnitFactory.h"
#include "ManaPool.h"
#include "BossSaveInterface.h"

class Army
{
public:
    Army() = default;
    ~Army();

    void addUnit(Unit* unit);
    bool removeUnit(Unit* unit);

    size_t getUnitCount() const;
    Unit* getUnit(size_t index) const;

    Unit* getUnitAt(size_t index) const { return units[index]; };

    void reset();

    void clear();
   
    void attack(Army* otherArmy);
    void useAllAbilities(Army* otherArmy);
    void ressurectUnits(std::vector<Unit*>& deadUnits);

    bool isArmyEmpty() const { return units.size() == 0; };

    std::vector<Unit*>& getDeadUnits(); 
    void removeDeadUnits(); 

    bool isAllGhosts() const;
private:

    std::vector<Unit*> deadUnits;

    std::vector<Unit*> units;
};
