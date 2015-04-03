#pragma once
#include "../Resources/Utils.hpp"
#include <SFML/Graphics.hpp>
class PopupMenu : public IWindow
{
public:
    PopupMenu(sf::Font*, sf::Vector2f, unsigned int);
    void addChoice(std::wstring);
    bool buttonHold(int);
    int  underButton(sf::Vector2i&);
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    bool intersects(sf::Vector2i&);
    void setPosition(sf::Vector2f);
    sf::Vector2f getPosition();
    int selectedOption(sf::Vector2i&);
    void highlightButton(int);
    void setVisible(bool);
    void refresh(sf::Vector2i&);
    bool isVisible() const;
private:
    bool visible;
    std::vector<std::pair<sf::RectangleShape, sf::Text>> choices;
    sf::RectangleShape menu;
    sf::Font          *font;
    unsigned int       font_size;
    void clean();
    bool               hoover;
    int padding_button = 2;
    int text_offset = 10;
    int text_margin = 3;
    int button_width = 100;
    sf::Clock          click_clock;
};
