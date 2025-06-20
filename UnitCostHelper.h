
#pragma once
#include "Skeleton.h"
#include "Ghoul.h"
#include "Necromancer.h"
#include "Zombie.h"
#include "Dibbuk.h"
#include "Revenant.h"
#include "Ghost.h"

#include "Infantry.h"
#include "Archer.h"
#include "Knight.h"
#include "Healer.h"
#include "Wizard.h"

#include "Lich.h"
#include "DarkLord.h"
#include "DeathKnight.h"

#include "UndeadHunter.h"
#include "BladeDancer.h"
#include "Paladin.h"

#include <stdexcept>

inline int16_t getUnitGoldCost(UnitType type) {
    switch (type) {
    case UnitType::SKELETON:      return Skeleton::SKELETONGOLDCOST;
    case UnitType::GHOUL:         return Ghoul::GHOULGOLDCOST;
    case UnitType::NECROMANCER:   return Necromancer::NECROMANCERGOLDCOST;
    case UnitType::ZOMBIE:        return Zombie::ZOMBIEGOLDCOST;
    case UnitType::DIBBUK:        return Zombie::ZOMBIEGOLDCOST;
    case UnitType::REVENANT:      return Zombie::ZOMBIEGOLDCOST;
    case UnitType::GHOST:         return Ghost::GHOSTGOLDCOST;

    case UnitType::INFANTRY:      return Infantry::INFANTRYGOLDCOST;
    case UnitType::ARCHER:        return Archer::ARCHERGOLDCOST;
    case UnitType::KNIGHT:        return Knight::KNIGHTGOLDCOST;
    case UnitType::HEALER:        return Healer::HEALERGOLDCOST;
    case UnitType::WIZARD:        return Wizard::WIZARDGOLDCOST;

    default:
        throw std::invalid_argument("Unknown or NONE UnitType passed to getUnitGoldCost()");
    }
}



