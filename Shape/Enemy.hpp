#pragma once
#include "Entities.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Lib.hpp"
#include "World.hpp"
#include "Fragment.hpp"

class Enemy : public Entity {
public:

	float range = 32.0f;
	int resolution = 3;
	float dist = 0;

	auto getAngle(float a) {
		return sf::Vector2f(
			std::cos(a),
			std::sin(a)
		);
	};

	Enemy(sf::Vector2f pixelPos) : Entity(pixelPos, new sf::ConvexShape()) {
		auto rect = (sf::ConvexShape*)this->shp;
		rect->setPointCount(resolution);


		for (int i = 0; i < resolution; i++) {
			double t = (double)i / resolution;
			t *= 3.14159 * 2;
			rect->setPoint(i, getAngle(t) * range);
		}


		rect->setFillColor(sf::Color::Red);
		shp->setPosition(pixelPos);
	};

	~Enemy() {
		std::cout << "enemy";
	};
	void im();
	void update();
	void shoot();
	bool isCollided(float gx, float gy);
};