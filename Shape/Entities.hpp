#pragma once

#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <iostream>

class Entity {
public:
	sf::Shape*		shp = nullptr;

	int				cx = 0;
	int				cy = 0;

	float			rx = 0.0f;
	float			ry = 0.0f;


	//Resulting coord
	float			xx = 0.0f;
	float			yy = 0.0f;

	float			dx = 0.0f;
	float			dy = 0.0f;

	float collisionAccuracy = 0.1f;

	Entity(sf::Vector2f pixelPos, sf::Shape* shp);
	virtual ~Entity() {
		std::cout << " child of entity as been deleted" << "\n";
	}

	sf::Vector2f getGridPosition();
	void setPixelPos(sf::Vector2f npos);
	void setGridPos(sf::Vector2f npos);
	virtual void update();
	void baseUpdate();
	void updatePos();
	void syncPos();
	void draw(sf::RenderWindow& win);
	virtual bool collides(float gx,float gy);
	virtual bool isCollided(float gx, float gy);
	virtual void im();
	virtual void save();
	virtual void save(FILE* file);
	virtual void load();
	virtual void load(FILE* file);
};