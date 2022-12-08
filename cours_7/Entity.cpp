#include "Entity.hpp"

Entity::Entity(sf::RectangleShape* _sprite, sf::Vector2f pixelPos, std::vector<Entity>* _entities) {
	sprite = _sprite;
	sprite->setOrigin(sprite->getSize() * 0.5f);
	setPixelCoordinates(pixelPos);
	entities = _entities;
	entities->push_back(*this);
}
void Entity::setPixelCoordinates(sf::Vector2f npos) {
	cx = (int)npos.x / Cst::CELL_SIZE;
	cy = (int)npos.y / Cst::CELL_SIZE;

	rx = (npos.x - (cx * Cst::CELL_SIZE)) / Cst::CELL_SIZE;
	ry = (npos.y - (cy * Cst::CELL_SIZE)) / Cst::CELL_SIZE;

	xx = (int)((cx + rx) * Cst::CELL_SIZE);
	yy = (int)((cy + ry) * Cst::CELL_SIZE);
};

void Entity::setGridCoordinates(sf::Vector2f npos) {
	setPixelCoordinates(sf::Vector2f(npos.x * Cst::CELL_SIZE, npos.y * Cst::CELL_SIZE));
};

void Entity::update() {
	rx += dx;
	ry += dy;

	dx *= fx;
	dy *= fy;

	falling =		!(hasCollision(cx, cy + 1));
	if (falling)	moveDown(weight * Cst::GRAVITY);

	while (rx > 1) {
		if (hasCollision(cx + 1, cy)) {
			rx--;
			dx = 0;
		}
		else {
			rx--;
			cx++;
		}
	}
	while (rx < 0) {
		if (hasCollision(cx - 1, cy)) {
			rx++;
			dx = 0;
		}
		else {
			rx++;
			cx--;
		}
	}
	while (ry > 1) {
		if (hasCollision(cx, cy + 1)) {
			ry--;
			dy = 0;
		}
		else {
			ry--;
			cy++;
		}
	}
	while (ry < 0) {
		if (hasCollision(cx, cy - 1)) {
			ry++;
			dy = 0;
		}
		else {
			ry++;
			cy--;
		}
	}

	//Sync grid to pixel
	xx = (int)((cx + rx) * Cst::CELL_SIZE);
	yy = (int)((cy + ry) * Cst::CELL_SIZE);
	sprite->setPosition(xx,yy);
};

bool Entity::hasCollision(int x, int y) {
	return world.collides(x, y);
};

void Entity::draw(sf::RenderWindow* win) {
	win->draw(*sprite);
}
void Entity::move(sf::Vector2f dir) {
	moveRight(dir.x);
	moveUp(dir.y);
};
void Entity::moveRight(float nudge) {
	rx += nudge;
};
void Entity::moveLeft(float nudge) {
	rx -= nudge;
};
void Entity::moveUp(float nudge) {
	ry -= nudge;
};
void Entity::moveDown(float nudge) {
	ry += nudge;
}
void Entity::jump() {
	if (falling) return;
	moveUp(10);
};

void Entity::im() {
	using namespace ImGui;

	DragFloat2("friction", &fx, 0.5, 0.001, 1);
	DragFloat2("dir", &dx);
	DragInt2("C coord", &cx);
	DragFloat2("R coord", &rx);
	DragFloat("Weight", &weight);
	Value("cx", cx);
	Value("cy", cy);
	Value("rx", rx);
	Value("ry", ry);
	Value("Pos X :", sprite->getPosition().x);
	Value("Pos X :", sprite->getPosition().y);
	Value("Falling", falling);

	float nudge = 1.0f;
	if (Button("C Right")) {
		moveRight(nudge);
	}
	if (Button("C Left")) {
		moveLeft(nudge);
	}
	if (Button("C Up")) {
		moveUp(nudge);
	}
	if (Button("C Down")) {
		moveDown(nudge);
	}
	if (Button("R Right")) {
		moveRight();
	}
	if (Button("R Left")) {
		moveLeft();
	}
	if (Button("R Up")) {
		moveUp();
	}
	if (Button("R Down")) {
		moveDown();
	}
	if (Button("Jump")) {
		jump();
	}
}
