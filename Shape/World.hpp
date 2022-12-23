#pragma once

#include "Entities.hpp"

class World{
public:
	World();

	bool collides(float x, float y);

	std::vector<Entity*> entities;

	void addEntity(Entity* entity);
	void removeEntity(Entity* entity);
	void update();
	void draw(sf::RenderWindow& window);
};

extern World world;
