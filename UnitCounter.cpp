#include "UnitCounter.h"

int32_t UnitCounter::currentUnitCount = 0;
int32_t UnitCounter::maxUnitLimit = 0;

void UnitCounter::initializeCounter(int limitFromConfig) {
    maxUnitLimit = limitFromConfig;
}

bool UnitCounter::tryRegisterUnit(UnitType type) {

    if (Unit::isBossStatic(type)) {
        return true; 
    }
    if (currentUnitCount >= maxUnitLimit) return false;
    ++currentUnitCount;
    return true;
}
void UnitCounter::decrement()
{
    --currentUnitCount;
}


void UnitCounter::increment()
{
    ++currentUnitCount;
}


void UnitCounter::unregisterUnit(UnitType type) {
    if (!Unit::isBossStatic(type)) {
        UnitCounter::decrement();
    }
}

int16_t UnitCounter::getCurrentCount() {
    return currentUnitCount;
}

int16_t UnitCounter::getMaxCount() {
    return maxUnitLimit;
}
