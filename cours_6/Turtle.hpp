#pragma once
#include <SFML/Graphics.hpp>

class Turtle {
public:
	Turtle(float radius, sf::Vector2f startPos, float speed, sf::Color color = sf::Color::Green);

	void draw(sf::RenderWindow* win);
	void update();
	void Reset();
private:
	sf::CircleShape body;
	sf::CircleShape head;
	sf::Color turtleColor;
	sf::Color trailColor = sf::Color::Red;
	sf::Transform trs;
	sf::Vector2f startPos;
	float speed;
	bool drawTrail;
	sf::VertexArray trail = sf::VertexArray(sf::Points, 0);

	void updateHead();
	void updateTrail(sf::Vector2f pos);
	void move();
	void moveForward(float pixels = 1);
	void moveBackward(float pixels = 1);
	void rotateRight(float degrees = 1);
	void rotateLeft(float degrees = 1);
	void setDrawtrail(bool b);
};