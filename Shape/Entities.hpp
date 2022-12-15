#pragma once

#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Cst.hpp"

class Entity {
public:
	sf::Shape*		shp = nullptr;

	int				cx = 0;
	int				cy = 0;

	float			rx = 0.5f;
	float			ry = 1.0f;


	//Resulting coord
	float			xx = 0.0f;
	float			yy = 0.0f;

	float			dx = 0.0f;
	float			dy = 0.0f;

	Entity(sf::Vector2f pixelPos, sf::Shape* shp);

	void setPixelPos(sf::Vector2f npos);
	void setGridPos(sf::Vector2f npos);
	void update();
	void draw(sf::RenderWindow& win);
	bool collides(float gx,float gy);
};
