#include "Dibbuk.h"

Dibbuk::Dibbuk()
	: Zombie(), ManaPool(DIBBUKMANA, DIBBUKMANA, DIBBUKABILITYCOST)
{
}

std::string Dibbuk::getName() const
{
	return std::string("Dibbuk");
}

void Dibbuk::castAbility(Unit* target)
{
	_mana -= getAbilityCost();
	attack(target);
}
