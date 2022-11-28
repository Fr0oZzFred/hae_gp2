using namespace std;
#include <SFML/Graphics.hpp>
#include <iostream>
#include "sphirograph.hpp"

//Public
Sphirograph::Sphirograph(
	sf::Vector2f center, int* nbArms, vector<float>* armsLength, vector<double>* armsAngularVelocity,
	sf::Color armsColor, sf::Color drawColor
) {
	init(center, nbArms, armsLength, armsAngularVelocity, armsColor, drawColor);
}
void Sphirograph::update(float dt) {
	time += dt;
	arms[0].position = center;
	for (int i = 1; i < *nbArms + 1; i++) {
		arms[i].position = arms[i - 1].position + getAngle(time * armsAngularVelocity->at(i - 1)) * armsLength->at(i - 1);
	}
	sf::Vertex point(arms[*nbArms]);
	point.color = drawColor;
	drawPoints.append(point);
};
void Sphirograph::draw(sf::RenderWindow* window, bool drawArms) {
	if(drawArms) window->draw(arms);
	window->draw(drawPoints);
};

//Private
void Sphirograph::init(
	sf::Vector2f center, int* nbArms, vector<float>* armsLength, vector<double>* armsAngularVelocity,
	sf::Color armsColor, sf::Color drawColor
) {
	this->center = center;
	this->nbArms = nbArms;
	this->armsLength = armsLength;
	this->armsAngularVelocity = armsAngularVelocity;
	this->armsColor = armsColor;
	this->drawColor = drawColor;
	this->arms = sf::VertexArray(sf::LineStrip, (*nbArms) + 1);
	for (int i = 0; i < *nbArms + 1; i++) {
		arms[i].color = armsColor;
	}
	update(0);
}
sf::Vector2f Sphirograph::getAngle(float rad) {
	return sf::Vector2f(-sin(rad), -cos(rad));
};