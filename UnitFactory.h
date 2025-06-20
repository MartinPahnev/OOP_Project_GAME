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

#include "UnitCounter.h"

class UnitFactory
{
public:
    static void printLivingUnitCosts();
    static Unit* create(UnitType type);
};
