#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

#include "Unit.h"

class BossNameManager
{
public:
    static BossNameManager& getInstance();

    static void createInstance(const std::string& filename);
    

    BossNameManager(const BossNameManager&) = delete;
    BossNameManager& operator=(const BossNameManager&) = delete;

    void loadNamesFromFile(const std::string& filename);

    std::string getNextName(UnitType type);
    
    void returnName(UnitType type, const std::string& name);
    static void destroyInstance();
    bool isNameRegistered(const std::string& name) const;
    void registerName(const std::string& name);

private:
    BossNameManager(const std::string& filename);

    int findUnitTypeIndex(UnitType type);

    void trim(std::string& s);
    

    UnitType stringToUnitType(const std::string& str);
    

    std::vector<UnitType> _unitTypes;
    std::vector<std::vector<std::string>> _names;
    std::vector<std::vector<bool>> _usedNames;

    static BossNameManager* _instance;
};