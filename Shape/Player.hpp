#pragma once
#include "Entities.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include "Lib.hpp"
#include "Projectile.hpp"

class Player : public Entity {
public:

	float	frictX = 0.9f;
	float	frictY = 0.9f;

	float speed = 0.02f;

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
		auto convexShape = (sf::ConvexShape*)this->shp;
		convexShape->setPointCount(resolution);
		updateShape();

		convexShape->setFillColor(sf::Color::Cyan);
	};
	void im();
	void update();
	void updateShape();
	void shoot();
	void save();
	void save(FILE* file);
	void load();
	void load(FILE* file);
};