#pragma once

#include "UI.hpp"
#include "Player.hpp"
#include "SoundManager.hpp"

enum class GameState : int {
	Boot,
	MainMenu,
	InGame,
	Pause,
	GameOver
};

class World {
public:
	World();

	sf::Clock* time = nullptr;
	GameState currentState = GameState::Boot;
	GameState oldState = GameState::Boot;
	Entity* player = nullptr;
	sf::RenderWindow* window = nullptr;
	std::vector<Entity*> projectiles;
	std::vector<Entity*> enmProjectiles;
	std::vector<Entity*> enemies;
	std::vector<Entity*> fragments;
	int score = 0;

	bool collides(float x, float y);
	bool collidesWithWalls(float x, float y);
	bool collidesWithProjectiles(float x, float y);
	bool collidesWithEnemies(float x, float y);
	bool collidesWithFragments(float x, float y);

	void addEntity(Entity* entity, std::vector<Entity*> &list);
	void removeEntity(Entity* entity, std::vector<Entity*>& list);
	void update();
	void draw(sf::RenderWindow& window);
	void changeState(GameState nuState);
	void addScore(int v);
	void addResolution(int v);
	void reset();
	void quitGame();
};

extern World world;
