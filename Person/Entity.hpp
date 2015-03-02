#pragma once
#include "../AnimatedSprite/AnimatedTex.hpp"
#include <SFML/Graphics.hpp>
/**
 * \brief Klasa bytu, który może poruszać sie po mapie, i mieć animacje.
 */
class Entity : public sf::Drawable, public sf::Transformable
{
	public:
		Entity(unsigned int x=32, unsigned int y=32);
		bool load(const std::string path);
		void moveDown();
		void moveLeft();
		void moveRight();
		void moveUp();
		void update();
		void idle();
		void setPosition(unsigned int, unsigned int);
		void setPositionFloat(float,float);
		sf::Vector2u getPosition();
		sf::Vector2f getPositionFloat();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	protected:
		unsigned int tile_width  = 32;
		unsigned int tile_height = 32;
		/** * \brief Animacje */
		std::vector<Animation> anims;
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

};
