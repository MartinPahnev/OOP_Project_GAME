#include "Revenant.h"


Revenant::Revenant()
	: Zombie(REVENANTHEALTH)
{}

std::string Revenant::getName() const
{
	return std::string("Revenant");
}