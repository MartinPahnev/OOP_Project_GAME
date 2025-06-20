#pragma once
#include "Zombie.h"
class Revenant :
    public Zombie
{
public:
	Revenant();

	// Inherited via UndeadUnit
	std::string getName() const override;
private:
	static constexpr int16_t REVENANTHEALTH = 600;

};

