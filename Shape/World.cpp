#include "Game.hpp"
#include "World.hpp"

World world;

World::World() {};
bool World::collides(float x, float y) {
	if (x > (Game::WIDTH - Game::AREA_X_SIDE()) / Game::CELL_SIZE)	return true;
	if (y > (Game::HEIGHT - Game::AREA_Y_SIDE()) / Game::CELL_SIZE)	return true;
	else if (x < Game::AREA_X_SIDE() / Game::CELL_SIZE)				return true;
	else if (y < Game::AREA_Y_SIDE() / Game::CELL_SIZE)				return true;
	return false;
};
void World::addEntity(Entity* entity) {
	entities.push_back(entity);
};
void World::removeEntity(Entity* entity) {
	for (auto iter = entities.begin(); iter != entities.end();) {
		if (*iter == entity) {
			iter = entities.erase(iter);
			delete entity;
			return;
		}
		else
			iter++;
	}
};
void World::update() {
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->update();
	}
};
void World::draw(sf::RenderWindow& window) {
	for (auto& entity : entities)	entity->draw(window);
};