#pragma once
#include "Enemy.hpp"
#include "World.hpp"
#include "Game.hpp"
#include "Lib.hpp"
#include "Data.hpp"
#include "SpawnEnemy.hpp"

enum class Side : int {
	Top,
	Right,
	Bot,
	Left
};


class EnemySpawner {
public:

	sf::Clock time;
	int idx = 0;
	bool enabled = false;

	std::vector<SpawnEnemy> enemies;
	SpawnEnemy enemy{ 0,0,0 };
	EnemySpawner();
	void Spawn(SpawnEnemy enm);
	void Spawn(Side side, float lerpPos);
	sf::Vector2f SideToAreaPos(Side side, float lerpPos);
	void checkSpawn();
	void restart();
	void stop();
	void update();
	void im();
	void save();
	void load();
	void load(const char* path);
	void add();
	void remove(int idx);
	void sort();
};

extern EnemySpawner enemySpawner;