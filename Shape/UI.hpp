#pragma once
#include <SFML/Graphics.hpp>
#include "UiElement.hpp"
#include "Data.hpp"

class UI {
public:
	UI() {};

	void add(UiElement* elem);
	void update();
	void im();
	void draw(sf::RenderWindow& window);
	void save();
	void load();
private:
	std::vector<UiElement*> elements;
};
extern UI ui;