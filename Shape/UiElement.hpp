#pragma once
#include <SFML/Graphics.hpp>
#include "imgui.h"

enum class ElementType : int {
	ButtonType,

};

class UiElement {
public:

	ElementType type = ElementType::ButtonType;
	const char* name = "";

	int				cx = 0;
	int				cy = 0;

	float			rx = 0.0f;
	float			ry = 0.0f;


	//Resulting coord
	float			xx = 0.0f;
	float			yy = 0.0f;

	sf::Vector2f getGridPosition();
	void setPixelPos(sf::Vector2f npos);
	void setGridPos(sf::Vector2f npos);
	virtual void update() = 0;
	void baseUpdate();
	void updatePos();
	void syncPos();
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void im() = 0;
	virtual void save(FILE* file) = 0;
	virtual void load(FILE* file) = 0;
};