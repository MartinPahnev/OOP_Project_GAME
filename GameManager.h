#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <cctype>
#include "Base.h"
#include "Army.h"
#include "Duel.h"

class GameManager
{
public:
    GameManager();
    ~GameManager();

    void initialize(const std::string& configFilePath);

    void run();

    bool saveGame(const std::string& saveFilePath) const;

    bool loadGame(const std::string& saveFilePath);

    void restart();

private:

    static std::vector<std::string> tokenizeCommand(const std::string& input);

    static bool parseInt(const std::string& str, int& out);

    void handleCommand(const std::string& commandLine);

    void displayMenu() const;

    bool loadConfig(const std::string& configFilePath);

    void returnSurvivorsToBase(Base& base, Army& army);

    void loadUndeadWaves(const std::string& filename);
    void autoSelectUndeadUnits();

    void spawnCurrentWave();
    void checkAndSpawnNextWave();

    void prepareToSave();

    uint16_t checkWinCondition() const;

    Base livingBase;
    Base undeadBase;

    Army livingArmy;
    Army undeadArmy;

    Duel currentDuel;

    uint16_t livingDuelWins;
    uint16_t undeadDuelWins;

    bool isGameRunning;

    std::string originalConfigPath;

    std::vector<std::vector<std::string>> undeadWaves;
    size_t currentWaveIndex = 0;

    uint16_t bossesCreated = 0;

};
