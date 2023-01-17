#pragma once
#include "Entities.hpp"
#include "Lib.hpp"
#include "World.hpp"
#include "Game.hpp"
#include <iostream>

class Projectile : public Entity {
public:

	float speed = 0.25f;
	int type = 0;

	//Type 0 = player proj, 1 = enmProj
	Projectile(Entity* entity, sf::Vector2f dir, sf::Color color, int _type) : Entity(
		//sf::Vector2f(entity->xx, entity->yy) + dir, C'est un truc un peu funky, pourrait faire un mix entre shotgun et rifle
		sf::Vector2f(entity->xx, entity->yy) + Lib::normalize(dir) * 30.0f,
		new sf::RectangleShape(sf::Vector2f(24, 12))) {
		shp->setOrigin(12, 6);

		shp->setRotation(Lib::lookAt(shp->getPosition(),
			dir)
		);

		Entity::baseUpdate();
		//Lib::safeNormalize(dir);
		dir *= speed;
		this->dx = dir.x;
		this->dy = dir.y;

		shp->setFillColor(color);
		type = _type;
	};

	//~Projectile() {
	//	std::cout << "projectile";
	//};
	void update();
	bool collides();
	bool isCollided(float gx, float gy);

private:

};