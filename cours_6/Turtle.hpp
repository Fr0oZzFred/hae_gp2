#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "CmdId.hpp"

class Turtle {
public:
	Turtle(float radius, sf::Vector2f startPos, float speed, sf::Color color = sf::Color::Green);

	void draw(sf::RenderWindow* win);
	void update();
	void Reset(); 
	void updateHead();
	void updateTrail(sf::Vector2f pos);
	void move();
	void moveForward(float pixels = 1);
	void moveBackward(float pixels = 1);
	void rotateRight(float degrees = 1);
	void rotateLeft(float degrees = 1);
	void setDrawTrail(bool b);
	void setDrawColor(sf::Color color);
	void setRecord(bool b);
	bool evaluate(float dt);
	
	std::vector<Cmd> commands;
	int index = 0;
private:
	sf::CircleShape body;
	sf::CircleShape head;
	sf::Color turtleColor;
	sf::Color trailColor = sf::Color::Red;
	sf::Transform trs;
	sf::Vector2f startPos;
	float speed;
	bool drawTrail = true;
	sf::VertexArray trail = sf::VertexArray(sf::Points, 0);
	bool record = false;
};