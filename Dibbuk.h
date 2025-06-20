#pragma once
#include "Zombie.h"
#include "ManaPool.h"
class Dibbuk :
    public Zombie, public ManaPool
{
public:
	Dibbuk();

	// Inherited via UndeadUnit
	std::string getName() const override;
	
	// Inherited via ManaPool
	void castAbility(Unit* target) override;

private:
	static constexpr int16_t DIBBUKMANA = 300;
	static constexpr int16_t DIBBUKABILITYCOST = 150;

	
};
