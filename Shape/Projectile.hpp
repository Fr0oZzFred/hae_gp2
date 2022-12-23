#pragma once
#include "Entities.hpp"
#include "Lib.hpp"
#include "World.hpp"
#include "Game.hpp"
#include <iostream>

class Projectile : public Entity {
public:

	float speed = 0.1f;

	Projectile(Entity* entity, sf::Vector2f dir) : Entity(
		sf::Vector2f((entity->cx + entity->rx) * Game::CELL_SIZE, (entity->cy + entity->ry) * Game::CELL_SIZE),
		new sf::RectangleShape(sf::Vector2f(24, 12))) {

		shp->setOrigin(12, 6);

		shp->setRotation(Lib::lookAt(entity->shp->getPosition(),
			(sf::Vector2f)sf::Mouse::getPosition())
		);
		Lib::safeNormalize(dir);
		dir *= speed;
		this->dx = dir.x;
		this->dy = dir.y;
	};

	~Projectile() {
		std::cout << "projectile";
	};
	void update();
	bool collides();

private:

};