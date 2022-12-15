#pragma once
#include "Entities.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>
class Player : public Entity {
public:

	float			frictX = 0.9f;
	float			frictY = 0.9f;

	float speed = 0.2f;

	Player() : Entity(sf::Vector2f(Game::WIDTH * 0.5f, Game::HEIGHT * 0.5f), new sf::RectangleShape(sf::Vector2f(24, 24))) {
		auto rect = (sf::RectangleShape*)this->shp;
		rect->setOrigin(12, 12);
		rect->setFillColor(sf::Color::Red);
	};
	void im();
	void update();
};