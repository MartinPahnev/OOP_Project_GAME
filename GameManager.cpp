#include "GameManager.h"

GameManager::GameManager()
	: livingDuelWins(0), undeadDuelWins(0), isGameRunning(false) {}

GameManager::~GameManager() {}

void GameManager::initialize(const std::string& configFilePath)
{
	originalConfigPath = configFilePath;
	if (!loadConfig(configFilePath)) {
		throw std::runtime_error("Failed to load configuration.");
	}
	isGameRunning = true;
	spawnCurrentWave();
}
void GameManager::checkAndSpawnNextWave() {
	if (undeadBase.getUnitCount() == 0 && currentWaveIndex + 1 < undeadWaves.size()) {
		++currentWaveIndex;
		spawnCurrentWave();
	}
}

void GameManager::autoSelectUndeadUnits()
{
	for (size_t i = 0; i < undeadBase.getUnitCount(); ) {
		Unit* unit = undeadBase.getUnit(i);
		undeadBase.transferUnitToArmy(unit, undeadArmy);
	}
}

void GameManager::prepareToSave()
{
	returnSurvivorsToBase(livingBase, livingArmy);
}

void GameManager::run()
{
	displayMenu();
	std::string commandLine;
	while (isGameRunning && std::getline(std::cin, commandLine)) {
		handleCommand(commandLine);
	}
}

bool GameManager::saveGame(const std::string& saveFilePath) const {
	std::ofstream out(saveFilePath);
	if (!out.is_open()) return false;

	out << (int)livingDuelWins << ' ' << (int)undeadDuelWins << '\n';
	out << livingBase.getGold() << ' ' << undeadBase.getGold() << '\n';
	out << currentWaveIndex << '\n';

	livingBase.saveBosses(out);

	return true;
}

bool GameManager::loadGame(const std::string& saveFilePath) {
	std::ifstream in(saveFilePath);
	if (!in.is_open()) return false;
	int waveIndex = 0;
	int16_t lWins, uWins;
	int32_t lGold, uGold;
	in >> lWins >> uWins >> lGold >> uGold >> waveIndex;
	livingDuelWins = lWins;
	undeadDuelWins = uWins;
	livingBase.setGold(lGold);

	currentWaveIndex = waveIndex;

	livingBase.loadBosses(in);

	bossesCreated = 0;
	auto bossNameMgr = &BossNameManager::getInstance();

	for (size_t i = 0; i < livingBase.getUnitCount(); ++i) {
		Unit* unit = livingBase.getUnit(i);
		if (unit->isBoss()) {
			++bossesCreated;
			bossNameMgr->registerName(unit->getName());
		}
	}


	undeadBase.emptyUnits();

	if (currentWaveIndex < undeadWaves.size()) {
		spawnCurrentWave();
	}
	else throw std::invalid_argument("Attempting to spawn an unexisting wave");
	return true;
}

void GameManager::restart() {
	livingDuelWins = 0;
	undeadDuelWins = 0;
	livingBase.reset();
	undeadBase.reset();
	livingArmy.reset();
	undeadArmy.reset();

	BossNameManager::destroyInstance();

	if (!loadConfig(originalConfigPath)) {
		std::cerr << "Failed to reload configuration during restart.\n";
		isGameRunning = false;
		return;
	}
	isGameRunning = true;
}

uint16_t GameManager::checkWinCondition() const
{
	if (undeadDuelWins >= 1)
		return 2;

	bool allWavesCleared = (currentWaveIndex >= undeadWaves.size() - 1) && (undeadBase.getUnitCount() == 0);

	if (allWavesCleared && livingDuelWins >= 1)
		return 1;

	return 0;
}

void GameManager::spawnCurrentWave() {
	if (currentWaveIndex >= undeadWaves.size()) {
		std::cerr << "All waves have been spawned.\n";
		return;
	}

	const auto& wave = undeadWaves[currentWaveIndex];
	for (const std::string& entry : wave) {
		if (entry.rfind("BOSS ", 0) == 0) {
			std::string bossType = entry.substr(5);
			Unit* boss = UnitFactory::create(getUnitTypeFromString(bossType));
			if (boss) {
				undeadBase.addUnit(boss);
			}
		}
		else {
			UnitType type = getUnitTypeFromString(entry);
			Unit* unit = UnitFactory::create(type);
			if (unit) {
				undeadBase.addUnit(unit);
			}
		}
	}

	std::cout << "Spawned Wave #" << (currentWaveIndex + 1) << "\n";
}


std::vector<std::string> GameManager::tokenizeCommand(const std::string& input) {
	std::vector<std::string> tokens;
	char buffer[256];
	strncpy_s(buffer, sizeof(buffer), input.c_str(), _TRUNCATE);

	char* context = nullptr;
	char* token = strtok_s(buffer, " ", &context);
	while (token) {
		tokens.emplace_back(token);
		token = strtok_s(nullptr, " ", &context);
	}

	return tokens;
}

bool GameManager::parseInt(const std::string& str, int& out) {
	if (str.empty()) return false;
	for (char c : str) if (c < '0' || c > '9') return false;
	out = std::atoi(str.c_str());
	return true;
}


void GameManager::displayMenu() const {
	std::cout << "\n=== Available Commands ===\n"
		<< "SAVE <file>            - Save the game state to a file\n"
		<< "LOAD <file>            - Load the game state from a file\n"
		<< "RESTART                - Restart the game and reload initial config\n"
		<< "EXIT                   - Exit the game (option to save first)\n"
		<< "MENU                   - Show this help menu\n"
		<< "STATUS                 - Display current gold amounts\n"
		<< "COSTS                  - Show cost for all living units\n"
		<< "\n--- Preparation Phase ---\n"
		<< "PREPARE                - Enter help mode\n"
		<< "CREATE <unit> [count]  - Hire unit(s) from the living faction\n"
		<< "SELECT <unit> <count>  - Select regular units for the duel\n"
		<< "SELECT BOSS <type>     - Create boss unit (if allowed)\n"
		<< "SELECT BOSSNAME <name> - Select an existing boss from your base\n"
		<< "\n--- Duel Phase ---\n"
		<< "DUEL <L> <U>           - Start duel (auto-selects undead units)\n"
		<< "\nCurrent Living Gold: " << livingBase.getGold() << "\n"
		<< "============================\n";
}

bool GameManager::loadConfig(const std::string& configFilePath) {
	std::ifstream file(configFilePath);
	if (!file.is_open()) {
		std::cerr << "Failed to open config file: " << configFilePath << "\n";
		return false;
	}

	int livingGold, undeadGold, unitLimit;
	std::string bossNamesFile;
	std::string undeadWavesFile;

	if (!(file >> livingGold >> undeadGold >> unitLimit)) {
		std::cerr << "Invalid format in config file (expected 3 values before filename)\n";
		return false;
	}

	file >> bossNamesFile;
	if (bossNamesFile.empty()) {
		std::cerr << "Boss names file missing from config\n";
		return false;
	}
	file >> undeadWavesFile;
	if (undeadWavesFile.empty()) {
		std::cerr << "Boss names file missing from config\n";
		return false;
	}
	loadUndeadWaves(undeadWavesFile);

	livingBase.setGold(livingGold);
	undeadBase.setGold(undeadGold);

	UnitCounter::initializeCounter(unitLimit);

	BossNameManager::createInstance(bossNamesFile);

	return true;
}

void GameManager::loadUndeadWaves(const std::string& filename) {
	std::ifstream file(filename);
	if (!file) {
		std::cerr << "Failed to open wave file.\n";
		return;
	}

	std::string line;
	std::vector<std::string> currentWave;

	while (std::getline(file, line)) {
		size_t start = line.find_first_not_of(" \t\r\n");
		if (start == std::string::npos) continue;

		std::string trimmed = line.substr(start);
		if (trimmed.empty()) continue;

		if (trimmed.rfind("WAVE", 0) == 0) {
			currentWave.clear();
		}
		else if (trimmed == "END") {
			if (!currentWave.empty()) {
				undeadWaves.push_back(currentWave);
			}
		}
		else {
			size_t pos = 0;
			while (pos < trimmed.size()) {
				while (pos < trimmed.size() && std::isspace(trimmed[pos])) ++pos;

				size_t end = pos;
				while (end < trimmed.size() && !std::isspace(trimmed[end])) ++end;

				if (end > pos) {
					std::string word = trimmed.substr(pos, end - pos);
					if (word == "BOSS") {
						pos = end;
						while (pos < trimmed.size() && std::isspace(trimmed[pos])) ++pos;

						size_t bossEnd = pos;
						while (bossEnd < trimmed.size() && !std::isspace(trimmed[bossEnd])) ++bossEnd;

						if (bossEnd > pos) {
							std::string bossType = trimmed.substr(pos, bossEnd - pos);
							currentWave.push_back("BOSS " + bossType);
							pos = bossEnd;
						}
						else {
							std::cerr << "BOSS type missing after BOSS keyword!\n";
						}
					}
					else {
						currentWave.push_back(word);
						pos = end;
					}
				}
			}
		}
	}
}

void GameManager::returnSurvivorsToBase(Base& base, Army& army) {
	for (size_t i = 0; i < army.getUnitCount(); ) {
		Unit* unit = army.getUnit(i);
		if (unit->isAlive()) {
			base.addUnit(unit);
			army.removeUnit(unit);
		}
		else {
			++i;
		}
	}
	army.removeDeadUnits();
}



void GameManager::handleCommand(const std::string& commandLine) {
	auto tokens = tokenizeCommand(commandLine);
	if (tokens.empty()) return;


	const std::string& command = tokens[0];

	if (command == "PREPARE") {
		std::cout << "Preparation mode enabled.\n";
		std::cout << "Use CREATE <unitname> to create units.\n";
		std::cout << "Use SELECT BOSS <bossname> to select a boss.\n";
		std::cout << "Use SELECT <unitname> <count> to select regular units.\n";
		std::cout << "When ready, use START to begin the duel.\n";
		std::cout << "Current Living Gold: " << livingBase.getGold() << "\n";
	}
	else if (command == "EXIT") {
		std::cout << "Exit the game? Save first? (yes/no): ";
		std::string choice;
		std::getline(std::cin, choice);
		if (choice == "yes") {
			std::cout << "Enter file name to save: ";
			std::string filename;
			std::getline(std::cin, filename);
			prepareToSave();
			if (saveGame(filename)) {
				std::cout << "Game saved successfully.\n";
			}
			else {
				std::cout << "Failed to save game. Units returned to base.\n";
			}
		}
		isGameRunning = false;

	}
	else if (command == "SAVE" && tokens.size() > 1) {
		prepareToSave();

		if (saveGame(tokens[1])) {
			std::cout << "Game saved to " << tokens[1] << "\n";
		}
		else {
			std::cout << "Failed to save game. Units returned to base.\n";
		}

	}
	else if (command == "LOAD" && tokens.size() > 1) {
		if (loadGame(tokens[1])) {
			std::cout << "Game loaded from " << tokens[1] << "\n";
		}
		else {
			std::cout << "Failed to load game.\n";
		}

	}
	else if (command == "RESTART") {
		restart();
		std::cout << "Game restarted.\n";

	}
	else if (command == "MENU") {
		displayMenu();

	}
	else if (command == "DUEL") {
		autoSelectUndeadUnits();

		currentDuel.setup(&livingArmy, &undeadArmy);
		currentDuel.fight();

		returnSurvivorsToBase(livingBase, livingArmy);
		returnSurvivorsToBase(undeadBase, undeadArmy);

		uint16_t result = currentDuel.getResult();

		if (result == 1) {
			++livingDuelWins;
			std::cout << "Living army wins this duel!\n";
			checkAndSpawnNextWave();
		}
		else if (result == 2) {
			++undeadDuelWins;
			std::cout << "Undead army wins this duel!\n";
		}
		else {
			std::cout << "The duel ended in a draw.\n";
		}

		uint16_t winner = checkWinCondition();
		if (winner == 1) {
			std::cout << "Living side has won the game!\n";
			isGameRunning = false;
		}
		else if (winner == 2) {
			std::cout << "Undead side has won the game!\n";
			isGameRunning = false;
		}
		livingBase.addGold(1000);
		undeadBase.addGold(1000);

	}
	else if (command == "CREATE" && (tokens.size() == 2 || tokens.size() == 3)) {
		const std::string& name = tokens[1];
		int count = 1;

		if (tokens.size() == 3) {
			if (!parseInt(tokens[2], count) || count <= 0) {
				std::cout << "Invalid unit count.\n";
				return;
			}
		}

		UnitType type = getUnitTypeFromString(name);
		int current = UnitCounter::getCurrentCount();
		int max = UnitCounter::getMaxCount();

		if (current + count > max) {
			std::cout << "Cannot create " << count << " units. Limit exceeded.\n";
			return;
		}

		int costPerUnit = getUnitGoldCost(type);
		int totalCost = costPerUnit * count;

		if (!livingBase.spendGold(totalCost)) {
			std::cout << "Not enough gold to create " << count << " " << name << "(s).\n";
			return;
		}

		int created = 0;
		for (int i = 0; i < count; ++i) {
			if (!UnitCounter::tryRegisterUnit(type)) {
				std::cout << "Reached unit limit during creation. Created " << created << " units.\n";
				break;
			}

			Unit* unit = UnitFactory::create(type);
			if (!unit) {
				std::cout << "Invalid unit type.\n";
				break;
			}

			livingBase.addUnit(unit);
			++created;
		}

		if (created > 0) {
			std::cout << "Created " << created << " " << name << "(s).\n";
		}
	}
	else if (command == "SELECT" && tokens.size() == 3 && tokens[1] == "BOSSNAME") {
		const std::string& bossName = tokens[2];
		auto bossNameMgr = &BossNameManager::getInstance();

		if (!bossNameMgr->isNameRegistered(bossName)) {
			std::cout << "Boss named \"" << bossName << "\" is not registered.\n";
			return;
		}

		bool found = false;
		for (size_t i = 0; i < livingBase.getUnitCount();) {
			Unit* unit = livingBase.getUnit(i);
			if (unit->isBoss() && unit->getName() == bossName) {
				livingBase.transferUnitToArmy(unit, livingArmy);
				found = true;
				std::cout << "Boss " << bossName << " selected for duel.\n";
				break;
			}
			else {
				++i;
			}
		}

		if (!found) {
			std::cout << "Boss named \"" << bossName << "\" not found in your base.\n";
		}
	}
	else if (command == "SELECT" && tokens.size() == 3 && tokens[1] == "BOSS") {
		const std::string& bossTypeStr = tokens[2];
		UnitType bossType = getUnitTypeFromString(bossTypeStr);

		if (!Unit::isBossStatic(bossType)) {
			std::cout << bossTypeStr << " is not a valid boss type.\n";
			return;
		}

		uint16_t allowedBosses = 1 + (livingDuelWins / 3);
		if (bossesCreated >= allowedBosses) {
			std::cout << "You can only select up to " << (int)allowedBosses << " boss(es) at this point.\n";
			return;
		}
		Unit* boss = UnitFactory::create(bossType);
		if (!boss) {
			std::cout << "Failed to create boss of type: " << bossTypeStr << "\n";
			return;
		}

		if (!boss->isBoss()) {
			std::cout << bossTypeStr << " is not marked as a boss unit.\n";
			delete boss;
			return;
		}
		for (size_t i = 0; i < livingBase.getUnitCount(); ++i) {
			Unit* unit = livingBase.getUnit(i);
			if (unit->isBoss() && unit->getName() == boss->getName()) {
				std::cout << "Boss " << boss->getName() << " is already in your base.\n";
				delete boss;
				return;
			}
		}
		livingBase.addUnit(boss);
		++bossesCreated;  
		std::cout << "Boss " << boss->getName() << " added to base for future duels.\n";
		}

	else if (command == "SELECT" && tokens.size() == 3 && tokens[1] != "BOSS") {
		const std::string& unitName = tokens[1];
		int count = 0;
		if (!parseInt(tokens[2], count) || count <= 0) {
			std::cout << "Invalid unit count.\n";
			return;
		}

		int selected = 0;
		for (size_t i = 0; i < livingBase.getUnitCount() && selected < count;) {
			Unit* unit = livingBase.getUnit(i);
			if (unit->getName() == unitName && !unit->isBoss()) {
				livingBase.transferUnitToArmy(unit, livingArmy);
				++selected;
			}
			else ++i;
		}

		if (selected == 0) {
			std::cout << "No matching units found.\n";
		}
		else {
			std::cout << "Selected " << selected << " " << unitName << "(s) for duel.\n";
		}
	}
	else if (command == "STATUS") {
		std::cout << "Living Gold: " << livingBase.getGold() << "\n";
		std::cout << "Undead Gold: " << undeadBase.getGold() << "\n";

	}
	else if (command == "COSTS") {
		UnitFactory::printLivingUnitCosts();

	}
	else {
		std::cout << "Unknown command. Type MENU to see available options.\n";
	}
}

