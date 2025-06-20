#include <iostream>
#include <fstream>
#include <string>
#include "GameManager.h"
#include "BossNameManager.h"


int main()
{
    const std::string configPath = "config.txt";

    try
    {
        // GameManager setup and run
        GameManager game;
        game.initialize(configPath);
        game.run();
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Fatal error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}