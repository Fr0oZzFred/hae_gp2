#pragma once

#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

#include "Cst.hpp"

class State;

class Entity{
public:
	sf::Shape*		shp = nullptr;

	float			rx = 0.5f;//
	float			ry = 1.0f;

	float			dx = 0.0f;
	float			dy = 0.0f;

	float			frictX = 0.9f;
	float			frictY = 0.9f;

	int				cx = 0;
	int				cy = 0;

	float			stateLife = 0.0f;

	State*			currentState = nullptr;
	State*			idleState = nullptr;
	State*			walkState = nullptr;

	Entity(sf::Vector2f pixelPos, sf::Shape* shp);

	void setPixelPos(sf::Vector2f npos);
	void setGridPos(sf::Vector2f npos);

	void im();

	inline auto getLocalBounds() const {
		return shp->getLocalBounds();
	};
	
	inline auto getGlobalBounds() const {
		return shp->getGlobalBounds();
	};
	inline auto getPosition() const {
		return shp->getPosition();
	};
	
	inline void setPosition(const sf::Vector2f& v) {
		shp->setPosition(v);
	};
	
	void syncGridToPixel();
	void onEvent(sf::Event& e);
	void update();
	void draw(sf::RenderWindow& win);
	bool collides(float gx,float gy);

	void jumpControl(sf::Event& e);
	void walkControl();

	void changeState(State * st);
};
