#pragma once
#include "Entities.hpp"
#include "Lib.hpp"
#include "World.hpp"
#include <iostream>

class Projectile : public Entity {
public:

	float speed = 0.001f;
	Projectile(Entity* entity, sf::Vector2f dir) : Entity(
		sf::Vector2f((entity->cx + entity->rx)* Cst::CELL_SIZE, (entity->cy + entity->ry)* Cst::CELL_SIZE),
		new sf::RectangleShape(sf::Vector2f(24, 12))) {

		shp->setRotation(Lib::lookAt(entity->shp->getPosition(),
			(sf::Vector2f)sf::Mouse::getPosition())
		);
		dir *= speed;
		this->dx = dir.x;
		this->dy = dir.y;
	};

	~Projectile() {
		std::cout << "Je suis delete";
	};
	void update();

private:

};