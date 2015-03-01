class Person : public sf::Drawable, public sf::Transformable
{
	public:
		Person();
		bool load(const std::string path);
		void walkDown();
		void walkLeft();
		void walkRight();
		void walkUp();
		void update();
		void idle();
		void setPosition(unsigned int x, unsigned int y);
		void setTimerHandle(sf::Clock*);
		void setPositionHandle(sf::Vector2f*);
		void setKeyPressed(bool);
		sf::Vector2u getPosition();
		sf::Vector2f getPosition1();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	protected:
		unsigned int tile_width = 32;
		unsigned int tile_height = 32;
		std::vector<Animation> anims;
		Animation *c_anim;
		AnimatedTex  anitex;
		sf::Vector2f *position;
		sf::Texture  tiles;
		float speed;
		sf::Clock *_hnd;
		bool nokeypressed;

};

