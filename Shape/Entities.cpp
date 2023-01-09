#include "Entities.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "Lib.hpp"
#include "World.hpp"
#include "Game.hpp"
#include "imgui.h"

Entity::Entity(sf::Vector2f pixelPos, sf::Shape* shp) {
	this->shp = shp;
	setPixelPos(pixelPos);
};

sf::Vector2f Entity::getGridPosition() {
	return sf::Vector2f(cx + rx, cy + ry);
}

void Entity::setPixelPos(sf::Vector2f npos) {
	cx = (int)npos.x / Game::CELL_SIZE;
	cy = (int)npos.y / Game::CELL_SIZE;

	rx = (npos.x - (cx * Game::CELL_SIZE)) / Game::CELL_SIZE;
	ry = (npos.y - (cy * Game::CELL_SIZE)) / Game::CELL_SIZE;

	xx = (int)((cx + rx) * Game::CELL_SIZE);
	yy = (int)((cy + ry) * Game::CELL_SIZE);
};

void Entity::setGridPos(sf::Vector2f npos) {
	setPixelPos(sf::Vector2f(npos.x * Game::CELL_SIZE, npos.y * Game::CELL_SIZE));
}
void Entity::update() {};

void Entity::baseUpdate() {
	updatePos();
	syncPos();
}
void Entity::updatePos() {
	rx += dx;
	ry += dy;

	//Handle rx,ry
	while (rx > 1) {
		rx--;
		cx++;
	}
	while (rx < 0) {
		rx++;
		cx--;
	}
	while (ry > 1) {
		ry--;
		cy++;
	}
	while (ry < 0) {
		ry++;
		cy--;
	}
};

void Entity::syncPos() {
	xx = (int)((cx + rx) * Game::CELL_SIZE);
	yy = (int)((cy + ry) * Game::CELL_SIZE);

	shp->setPosition(xx, yy);
};

void Entity::draw(sf::RenderWindow& win) {
	win.draw(*shp);
};

bool Entity::collides(float gx, float gy) {
	return world.collides(gx, gy);
}
bool Entity::isCollided(float gx, float gy) {
	return false;
}
void Entity::im() {};
void Entity::save() {};
void Entity::save(FILE* file) {};
void Entity::load() {};
void Entity::load(FILE* file) {};
