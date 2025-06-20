#pragma once
#include <stdint.h>
#include "Unit.h"
class ManaPool
{
public:

	ManaPool(int16_t mana,int16_t maxMana,int16_t abilityCost);
	inline int16_t getMaxMana() const { return _maxMana; }
	inline int16_t getCurrentMana() const { return _mana; };
	inline int16_t getAbilityCost() const { return _abilityCost; };
	virtual void castAbility(Unit* target) = 0;

protected:
	int16_t _mana;
	int16_t _maxMana;
	int16_t _abilityCost;
};

