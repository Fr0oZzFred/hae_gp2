#pragma once
#include "Enemy.hpp"
#include "World.hpp"
#include "Game.hpp"
#include "Lib.hpp"

enum class Side : int {
	Top,
	Right,
	Bot,
	Left
};

class EnemySpawner {
public:
	EnemySpawner();
	void Spawn(Side side, float lerpPos);
	sf::Vector2f SideToAreaPos(Side side, float lerpPos);
};

extern EnemySpawner enemySpawner;