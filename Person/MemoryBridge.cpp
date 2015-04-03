#include "MemoryBridge.hpp"
MemoryManager::MemoryManager() : IMemoryManager(){}
MemoryManager::~MemoryManager()                  {}
void MemoryManager::set(std::unordered_map<std::string, unsigned int>* ptr)
{
    baseMemory = ptr;
}
unsigned int MemoryManager::get(std::string x)
{
    return baseMemory->at(x);
}
bool MemoryManager::hasFreepoints()
{
    return (baseMemory->at("freepoints") != 0)?(true):(false);
}
bool MemoryManager::shieldEquiped()
{
    return (baseMemory->at("shield") != 0)?(true):(false);
}
bool MemoryManager::bootsEquiped()
{
    return (baseMemory->at("boots") != 0)?(true):(false);
}
bool MemoryManager::pantsEquiped()
{
    return (baseMemory->at("pants") != 0)?(true):(false);
}
bool MemoryManager::helmetEquiped()
{
    return (baseMemory->at("helmet") != 0)?(true):(false);
}
bool MemoryManager::weaponEquiped()
{
    return (baseMemory->at("weapon") != 0)?(true):(false);
}
bool MemoryManager::armorEquiped()
{
    return (baseMemory->at("armor") != 0)?(true):(false);
}
void MemoryManager::wearShield(int id)
{
    if(shieldEquiped() == false) baseMemory->at("shield") = id;
}
void MemoryManager::wearBoots(int id)
{
    if(bootsEquiped() == false) baseMemory->at("boots") = id;
}
void MemoryManager::wearPants(int id)
{
    if(pantsEquiped() == false) baseMemory->at("pants") = id;
}
void MemoryManager::wearHelmet(int id)
{
    if(helmetEquiped() == false) baseMemory->at("helmet") = id;
}
void MemoryManager::wearWeapon(int id)
{
    if(weaponEquiped() == false) baseMemory->at("weapon") = id;
}
void MemoryManager::wearArmor(int id)
{
    if(armorEquiped() == false) baseMemory->at("armor") = id;
}
int  MemoryManager::unwearShield()
{
    if(shieldEquiped())
    {
        int s = baseMemory->at("shield");
        baseMemory->at("shield") = 0;
        return s;
    }
    return false;
}
int  MemoryManager::unwearBoots()
{
    if(bootsEquiped())
    {
        int s = baseMemory->at("boots");
        baseMemory->at("boots") = 0;
        return s;
    }
    return false;
}
int  MemoryManager::unwearPants()
{
    if(pantsEquiped())
    {
        int s = baseMemory->at("pants");
        baseMemory->at("pants") = 0;
        return s;
    }
    return false;
}
int  MemoryManager::unwearHelmet()
{
    if(helmetEquiped())
    {
        int s = baseMemory->at("helmet");
        baseMemory->at("helmet") = 0;
        return s;
    }
    return false;
}
int  MemoryManager::unwearWeapon()
{
    if(weaponEquiped())
    {
        int s = baseMemory->at("weapon");
        baseMemory->at("weapon") = 0;
        return s;
    }
    return false;
}
int  MemoryManager::unwearArmor()
{
    if(armorEquiped())
    {
        int s = baseMemory->at("armor");
        baseMemory->at("armor") = 0;
        return s;
    }
    return false;
}
unsigned int  MemoryManager::getFreepoints()
{
    return baseMemory->at("freepoints");
}
unsigned int  MemoryManager::getStrength()
{
    return baseMemory->at("strength");
}
unsigned int  MemoryManager::getWisdom()
{
    return baseMemory->at("wisdom");
}
unsigned int MemoryManager::getCharisma()
{
    return baseMemory->at("charisma");
}
unsigned int MemoryManager::getEnergy()
{
    return baseMemory->at("energy");
}
unsigned int MemoryManager::getVital()
{
    return baseMemory->at("vital");
}
unsigned int MemoryManager::getAgility()
{
    return baseMemory->at("agility");
}
unsigned int MemoryManager::getLevel()
{
    return baseMemory->at("level");
}
unsigned int MemoryManager::getExperience()
{
    return baseMemory->at("exp");
}
unsigned int&MemoryManager::freepoints()
{
    return baseMemory->at("freepoints");
}
unsigned int&MemoryManager::strength()
{
    return baseMemory->at("strength");
}
unsigned int&MemoryManager::wisdom()
{
    return baseMemory->at("wisdom");
}
unsigned int&MemoryManager::charisma()
{
    return baseMemory->at("charisma");
}
unsigned int&MemoryManager::energy()
{
    return baseMemory->at("energy");
}
unsigned int&MemoryManager::vital()
{
    return baseMemory->at("vital");
}
unsigned int&MemoryManager::agility()
{
    return baseMemory->at("agility");
}
unsigned int&MemoryManager::level()
{
    return baseMemory->at("level");
}
unsigned int&MemoryManager::experience()
{
    return baseMemory->at("experience");
}
