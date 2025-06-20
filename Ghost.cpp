#include "Ghost.h"

Ghost::Ghost()
	:UndeadUnit(GHOSTHEALTH, GHOSTHEALTH, GHOSTATTACKDAMAGE,
		GHOSTARMOUR, GHOSTARMOURTYPE, GHOSTFACTION, GHOSTUNITTYPE), ManaPool(GHOSTMANA, GHOSTMANA, GHOSTABILITYCOST)
{
}

std::string Ghost::getName() const
{
	return std::string("Ghost");
}

bool Ghost::isAlive() const
{
	return hasSuicided;
}

void Ghost::castAbility(Unit* target)
{
	target->changeHealth(250);
	hasSuicided = true;
}
