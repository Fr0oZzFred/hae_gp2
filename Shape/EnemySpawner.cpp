#include "EnemySpawner.hpp"

EnemySpawner enemySpawner;

EnemySpawner::EnemySpawner() {
};
void EnemySpawner::Spawn() {
	world.addEnemy(new Enemy((Player*)world.player, sf::Vector2f(0, 0)));
};