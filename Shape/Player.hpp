#pragma once
#include "Entities.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>
class Player : public Entity {
public:

	float			frictX = 0.9f;
	float			frictY = 0.9f;

	float speed = 0.2f;

	float range = 64.0f;
	int resolution = 3;



	Player() : Entity(sf::Vector2f(Game::WIDTH * 0.5f, Game::HEIGHT * 0.5f), new sf::ConvexShape()) {
		auto rect = (sf::ConvexShape*)this->shp;
		rect->setPointCount(resolution);
		auto getAngle = [](float a) {
			//Inversed for having the first point up
			return sf::Vector2f(
				-std::sin(a),
				-std::cos(a)
			);
		};

		for (int i = 0; i < resolution; i++) {
			double t = (double)i / resolution;
			t *= 3.14159 * 2;
			rect->setPoint(i, getAngle(t) * range);
		}


		rect->setFillColor(sf::Color::Red);
	};
	void im();
	void update();
};