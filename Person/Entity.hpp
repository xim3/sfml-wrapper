#pragma once
#include "../AnimatedSprite/AnimatedTex.hpp"
#include <SFML/Graphics.hpp>
#include <map>
/**
 * \brief Klasa bytu, który może poruszać sie po mapie, i mieć animacje.
 */
enum DIR {D_LEFT,D_RIGHT,D_UP,D_DOWN};
class Entity : public sf::Drawable, public sf::Transformable
{
public:
    Entity(unsigned int x=32, unsigned int y=32);
    bool load(const std::string);
    void move(const std::string);
    void action(const std::string);
    void update();
    void idle();
    void setPosition(unsigned int, unsigned int);
    void setPositionFloat(float,float);
    sf::Vector2u getPosition() const;
    sf::Vector2i getPositionInt() const;
    sf::Vector2f getPositionFloat() const;
    sf::Vector2f getPositionFixed(DIR, float) const;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
protected:
    unsigned int tile_width  = 32;
    unsigned int tile_height = 32;
    /** * \brief Aktualna animacja */
    Animation *c_anim;
    /** * \brief Util*/
    AnimatedTex  anitex;
    /** * \brief Pozycja*/
    sf::Vector2f position;
    /** * \brief Tekstura*/
    sf::Texture  tiles;
    /** * \brief Szybkość przemieszczania się */
    float speed;
    /** * \brief Zegarek*/
    sf::Clock _clock;
    /** * \brief klawisz*/
    bool nokeypressed;
    /** * \brief Animacje */
    std::map<std::string, Animation> _anims;
};
