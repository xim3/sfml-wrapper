#include "Window.hpp"
#include "ItemGrid.hpp"
#include <SFML/Graphics.hpp>

class GridWindow : public Window
{
	public:
		GridWindow(sf::Texture*, sf::Texture*,sf::Vector2f, unsigned int,unsigned int,
				   unsigned int w_tile = 32, unsigned int h_tile = 32);
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void append(const unsigned int x,const unsigned int y, const unsigned int GID);
	private:
		ItemGrid grid;
};
