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
	float shotRate = 1.0f;
	float shootTime = 0.0f;

	float range = 32.0f;
	int resolution = 3;
	float angle = 0.0f;

	float projectileColor[3] = { 0.0f, 0.0f, 0.0f };

	int shotPattern = 0;
	sf::ConvexShape* convexShape;

	auto getAngle(float a) {
		return sf::Vector2f(
			std::cos(a),
			std::sin(a)
		);
	};
	auto rotateVec2(sf::Vector2f input, sf::Vector2f rotation) {
		sf::Vector2f res(0, 0);
		res.x = input.x * rotation.x - input.y * rotation.y;
		res.y = input.x * rotation.y + input.y * rotation.x;
		return res;
	};

	Player() : Entity(sf::Vector2f(Game::WIDTH * 0.5f, Game::HEIGHT * 0.5f), new sf::ConvexShape()) {
		convexShape = (sf::ConvexShape*)this->shp;
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
	void addResolution(int value);
};