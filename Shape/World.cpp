#include "Game.hpp"
#include "World.hpp"

World world;

World::World() {};
bool World::collides(float x, float y) {
	if (collidesWithWalls(x, y))		return true;
	if (collidesWithProjectiles(x, y))	return true;
	if (collidesWithEnemies(x, y))		return true;
	return false;
}
bool World::collidesWithWalls(float x, float y) {
	if (x > (Game::WIDTH - Game::AREA_MARGE_X()) / Game::CELL_SIZE)	return true;
	if (y > (Game::HEIGHT - Game::AREA_MARGE_Y()) / Game::CELL_SIZE)	return true;
	else if (x < Game::AREA_MARGE_X() / Game::CELL_SIZE)				return true;
	else if (y < Game::AREA_MARGE_Y() / Game::CELL_SIZE)				return true;
	return false;
}
bool World::collidesWithProjectiles(float x, float y) {
	return false;
};
bool World::collidesWithEnemies(float x, float y) {
	for (auto& entity : enemies)
		if (entity->isCollided(x, y)) return true;

	return false;
};
void World::addProjectile(Entity* entity) {
	projectiles.push_back(entity);
}
void World::addEnemies(Entity* entity) {
	enemies.push_back(entity);
};
void World::removeEntity(Entity* entity) {
	for (auto iter = projectiles.begin(); iter != projectiles.end();) {
		if (*iter == entity) {
			iter = projectiles.erase(iter);
			delete entity;
			return;
		}
		else
			iter++;
	}
};
void World::update() {
	switch (currentState) {
	case GameState::Boot:

	break;
	case GameState::MainMenu:

	break;
	case GameState::InGame:
		for (int i = 0; i < projectiles.size(); i++)	projectiles[i]->update();
		for (int i = 0; i < enemies.size(); i++)		enemies[i]->update();
	break;
	case GameState::Pause:

	break;
	}
};
void World::draw(sf::RenderWindow& window) {
	switch (currentState) {
		case GameState::Boot:

		break;
		case GameState::MainMenu:

		break;
		case GameState::InGame:
			for (auto& entity : projectiles)	entity->draw(window);
			for (auto& entity : enemies)		entity->draw(window);
		break;
		case GameState::Pause:

		break;
	}
}
void World::changeState(GameState nuState) {
	if (currentState == nuState) return;
	currentState = nuState;
	switch (currentState) {
		case GameState::Boot:
			ui.load("res/boot.txt");
		break;
		case GameState::MainMenu:
			ui.load("res/mainMenu.txt");
		break;
		case GameState::InGame:
			ui.load("res/inGame.txt");
		break;
		case GameState::Pause:
			ui.load("res/pause.txt");
		break;
	}
};