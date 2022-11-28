#pragma once

class Sphirograph {
public:
	Sphirograph(
		sf::Vector2f center, int* nbArms, vector<float>* armsLength, vector<double>* armsAngularVelocity,
		sf::Color armsColor, sf::Color drawColor
	);

	void update(float dt);
	void draw(sf::RenderWindow* window, bool drawArms);

private:
	sf::Vector2f center					= sf::Vector2f(0,0);
	int* nbArms							= nullptr;
	vector<float>* armsLength			= nullptr;
	vector<double>* armsAngularVelocity = nullptr;
	sf::Color armsColor					= sf::Color::Green;
	sf::Color drawColor					= sf::Color::Magenta;

	float time;
	sf::VertexArray arms				= sf::VertexArray();
	sf::VertexArray drawPoints			= sf::VertexArray(sf::Points, 0);
	void init(
		sf::Vector2f center, int* nbArms, vector<float>* armsLength, vector<double>* armsAngularVelocity,
		sf::Color armsColor, sf::Color drawColor
	);
	sf::Vector2f getAngle(float rad);
};