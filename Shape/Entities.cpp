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

void Entity::setPixelPos(sf::Vector2f npos) {
	cx = (int)npos.x / Cst::CELL_SIZE;
	cy = (int)npos.y / Cst::CELL_SIZE;

	rx = (npos.x - (cx * Cst::CELL_SIZE)) / Cst::CELL_SIZE;
	ry = (npos.y - (cy * Cst::CELL_SIZE)) / Cst::CELL_SIZE;

	xx = (int)((cx + rx) * Cst::CELL_SIZE);
	yy = (int)((cy + ry) * Cst::CELL_SIZE);
};

void Entity::setGridPos(sf::Vector2f npos) {
	setPixelPos(sf::Vector2f(npos.x * Cst::CELL_SIZE, npos.y * Cst::CELL_SIZE));
};

void Entity::update() {
	rx += dx;
	ry += dy;

	while (rx > 1) {
		if (collides(cx + 1, cy)) {
			rx--;
			dx = 0;
		}
		else {
			rx--;
			cx++;
		}
	}
	while (rx < 0) {
		if (collides(cx - 1, cy)) {
			rx++;
			dx = 0;
		}
		else {
			rx++;
			cx--;
		}
	}
	while (ry > 1) {
		if (collides(cx, cy + 1)) {
			ry--;
			dy = 0;
		}
		else {
			ry--;
			cy++;
		}
	}
	while (ry < 0) {
		if (collides(cx, cy - 1)) {
			ry++;
			dy = 0;
		}
		else {
			ry++;
			cy--;
		}
	}

	xx = (int)((cx + rx) * Cst::CELL_SIZE);
	yy = (int)((cy + ry) * Cst::CELL_SIZE);
	shp->setPosition(xx, yy);
};

void Entity::draw(sf::RenderWindow& win) {
	win.draw(*shp);
};

bool Entity::collides(float gx, float gy) {
	return world.collides(gx, gy);
};
