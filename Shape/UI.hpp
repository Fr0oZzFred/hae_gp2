#pragma once
#include <SFML/Graphics.hpp>
#include "UiElement.hpp"
#include "Button.hpp"
#include "Data.hpp"

class UI {
public:
	UI() {};

	void add(UiElement* elem);
	void remove(UiElement* elem);
	void update();
	void im();
	void draw(sf::RenderWindow& window);
	void save();
	void load();
	void load(const char* path);
private:
	std::vector<UiElement*> elements;
};
extern UI ui;