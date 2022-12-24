#pragma once
#include "UiElement.hpp"
#include "Game.hpp"

class Button : public UiElement {
public:
	sf::RectangleShape* box = nullptr;
	sf::Font content;

	Button() {
		setPixelPos(sf::Vector2f(1920/2, 1080/2));
		box = new sf::RectangleShape(sf::Vector2f(200.0f, 50.0f));
		box->setFillColor(sf::Color::White);
	};
	Button(sf::Vector2f pixelPos);

	void draw(sf::RenderWindow& window);
	void update();
	void im();
};