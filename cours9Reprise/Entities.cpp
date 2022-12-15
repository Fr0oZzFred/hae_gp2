#include "Entities.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "Lib.hpp"
#include "World.hpp"
#include "Game.hpp"
#include "imgui.h"
#include "State.hpp"

Entity::Entity(sf::Vector2f pixelPos, sf::Shape* shp) {
	this->shp = shp;
	
	setPixelPos(pixelPos);
	idleState = new StateIdle(this);
	walkState = new StateWalk(this);

	currentState = idleState;
}

void Entity::setPixelPos(sf::Vector2f npos) {
	cx = (int) npos.x / Cst::CELL_SIZE;
	cy = (int) npos.y / Cst::CELL_SIZE;

	//getthe fractionnal part
	rx = fmodf((npos.x / Cst::CELL_SIZE), 1.0f);
	ry = fmodf((npos.y / Cst::CELL_SIZE), 1.0f);

	int here = 0;
	shp->setPosition(npos);
}

void Entity::setGridPos(sf::Vector2f npos) {
	setPixelPos(sf::Vector2f(npos.x * Cst::CELL_SIZE, npos.y * Cst::CELL_SIZE));
}

void Entity::im() {
	using namespace ImGui;
	DragFloat2("frict", &frictX, 0.01,0.5,1.0);
	DragInt2("cx cy", &cx);
	DragFloat2("rx ry", &rx);
	Value("pos x", shp->getPosition().x);
	Value("pos y", shp->getPosition().y);
}

void Entity::syncGridToPixel() {
	float pxX = (cx + rx) * Cst::CELL_SIZE;
	float pxY = (cy + ry) * Cst::CELL_SIZE;
	shp->setPosition(sf::Vector2f((int)pxX,(int)pxY));
}

void Entity::onEvent(sf::Event &e ){
	currentState->onEvent(e);
}

void Entity::update() {

	currentState->updateState();

	rx += dx;
	ry += dy;

	dx *= frictX;
	dy *= frictY;

	bool needSync = true;
	while( rx > 1){
		if( collides( cx+1, cy) ){
			rx = 0.99f;
			dx = 0;
		}
		else {
			rx--;
			cx++;//shall we collide before crossing cell bound ?
		}
	}
	while(rx < 0) {
		if (collides(cx-1, cy)) {
			rx = 0;
			dx = 0;
		}
		else {
			rx++;
			cx--;//shall we collide before crossing cell bound ?
		}
	}
	while (ry > 1) {
		if (collides(cx, cy+1)) {
			ry = 0.99f;
			dy = 0;
		}
		else {
			ry--;
			cy++;//shall we collide before crossing cell bound ?
		}
	}
	while (ry < 0) {
		bool testFeet = collides(cx, cy - 1);
		bool testBody = collides(cx, cy - 2);
		bool testHead = collides(cx, cy - 3);
		if (testFeet|| testBody || testHead) {
			ry = 0.0f;
			dy = 0;
		}
		else {
			ry++;
			cy--;//shall we collide before crossing cell bound ?
		}
	}
	if (needSync)
		syncGridToPixel();
	stateLife++;
}

void Entity::draw(sf::RenderWindow& win) {
	win.draw(*shp);
}

bool Entity::collides(float gx, float gy) {
	return world.collides(gx, gy);
}

void Entity::walkControl() {
	sf::Vector2f dir(0, 0);
	float sp = 0.15f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		dir.x--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		dir.x++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		dir.y--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		dir.y++;
	float len = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (len) {
		dir.x /= len;
		dir.y /= len;
		dx += dir.x * sp;
		dy += dir.y * sp;
	}
}

void Entity::changeState(State* st) {
	st->onEnterState();
	currentState = st;
	stateLife = 0.0f;
}

void Entity::jumpControl(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Up
			|| event.key.code == sf::Keyboard::Space) {
			dy -= 1.5f;
		}
	}
}
