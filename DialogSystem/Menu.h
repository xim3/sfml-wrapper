#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu
{
    public:
        Menu(sf::Color default_, sf::Color second, int font_size);
        void draw(sf::RenderWindow &window);
        void move_pointer(bool up); //przesuwa pozycje 'wskaznika'
    private:
        sf::Font font;
        sf::Text header[3];
        int position; //aktualna pozycja wskaznika w menu, na tej podstawie zmienia sie kolor
        sf::Color colors[1];
        void clear_all(); //maluje fonty na drugi kolor pomijajac x
};

#endif // MENU_H
