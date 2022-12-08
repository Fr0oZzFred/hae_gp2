#pragma once
#include <SFML/Graphics.hpp>
#include "Cst.hpp"
#include "imgui.h"
#include "World.hpp"
#include <functional>

class Entity {
public:
	std::vector<Entity>* entities;

	//Graphics
	sf::RectangleShape* sprite;

	//Coordinates
	int cx = 0;
	int cy = 0;
	float rx = 0;
	float ry = 0;

	//Resulting coord
	float xx = 0.0f;
	float yy = 0.0f;

	//Movements
	float dx = 0.0f;
	float dy = 0.0f;
	float fx = 0.0f;
	float fy = 0.0f;

	float weight = 0.0f;

	Entity(sf::RectangleShape* _sprite, sf::Vector2f pixelPos, std::vector<Entity>* _entities);
	void setPixelCoordinates(sf::Vector2f npos);
	void setGridCoordinates(sf::Vector2f npos);
	void update();
	bool hasCollision(int x, int y);
	void draw(sf::RenderWindow* win);

	void move(sf::Vector2f dir);
	void moveRight(float nudge = 0.1f);
	void moveLeft(float nudge = 0.1f);
	void moveUp(float nudge = 0.1f);
	void moveDown(float nudge = 0.1f);
	void jump();

	void im();

	std::function<void()> currentState = std::bind(std::mem_fn(&Entity::idle), this);
	void idle();
	void idleNextWall();
	void falling();
	void moving();
	void checkH();
	void checkV();
};