#include "Menu.h"

Menu::Menu(sf::Color default_, sf::Color second, int font_size)
{
    position = 0;
    colors[0] = default_; colors[1] = second;
    font.loadFromFile("mariofont.ttf"); //nie wpisuj nic na sztywno..
    header[0].setString("Start"); header[1].setString("Informations"); header[2].setString("Exit");
    for(int x = 0; x < 3; x++)
    {
        header[x].setFont(font);
        header[x].setCharacterSize(font_size);
        header[x].setColor(default_);
    }
}

void Menu::draw(sf::RenderWindow& window)
{
    header[position].setColor(colors[1]);
    for(int b = 0; b < 3; b++)
    {
        header[b].setPosition(window.getSize().x / 2, window.getSize().y * (b * 0.07)); //magic numbers
    }
    for(int a = 0; a < 3; a++)
    {
        window.draw(header[a]);
    }
}

void Menu::move_pointer(bool up)
{
    if(up)
        --position;
    else
        ++position;

    this->clear_all();
    if(position == 0)
        header[0].setColor(colors[1]);
    else if(position == 1)
        header[1].setColor(colors[1]);
    else if(position == 2)
        header[2].setColor(colors[1]);
    else
    {
        if(position > 2)
            position = 0;
        else if(position < 0)
            position = 2;
        this->clear_all();
    }
}

void Menu::clear_all()
{
    for(int a = 0; a < 3; a++)
    {
        header[a].setColor(colors[0]);
    }

}
