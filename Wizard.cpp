#include "Wizard.h"

Wizard::Wizard()
    : AliveUnit(WIZARDHEALTH, WIZARDHEALTH, WIZARDATTACKDAMAGE,
        WIZARDARMOUR, WIZARDARMOURTYPE, WIZARDFACTION, WIZARDUNITTYPE),
      ManaPool(WIZARDMANA, WIZARDMANA, WIZARDABILITYCOST)
{}

std::string Wizard::getName() const
{
    return std::string("WIZARD");
}

void Wizard::castAbility(Unit* target)
{
    _mana -= getAbilityCost();
    attack(target);
}
