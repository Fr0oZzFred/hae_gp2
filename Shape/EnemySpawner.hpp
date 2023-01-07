#pragma once
#include "Enemy.hpp"
#include "World.hpp"

class EnemySpawner {
public:
	EnemySpawner();
	void Spawn();

};

extern EnemySpawner enemySpawner;