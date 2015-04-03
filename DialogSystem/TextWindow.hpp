#pragma once
#include <SFML/Graphics.hpp>
#include "../Resources/Utils.hpp"
class TextWindow : public IWindow
{
public:
    TextWindow(sf::Vector2f, sf::Vector2f,sf::Vector2i&, sf::Font*, unsigned int f_size=15);
    bool intersects(sf::Vector2i&);
    bool isVisible() const;
    bool buttonHold(int);
    int  underAnwser(sf::Vector2i&,int);
    int  selectAnwser(int);
    void addString(std::wstring);
    void setNPCString(std::wstring);
    void setVisible(bool);
    void setHighlightColor(sf::Color);
    void setIdleColor(sf::Color);
    void update();
    void clear();
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
private:
    void refresh();
    sf::Vector2i          &mousev;
    std::vector<sf::Text> dialogs;
    sf::Text              npc_text;
    sf::RectangleShape    win;
    sf::Font*             font;
    bool                  hoover;
    bool                  visible;
    sf::Color             highlight_color = sf::Color::Green;
    sf::Color             idle_color      = sf::Color::White;
    sf::Clock             click_clock;
    int                   font_size;
};

