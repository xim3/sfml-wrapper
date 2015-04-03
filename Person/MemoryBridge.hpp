#pragma once
#include "../Resources/Utils.hpp"
#include <unordered_set>
#include <string>

class MemoryManager : public IMemoryManager
{
public:
    MemoryManager();
    ~MemoryManager();
    void set(std::unordered_map<std::string, unsigned int>*);
    unsigned int get(std::string);

    bool hasFreepoints();
    bool shieldEquiped();
    bool bootsEquiped();
    bool pantsEquiped();
    bool helmetEquiped();
    bool weaponEquiped();
    bool armorEquiped();

    void wearShield(int);
    void wearBoots(int);
    void wearPants(int);
    void wearHelmet(int);
    void wearWeapon(int);
    void wearArmor(int);

    int  unwearShield();
    int  unwearBoots();
    int  unwearPants();
    int  unwearHelmet();
    int  unwearWeapon();
    int  unwearArmor();

    unsigned int  getFreepoints();
    unsigned int  getStrength();
    unsigned int  getWisdom();
    unsigned int  getCharisma();
    unsigned int  getEnergy();
    unsigned int  getVital();
    unsigned int  getAgility();
    unsigned int  getLevel();
    unsigned int  getExperience();

    unsigned int& freepoints();
    unsigned int& strength();
    unsigned int& wisdom();
    unsigned int& charisma();
    unsigned int& energy();
    unsigned int& vital();
    unsigned int& agility();
    unsigned int& level();
    unsigned int& experience();
private:
};
