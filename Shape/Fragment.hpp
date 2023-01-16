#pragma once
#include "Entities.hpp"
#include <SFML/Graphics.hpp>
#include "World.hpp"

class Fragment : public Entity {
public:

	sf::FloatRect collider;
	float time = 15.0f;

	Fragment(sf::Vector2f pixelPos) : Entity(pixelPos, new sf::RectangleShape(sf::Vector2f(10, 10))) {
		shp->setFillColor(sf::Color::Yellow);
		collider.height = 10;
		collider.width = 10;
		collider.left = shp->getPosition().x - 5.0f;
		collider.top = shp->getPosition().y - 5.0f;
		shp->setOrigin(5, 5);
		shp->setRotation(45);
	};
	~Fragment() {
		std::cout << "fragment";
	};
	void update();

	bool collides(Entity* player);
};