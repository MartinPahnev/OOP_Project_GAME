#pragma once
#include "Unit.h"

class UnitCounter {
public:
    static void initializeCounter(int32_t limitFromConfig);
    static bool tryRegisterUnit(UnitType type);
    static void unregisterUnit(UnitType type);
    static int16_t getCurrentCount();
    static int16_t getMaxCount();

    static void increment();
    static void decrement();

private:
    static int currentUnitCount;
    static int maxUnitLimit;
};
