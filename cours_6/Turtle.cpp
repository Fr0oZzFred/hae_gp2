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


	this->startPos = startPos;
	this->speed = speed;
};
void Turtle::draw(sf::RenderWindow* win) {
		win->draw(body);
		win->draw(head);
		win->draw(trail);
};
void Turtle::update() {
	setDrawTrail(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) setDrawColor(sf::Color::Red);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) setDrawColor(sf::Color::Magenta);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) setDrawColor(sf::Color::Cyan);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) Reset();
	move();
	updateHead();
};
void Turtle::move() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))		moveForward();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))		moveBackward();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	rotateRight();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		rotateLeft();
};
void Turtle::Reset() {
	trs = trs.Identity;
	body.setPosition(startPos);
	trs = trs.translate(body.getPosition());

	head.setPosition(body.getPosition() + sf::Vector2f(0, -head.getRadius() * 2.0f));

	trail.clear();

};
void Turtle::updateHead() {
	auto el = trs;
	sf::Transform transed = el.translate(sf::Vector2f(0, -head.getRadius() * 2.0f));
	auto elCenter = transed.transformPoint(sf::Vector2f(0, 0));
	head.setPosition(elCenter);
};
void Turtle::updateTrail(sf::Vector2f pos) {
	sf::Vertex p(pos, trailColor);
	trail.append(p);
};
void Turtle::moveForward(float pixels) {
	trs = trs.translate(sf::Vector2f(0, -pixels));
	body.setPosition(trs.transformPoint(sf::Vector2f(0, 0)));

	if(drawTrail) updateTrail(body.getPosition());
};
void Turtle::moveBackward(float pixels) {
	trs = trs.translate(sf::Vector2f(0, pixels));
	body.setPosition(trs.transformPoint(sf::Vector2f(0, 0)));
	if(drawTrail) updateTrail(body.getPosition());
};
void Turtle::rotateRight(float degrees) {
	trs = trs.rotate(degrees);
};
void Turtle::rotateLeft(float degrees) {
	trs = trs.rotate(-degrees);
};
void Turtle::setDrawTrail(bool b) {
	drawTrail = b;
};
void Turtle::setDrawColor(sf::Color color) {
	trailColor = color;
};
void Turtle::setRecord(bool b) {
	record = b;
};
bool Turtle::evaluate(float dt) {
	Cmd& task = commands[index];
	task.data -= dt;
	switch (task.id) {
		case CmdId::moveForward:
		moveForward(dt);
		break;
		case CmdId::moveBackward:
		moveBackward(dt);
		break;
		case CmdId::rotateLeft:
		rotateLeft(dt);
		break;
		case CmdId::rotateRight:
		rotateRight(dt);
		break;
		case CmdId::draw:
		task.data += dt;
		setDrawTrail(task.data);
		task.data -= dt;
		break;
		case CmdId::Reset:
		task.data += dt;
		Reset();
		break;
		default:
		break;
	}
	return task.data <= 0;
};