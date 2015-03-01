struct NPC
{
	NPC();
	NPC(std::string, unsigned int,unsigned int, sf::Vector2u, std::string);
	std::string name;
	sf::Vector2u m_pos;
	unsigned int id;
	unsigned int gid;
};
