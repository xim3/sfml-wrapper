#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include "EquipWindow.hpp"
#include "PlayerEquip.hpp"
#include "../MapSystem/StaticTiledMap.hpp"
#include "../Person/MemoryBridge.hpp"
#include "../Resources/Utils.hpp"
class DataWindow : public IWindow
{
public:
    DataWindow(sf::Vector2f,sf::Vector2u& , sf::Vector2i&, sf::Font* ,sf::Texture*, ItemManager&, TileMap&, IDataFormat&, unsigned int );
    int  underButton();
    bool intersects(sf::Vector2i&);
    bool getVisible() const;
    bool buttonHold(int);
    bool isVisible() const;
    void addButton(std::string);
    void setVisible(bool);
    void select();
    void update();
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    void setPlayerStats(std::unordered_map<std::string, unsigned int>* mem);
    void setMemoryManager(MemoryManager*);
    void equipRefresh();
    int  underSmallButton();
private:
    void smallButtonSelected();
    void drawPage();
    void drawEquip();
    void drawInfo();
    void drawSkills();
    void drawStats();
    void addSmallButton(int);
    bool checkCondition(Item);
    int  solveConditions(std::string);
    sf::Vector2i        &mouse;
    sf::Vector2u        &player_pos;
    sf::Font*           font;
    unsigned int        font_size;
    unsigned int        button_size_x, button_size_y;
    unsigned int        selectedPage;
    sf::RectangleShape  win;
    std::vector<sf::RectangleShape> pageButtons;
    std::vector<sf::RectangleShape> smallButton;
    std::vector<sf::Text>           smallButtonSign;
    std::vector<sf::Text>           buttonText;
    std::vector<sf::Text>           ad_data;
    EquipmentWindow     eq_0;
    sf::Clock           click_clock;
    ItemManager         &imgr;
    TileMap             &map;
    MemoryManager *mmgr = nullptr;
};
