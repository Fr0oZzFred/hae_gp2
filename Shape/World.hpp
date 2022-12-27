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
	std::vector<Entity*> entities;
	bool collides(float x, float y);

	void addEntity(Entity* entity);
	void removeEntity(Entity* entity);
	void update();
	void draw(sf::RenderWindow& window);
	void changeState(GameState nuState);
};

extern World world;
