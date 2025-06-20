#include "BossNameManager.h"

BossNameManager* BossNameManager::_instance = nullptr;

BossNameManager& BossNameManager::getInstance()
{
    if (_instance == nullptr)
        throw std::runtime_error("BossNameManager instance not created yet");
    return *_instance;
}

void BossNameManager::createInstance(const std::string& filename)
{
    if (_instance != nullptr)
        throw std::runtime_error("BossNameManager instance already created");

    _instance = new BossNameManager(filename);
}

void BossNameManager::loadNamesFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file)
        throw std::runtime_error("Failed to open boss names file: " + filename);

    _unitTypes.clear();
    _names.clear();
    _usedNames.clear();

    std::string line;
    UnitType currentType = UnitType::NONE;

    while (std::getline(file, line)) {
        trim(line);
        if (line.empty()) continue;

        if (line.front() == '[' && line.back() == ']') {
            std::string typeStr = line.substr(1, line.size() - 2);
            currentType = stringToUnitType(typeStr);
            _unitTypes.push_back(currentType);
            _names.emplace_back();
            _usedNames.emplace_back();
        }
        else if (currentType != UnitType::NONE) {
            _names.back().push_back(line);
            _usedNames.back().push_back(false);
        }
    }
}

std::string BossNameManager::getNextName(UnitType type)
{
    int idx = findUnitTypeIndex(type);
    if (idx == -1) throw std::invalid_argument("Invalid unit type");

    for (size_t i = 0; i < _names[idx].size(); ++i)
    {
        if (!_usedNames[idx][i])
        {
            _usedNames[idx][i] = true;
            return _names[idx][i];
        }
    }

    throw std::runtime_error("No free boss names available for this type");
}
BossNameManager::BossNameManager(const std::string& filename)
{
    loadNamesFromFile(filename);
}

void BossNameManager::returnName(UnitType type, const std::string& name)
{
    int idx = findUnitTypeIndex(type);
    if (idx == -1) throw std::invalid_argument("Invalid unit type");

    auto& names = _names[idx];
    auto& used = _usedNames[idx];

    for (size_t i = 0; i < names.size(); ++i)
    {
        if (names[i] == name)
        {
            if (!used[i])
                throw std::runtime_error("Name already free");
            used[i] = false;
            return;
        }
    }
    throw std::runtime_error("Name not found in pool");
}

void BossNameManager::destroyInstance()
{
    delete _instance;
    _instance = nullptr;
}

bool BossNameManager::isNameRegistered(const std::string& name) const {
    for (const auto& namesVec : _names) {
        for (const auto& n : namesVec) {
            if (n == name) return true;
        }
    }
    return false;
}

void BossNameManager::registerName(const std::string& name) {
    for (size_t i = 0; i < _names.size(); ++i) {
        for (size_t j = 0; j < _names[i].size(); ++j) {
            if (_names[i][j] == name) {
                _usedNames[i][j] = true;
                return;
            }
        }
    }
}


int BossNameManager::findUnitTypeIndex(UnitType type)
{
    for (size_t i = 0; i < _unitTypes.size(); ++i)
        if (_unitTypes[i] == type)
            return static_cast<int>(i);
    return -1;
}

void BossNameManager::trim(std::string& s)
{
    size_t start = 0;
    while (start < s.size() && (s[start] == ' ' || s[start] == '\t'))
        ++start;

    size_t end = s.size();
    while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t'))
        --end;

    s = s.substr(start, end - start);
}

UnitType BossNameManager::stringToUnitType(const std::string& str)
{
    if (str == "LICH") return UnitType::LICH;
    if (str == "DARKLORD") return UnitType::DARKLORD;
    if (str == "DEATHKNIGHT") return UnitType::DEATHKNIGHT;
    if (str == "UNDEADHUNTER") return UnitType::UNDEADHUNTER;
    if (str == "BLADEDANCER") return UnitType::BLADEDANCER;
    if (str == "PALADIN") return UnitType::PALADIN;
    else throw std::runtime_error("Reading incorrect unit type");
}
