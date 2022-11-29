#include "Turtle.hpp"

Turtle::Turtle(float radius, sf::Vector2f startPos, float speed, sf::Color color) {
	sf::CircleShape body(radius);
	body.setFillColor(color);
	body.setOrigin(radius, radius);
	body.setPosition(startPos);
	this->body = body;
	trs = trs.translate(body.getPosition());

	sf::CircleShape head(radius * 0.5f);
	head.setFillColor(sf::Color::Green);
	head.setOrigin(radius * 0.5f, radius * 0.5f);
	head.setPosition(body.getPosition() + sf::Vector2f(0, -radius));
	this->head = head;

	this->speed = speed;
};
void Turtle::draw(sf::RenderWindow* win) {
		win->draw(body);
		win->draw(head);
};
void Turtle::update(float dt) {
	move(dt);
	updateHead();
};
void Turtle::move(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))		moveForward		();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))		moveBackward	();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	rotateRight		();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		rotateLeft		();
};
void Turtle::updateHead() {
	auto el = trs;
	sf::Transform transed = el.translate(sf::Vector2f(0, -head.getRadius() * 2.0f));
	auto elCenter = transed.transformPoint(sf::Vector2f(0, 0));
	head.setPosition(elCenter);
};
void Turtle::moveForward(float pixels) {
	trs = trs.translate(sf::Vector2f(0, -pixels));
	body.setPosition(trs.transformPoint(sf::Vector2f(0, 0)));

};
void Turtle::moveBackward(float pixels) {
	trs = trs.translate(sf::Vector2f(0, pixels));
	body.setPosition(trs.transformPoint(sf::Vector2f(0, 0)));
};
void Turtle::rotateRight(float degrees) {
	trs = trs.rotate(degrees);
};
void Turtle::rotateLeft(float degrees) {
	trs = trs.rotate(-degrees);
};