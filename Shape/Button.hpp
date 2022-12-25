#pragma once
#include "UiElement.hpp"
#include "Game.hpp"
#include "Lib.hpp"

class Button : public UiElement {
public:
	//Button
	sf::RectangleShape* box = nullptr;
	float buttonColor[3] = { 1.0f, 1.0f ,1.0f };
	float sizeX = 200.0f, sizeY = 50.0f;
	sf::FloatRect collider;

	//Text
	sf::Font font;
	sf::Text text;
	float textColor[3] = { 0.0f, 0.0f ,0.0f };
	float fontSize = 10;
	float offsetX = 0.3f, offsetY = 0.3f;
	char content[128]{};
	

	Button() {
		Lib::Memcpy(name, "NewButton", 10);
		setPixelPos(sf::Vector2f(1920 * 0.5f, 1080 * 0.5f));
		box = new sf::RectangleShape(sf::Vector2f(sizeX, sizeY));
		box->setOrigin(box->getSize() * 0.5f);


		if(!font.loadFromFile("Ressources/depixel/DePixelBreitFett.ttf")) throw "Font not Found";
		text.setFont(font);
		text.setString("NewButton");
		text.setCharacterSize(fontSize);
		text.setOrigin(box->getOrigin());
	};

	void draw(sf::RenderWindow& window);
	void update();
	void im();
	void save(FILE* file);
	void load(FILE* file);
private:
	char _name[64] = {};
};