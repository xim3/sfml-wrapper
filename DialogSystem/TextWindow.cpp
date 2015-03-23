#include "TextWindow.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "../Resources/easylogging++.h"
#include "../Resources/Utils.hpp"
TextWindow::TextWindow(sf::Vector2f pos, sf::Vector2f size,sf::Vector2i& _mouse, sf::Font* f, unsigned int f_size)
: mousev(_mouse)
, font(f)
, visible(true)
, font_size(f_size)
{
    win.setPosition(pos);
    win.setSize(size);
    win.setFillColor(sf::Color(50,50,50,200));
    setPosition(pos);
}
void TextWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(win);
    target.draw(npc_text);
    for(auto dial : dialogs)
        target.draw(dial);
}
bool TextWindow::intersects(sf::Vector2i& vct)
{
    if(visible)
    {
       if((vct.x >= getPosition().x && vct.x <= (getPosition().x + win.getSize().x))
       && (vct.y >= getPosition().y && vct.y <= (getPosition().y + win.getSize().y)))
       {
          hoover = true;
          return true;
       }
       hoover = false;
       return false;
    }
    return false;
}
int TextWindow::underAnwser(sf::Vector2i& vct, int start)
{
    int i = start;
    refresh();
    if( intersects(vct) )
    {
        for( auto &text : dialogs )
        {
            if( (vct.x >= text.getPosition().x && vct.x <= (getPosition().x + win.getSize().x))
             && (vct.y >= text.getPosition().y && vct.y <= text.getPosition().y+font_size     ) )
             {
                text.setColor(highlight_color);
                return i;
             }
             ++i;
        }
        return -1;
    }
    else return -1;
}
#include <iostream>
using namespace std;
bool TextWindow::buttonHold(int n_msec)
{
    sf::Time time_button_hold;
    if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
    {
        time_button_hold += sf::Time(click_clock.getElapsedTime());
        std::cout << time_button_hold.asMilliseconds() << std::endl;
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
int TextWindow::selectAnwser(int start)
{
    int anw = underAnwser(mousev,start);
    if( buttonHold(250) && anw != -1 )
        return anw;
    else
        return -1;
}
void TextWindow::refresh()
{
    for(auto &text : dialogs)
        text.setColor(idle_color);
}
void TextWindow::setVisible(bool v)
{
    visible = v;
}
void TextWindow::setHighlightColor(sf::Color hl)
{
    highlight_color = hl;
}
void TextWindow::setIdleColor(sf::Color i_c)
{
    idle_color = i_c;
}
bool TextWindow::isVisible()
{
    return visible;
}
void TextWindow::clear()
{
    dialogs.clear();
}
void TextWindow::setNPCString(std::wstring text)
{
    std::basic_string<sf::Uint32> utf32;
    utf32 = to32UTF<std::wstring>(L"NPC:");
    utf32 += to32UTF<std::wstring>(text);
    sf::Text _p;
    _p.setString(utf32);
    _p.setCharacterSize(font_size);
    _p.setColor(sf::Color::Red);
    _p.setFont(*font);
    _p.setPosition(win.getPosition().x, win.getPosition().y);
    npc_text = _p;

}
void TextWindow::addString(std::wstring text)
{
    std::basic_string<sf::Uint32> utf32;
    utf32 = to32UTF<std::wstring>(text);
    sf::Text _p;
    _p.setString(utf32);
    _p.setCharacterSize(font_size);
    _p.setFont(*font);
    size_t dial_size;
    if(dialogs.size() == 0)
    dial_size = 1;
    else
    dial_size = dialogs.size() + 1;
    _p.setPosition(win.getPosition().x, win.getPosition().y + font_size * dial_size);
    dialogs.push_back(_p);
}
