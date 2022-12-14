#pragma once

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"


struct Part{
	int					life = 0;
	sf::Vector2f		speed;
	sf::RectangleShape	shp = sf::RectangleShape(sf::Vector2f(4, 4));

	Part();
	Part(sf::Vector2f pos);

	void update();
	void draw(sf::RenderWindow& win);
	void drawInto(sf::VertexArray& va,sf::RenderWindow& win);
};

class PartController{
public:
	std::vector<Part>	data;
	sf::VertexArray		va;

	void add(sf::Vector2f pos);
	void update();
	void draw(sf::RenderWindow& win);
};
