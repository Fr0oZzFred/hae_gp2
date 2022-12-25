#pragma once
#include "UiElement.hpp"
#include "Game.hpp"
#include "Lib.hpp"

class Button : public UiElement {
public:
	sf::RectangleShape* box = nullptr;
	sf::Font text;

	float r = 1, g = 1, b = 1;

	Button() {
		Lib::Memcpy(name, "NewButton", 10);
		setPixelPos(sf::Vector2f(1920/2, 1080/2));
		box = new sf::RectangleShape(sf::Vector2f(200.0f, 50.0f));
	};
	Button(sf::Vector2f pixelPos);

	void draw(sf::RenderWindow& window);
	void update();
	void im();
	void save(FILE* file);
	void load(FILE* file);
};