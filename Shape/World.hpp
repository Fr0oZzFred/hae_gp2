#pragma once

#include "UI.hpp"
#include "Player.hpp"

enum class GameState : int {
	Boot,
	MainMenu,
	InGame,
	Pause
};

class World {
public:
	World();

	GameState currentState = GameState::Boot;
	Entity* player = nullptr;
	std::vector<Entity*> projectiles;
	std::vector<Entity*> enemies;
	std::vector<Entity*> fragments;
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
};

extern World world;
