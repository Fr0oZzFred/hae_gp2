#pragma once

#include "Entity.hpp"

class World {
public:
	World();

	std::vector<sf::Vector2i>	statics;
	sf::VertexArray				staticGfx;
	bool collides(float gx, float gy);

	void mkGraphics();
	void poke(int gx, int gy);

	void draw(sf::RenderWindow& win);
};

extern World world;