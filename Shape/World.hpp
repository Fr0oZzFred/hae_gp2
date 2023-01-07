#pragma once

#include "Entities.hpp"
#include "UI.hpp"

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
	std::vector<Entity*> projectiles;
	std::vector<Entity*> enemies;
	bool collides(float x, float y);
	bool collidesWithWalls(float x, float y);
	bool collidesWithProjectiles(float x, float y);
	bool collidesWithEnemies(float x, float y);

	void addProjectile(Entity* entity);
	void addEnemies(Entity* entity);
	void removeEntity(Entity* entity);
	void update();
	void draw(sf::RenderWindow& window);
	void changeState(GameState nuState);
};

extern World world;
