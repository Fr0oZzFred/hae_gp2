#pragma once
#include <SFML/Graphics.hpp>
#include "UiElement.hpp"
#include "Button.hpp"
#include "Data.hpp"

class UI {
public:
	UI() {};

	bool elementsChanged = false;

	void add(UiElement* elem);
	void remove(UiElement* elem);
	UiElement* getText(const char* buttonName);
	void update();
	void im();
	void draw(sf::RenderWindow& window);
	void save();
	void save(const char* path);
	void load();
	void load(const char* path);
private:
	std::vector<UiElement*> elements;
};
extern UI ui;