#pragma once

#include <vector>
#include <cstdint>
#include "Unit.h"
#include "Army.h"
#include "UnitFactory.h"
#include "UnitCostHelper.h"

class Base
{
public:
	
	Base();
	Base(int32_t startingGold);

	Base(const Base&) = delete;
	Base& operator=(const Base&) = delete;

	Base(Base&& other) = delete;
	Base& operator=(Base&& other) = delete;

	bool hireUnit(UnitType type);
	int32_t getGold() const { return _gold; };
	void setGold(int32_t goldAmount) { _gold = goldAmount; };

	bool spendGold(int32_t amount);

	void addUnit(Unit* unit);
	Unit* getUnit(size_t index) const;
	size_t getUnitCount() const;

		
	void addGold(int32_t amount);

	bool transferUnitToArmy(Unit* unit, Army& targetArmy);

	const std::vector<Unit*>& getReserveUnits() const;

	size_t getReserveSize() const { return reserveUnits.size(); };
	void saveBosses(std::ofstream& ofs) const;

	void loadBosses(std::ifstream& ifs);

	void reset();

	void emptyUnits();
private:

	void stripQuotes(std::string& s);
	void trim(std::string& s);
	static constexpr int32_t BASESTARTINGGOLD = 1000;

	int32_t _gold;

	std::vector<Unit*> reserveUnits;

	Unit* createUnitByType(UnitType type);
	
	void deleteReserve();
};

