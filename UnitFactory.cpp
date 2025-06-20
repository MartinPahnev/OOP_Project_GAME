#include "UnitFactory.h"


void UnitFactory::printLivingUnitCosts()
{
    std::cout << std::endl;
    std::cout << "Infantry costs 250 gold.\n";
    std::cout << "Archer costs 300 gold.\n";
    std::cout << "Knight costs 700 gold.\n";
    std::cout << "Healer costs 150 gold.\n";
    std::cout << "Wizard costs 250 gold.\n";
}

Unit* UnitFactory::create(UnitType type)
{

    
    switch (type)
    {
    case UnitType::SKELETON:      return new Skeleton();
    case UnitType::GHOUL:         return new Ghoul();
    case UnitType::NECROMANCER:   return new Necromancer();
    case UnitType::ZOMBIE:        return new Zombie();
    case UnitType::DIBBUK:        return new Dibbuk();
    case UnitType::REVENANT:      return new Revenant();
    case UnitType::GHOST:         return new Ghost();

    case UnitType::INFANTRY:      return new Infantry();
    case UnitType::ARCHER:        return new Archer();
    case UnitType::KNIGHT:        return new Knight();
    case UnitType::HEALER:        return new Healer();
    case UnitType::WIZARD:        return new Wizard();

    case UnitType::LICH:          return new Lich();
    case UnitType::DARKLORD:      return new DarkLord();
    case UnitType::DEATHKNIGHT:   return new DeathKnight();

    case UnitType::UNDEADHUNTER:  return new UndeadHunter();
    case UnitType::BLADEDANCER:   return new Bladedancer();
    case UnitType::PALADIN:       return new Paladin();

    default:                      return nullptr;
    }
}