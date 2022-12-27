#include "Game.hpp"
#include "World.hpp"

World world;

World::World() {};
bool World::collides(float x, float y) {
	if (x > (Game::WIDTH  - Game::AREA_MARGE_X()) / Game::CELL_SIZE)	return true;
	if (y > (Game::HEIGHT - Game::AREA_MARGE_Y()) / Game::CELL_SIZE)	return true;
	else if (x < Game::AREA_MARGE_X() / Game::CELL_SIZE)				return true;
	else if (y < Game::AREA_MARGE_Y() / Game::CELL_SIZE)				return true;
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
	switch (currentState) {
	case GameState::Boot:

	break;
	case GameState::MainMenu:

	break;
	case GameState::InGame:
		for (int i = 0; i < entities.size(); i++)	entities[i]->update();
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
			for (auto& entity : entities)	entity->draw(window);
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