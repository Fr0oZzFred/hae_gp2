#pragma once
#include "Entities.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include "Lib.hpp"
#include "Projectile.hpp"

class Player : public Entity {
public:

	float			frictX = 0.9f;
	float			frictY = 0.9f;

	float speed = 0.2f;

	float range = 32.0f;
	int resolution = 3;
	float angle = 0.0f;


	auto getAngle(float a) {
		return sf::Vector2f(
			std::cos(a),
			std::sin(a)
		);
	};

	Player() : Entity(sf::Vector2f(Game::WIDTH * 0.5f, Game::HEIGHT * 0.5f), new sf::ConvexShape()) {
		auto rect = (sf::ConvexShape*)this->shp;
		rect->setPointCount(resolution);
		

		for (int i = 0; i < resolution; i++) {
			double t = (double)i / resolution;
			t *= 3.14159 * 2;
			rect->setPoint(i, getAngle(t) * range);
		}


		rect->setFillColor(sf::Color::Red);
	};
	void im();
	void update();
	void shoot();
};