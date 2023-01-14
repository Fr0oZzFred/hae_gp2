#include "Game.hpp"
#include "World.hpp"
#include "EnemySpawner.hpp"

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
}
bool World::collidesWithFragments(float x, float y) {
	for (auto& entity : fragments)
		if (entity->isCollided(x, y)) return true;

	return false;
};
void World::addEntity(Entity* entity, std::vector<Entity*> &list) {
	list.push_back(entity);
};
void World::removeEntity(Entity* entity, std::vector<Entity*>& list) {
	for (auto iter = list.begin(); iter != list.end();) {
		if (*iter == entity) {
			iter = list.erase(iter);
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
			enemySpawner.update();
			player->update();
			for (int i = 0; i < projectiles.size(); i++)	projectiles[i]->update();
			for (int i = 0; i < enmProjectiles.size(); i++)	enmProjectiles[i]->update();
			for (int i = 0; i < enemies.size(); i++)		enemies[i]->update();
			for (int i = 0; i < fragments.size(); i++)		fragments[i]->update();
		break;
		case GameState::Pause:

		break;
		case GameState::GameOver:

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
			for (auto& entity : fragments)		entity->draw(window);
			for (auto& entity : enmProjectiles)	entity->draw(window);
			for (auto& entity : enemies)		entity->draw(window);
			player->draw(window);
		break;
		case GameState::Pause:
			for (auto& entity : projectiles)	entity->draw(window);
			for (auto& entity : fragments)		entity->draw(window);
			for (auto& entity : enmProjectiles)	entity->draw(window);
			for (auto& entity : enemies)		entity->draw(window);
			player->draw(window);
		break;
		case GameState::GameOver:

		break;
	}
};
void World::changeState(GameState nuState) {
	if (currentState == nuState) return;
	if (world.currentState != GameState::InGame && nuState == GameState::Pause) return;
	oldState = currentState;
	currentState = nuState;
	soundManager.playSound();
	switch (currentState) {
		case GameState::Boot:
			ui.load("res/boot.txt");
		break;
		case GameState::MainMenu:
			ui.load("res/mainMenu.txt");
		break;
		case GameState::InGame:
			if(oldState != GameState::Pause)
				enemySpawner.restart();
			ui.load("res/inGame.txt");
			addResolution(0);
			addScore(0);
		break;
		case GameState::Pause:
			ui.load("res/pause.txt");
		break;
		case GameState::GameOver:
			ui.load("res/gameOver.txt");
		break;
	}
};
void World::addScore(int v) {
	score += v;
	auto button = (Button*)ui.getText("Score");
	if (button != nullptr)
		button->setText(std::to_string(score).c_str());
};
void World::addResolution(int v) {
	Player* _player = (Player*)player;
	if (_player == nullptr) return;
	if (_player->resolution + v < 3) {
		changeState(GameState::GameOver);
		return;
	}
	_player->addResolution(v);
	auto button = (Button*)ui.getText("Resolution");
	if (button != nullptr)
		button->setText(std::to_string(_player->resolution).c_str());
}
void World::reset() {
	projectiles.clear();
	enmProjectiles.clear();
	enemies.clear();
	fragments.clear();
	score = 0;
	player->load();
	player->setPixelPos(sf::Vector2f(Game::WIDTH * 0.5f, Game::HEIGHT * 0.5f));
};
void World::quitGame() {
	window->close();
};