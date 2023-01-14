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

	float speed = 7.0f;
	float shootTime = 0.0f;
	float currentShotRate = 0.15f;
	float shotRate = 1.0f;
	float triangleShotRate = 1.0f;
	float squareShotRate = 1.0f;
	float circleShotRate = 1.0f;

	float range = 32.0f;
	int resolution = 23;
	int displayedResolution = 23;
	float angle = 0.0f;

	float mainColor[3]		 = { 0.0f, 1.0f, 1.0f };
	float triangleColor[3]	 = { 0.0f, 1.0f, 0.0f };
	float squareColor[3]	 = { 1.0f, 0.0f, 1.0f };
	float circleColor[3]	 = { 1.0f, 0.0f, 0.0f };
	float currentColor[3]	 = { 0.0f, 0.0f, 0.0f };

	int shotPattern = 0;
	int upgradedPattern = 0;

	float skillTime = 0;
	float triangleDuration = 10.0f;
	float squareDuration = 7.5f;
	float circleDuration = 5.0f;

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
		activateSkill(0);
		updateShape();
		convexShape->setFillColor(sf::Color(mainColor[0] * 255.0f, mainColor[1] * 255.0f, mainColor[2] * 255.0f));
	};
	void im();
	void update();
	void updateShape();
	void shoot();
	void activateSkill(int index);
	void save();
	void save(FILE* file);
	void load();
	void load(FILE* file);
	void addResolution(int value);
	bool isCollided(float gx, float gy);
};