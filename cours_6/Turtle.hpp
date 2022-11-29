#pragma once
#include <SFML/Graphics.hpp>

class Turtle {
public:
	Turtle(float radius, sf::Vector2f startPos, float speed, sf::Color color = sf::Color::Green);

	void draw(sf::RenderWindow* win);
	void update(float dt);
	void move(float dt);
private:
	sf::CircleShape body;
	sf::CircleShape head;
	sf::Color turtleColor;
	sf::Transform trs;
	float speed;

	void updateHead();
	void moveForward(float pixels = 1);
	void moveBackward(float pixels = 1);
	void rotateRight(float degrees = 1);
	void rotateLeft(float degrees = 1);
};