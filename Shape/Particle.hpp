#pragma once
#include "Entities.hpp"
#include <SFML/Graphics.hpp>
#include "Lib.hpp"
#include "World.hpp"

class Particle : public Entity {
public:
	sf::RectangleShape rec[12];
	sf::Vector2f dir[12];
	int nb = 12;
	float maxScale = 4.0f;
	float t = 0;

	Particle(sf::Vector2f pixelPos, sf::Color color) : Entity(pixelPos, new sf::CircleShape(10.0f)) {
		shp->setOrigin(sf::Vector2f(10.0f,10.0f));
		shp->setOutlineColor(SFML_ORANGE);
		shp->setOutlineThickness(3);
		for (int i = 0; i < nb; i++) {
			rec[i].setSize(sf::Vector2f(10, 10));
			rec[i].setOrigin(sf::Vector2f(5, 5));
			rec[i].setPosition(pixelPos);
			rec[i].setFillColor(color);
			rec[i].setOutlineColor(SFML_ORANGE);
			rec[i].setOutlineThickness(0.5f);
			dir[i] = sf::Vector2f(std::cos(i * Lib::rand()), std::sin(i * Lib::rand()));
			rec[i].rotate(std::atan2(dir[i].x, dir[i].y));
		}
	};
	void update();
	void draw(sf::RenderWindow& win);
};