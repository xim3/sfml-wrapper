#include "PopupMenu.hpp"
#include <utility>
PopupMenu::PopupMenu(sf::Font *f, sf::Vector2f pos, unsigned int f_size)
: visible(0)
, font(f)
, font_size(f_size)
, hoover(false)
{
    menu.setPosition(pos);
    menu.setFillColor(sf::Color::Black);
    menu.setOutlineThickness(1);
    menu.setOutlineColor(sf::Color::Blue);
}
void PopupMenu::addChoice(std::wstring t)
{
    std::pair<sf::RectangleShape, sf::Text> buf;
    sf::RectangleShape s(sf::Vector2f(menu.getPosition().x,menu.getPosition().y));
    s.setSize(sf::Vector2f(button_width, font_size + text_margin));
    s.setOutlineColor(sf::Color::Red);
    s.setOutlineThickness(1);
    s.setFillColor(sf::Color(50,50,50,200));
    s.setPosition(menu.getPosition().x + padding_button, (menu.getPosition().y + padding_button )+ (choices.size() * (font_size + text_margin)));
    std::get<0>(buf) = s;
    sf::Text tx;
    tx.setFont(*font);
    tx.setString(t);
    tx.setCharacterSize(font_size);
    tx.setPosition(s.getPosition().x + text_offset , s.getPosition().y);
    std::get<1>(buf) = tx;
    choices.push_back(buf);
    menu.setSize(sf::Vector2f(button_width+padding_button*2, (choices.size()) * (font_size + text_margin) + padding_button*2));
    menu.setFillColor(sf::Color::Black);
    menu.setOutlineThickness(1);
    menu.setOutlineColor(sf::Color::Blue);
}
bool PopupMenu::buttonHold(int n_msec)
{
    sf::Time time_button_hold;
    if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
    {
        time_button_hold += sf::Time(click_clock.getElapsedTime());
        if( time_button_hold > sf::milliseconds(n_msec) )
        {
            time_button_hold = sf::Time::Zero;
            click_clock.restart();
            return true;
        }
        else return false;
    }
    else
    {
        time_button_hold = sf::Time::Zero;
        click_clock.restart();
        return false;
    }
}
void PopupMenu::setPosition(sf::Vector2f pos)
{
    menu.setPosition(pos);
    unsigned int i=0;
    for(auto &choice : choices)
    {
        std::get<0>(choice).setPosition(menu.getPosition().x + padding_button
                 , (menu.getPosition().y + padding_button )+ (i * (font_size + text_margin)));
        std::get<1>(choice).setPosition(std::get<0>(choice).getPosition().x + text_offset , std::get<0>(choice).getPosition().y);
        ++i;
    }
}
sf::Vector2f PopupMenu::getPosition()
{
    return menu.getPosition();
}
int PopupMenu::underButton(sf::Vector2i& mouse)
{
    unsigned int i=0;
    for(auto button : choices)
    {
        int xbutt = std::get<0>(button).getPosition().x;
        int ybutt = std::get<0>(button).getPosition().y;
        if((mouse.x >= xbutt + padding_button && mouse.x <= xbutt + std::get<0>(button).getSize().x)
         &&(mouse.y >= ybutt + padding_button && mouse.y <= ybutt + std::get<0>(button).getSize().y))
              break;
        i++;
    }
    bool inters = intersects(mouse);
    if(visible && inters && i != choices.size())
        return i;
    else return -1;
}
void PopupMenu::highlightButton(int i)
{
    if(i != -1)
        std::get<0>(choices.at(i)).setFillColor(sf::Color::Green);
}

void PopupMenu::clean()
{
    for(auto &button : choices)
        std::get<0>(button).setFillColor(sf::Color(50,50,50,200));
}
void PopupMenu::setVisible(bool b)
{
    visible = b;
}
bool PopupMenu::isVisible() const
{
    return visible;
}
#include <iostream>
using namespace std;
void PopupMenu::refresh(sf::Vector2i& mouse)
{
    clean();
    highlightButton(underButton(mouse));
}
int PopupMenu::selectedOption(sf::Vector2i& mouse)
{
    clean();
    int selected = -1;
    if(intersects(mouse) && visible)
    {
        selected = underButton(mouse);
        if(selected != -1 && buttonHold(50))
        {
            std::cout << "SELECT\n";
            setVisible(false);
            return selected;
        }
    }
    return -1;
}
bool PopupMenu::intersects(sf::Vector2i& vct)
{
    if(visible)
    {
       if((vct.x >= menu.getPosition().x && vct.x <= (menu.getPosition().x + menu.getSize().x))
       && (vct.y >= menu.getPosition().y && vct.y <= (menu.getPosition().y + menu.getSize().y)))
       {
          hoover = true;
          return true;
       }
       hoover = false;
       return false;
    }
    return false;
}
void PopupMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
	states.texture = NULL;
    if(visible)
    {
        target.draw(menu, states);
        for(auto box : choices)
        {
            target.draw(std::get<0>(box),states);
            for(auto text : choices)
                target.draw(std::get<1>(box), states);
        }
    }
}
