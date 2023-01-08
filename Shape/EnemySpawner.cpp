#include "EnemySpawner.hpp"

EnemySpawner enemySpawner;

EnemySpawner::EnemySpawner() {
}
void EnemySpawner::Spawn(Side side, float lerpPos) {
	world.addEnemy(new Enemy((Player*)world.player, SideToAreaPos(side, lerpPos)));
}
sf::Vector2f EnemySpawner::SideToAreaPos(Side side, float lerpPos) {
	switch (side) {
		case Side::Top:
			return Lib::lerp(sf::Vector2f(Game::AREA_MARGE_X(), Game::AREA_MARGE_Y()),					sf::Vector2f(Game::WIDTH - Game::AREA_MARGE_X(), Game::AREA_MARGE_Y()),					lerpPos);
		case Side::Right:
			return Lib::lerp(sf::Vector2f(Game::WIDTH - Game::AREA_MARGE_X(), Game::AREA_MARGE_Y()),	sf::Vector2f(Game::WIDTH - Game::AREA_MARGE_X(), Game::HEIGHT - Game::AREA_MARGE_Y()),	lerpPos);
		case Side::Bot:
			return Lib::lerp(sf::Vector2f(Game::AREA_MARGE_X(), Game::HEIGHT - Game::AREA_MARGE_Y()),	sf::Vector2f(Game::WIDTH - Game::AREA_MARGE_X(), Game::HEIGHT - Game::AREA_MARGE_Y()),	lerpPos);
		case Side::Left:
			return Lib::lerp(sf::Vector2f(Game::AREA_MARGE_X(), Game::AREA_MARGE_Y()),					sf::Vector2f(Game::AREA_MARGE_X(),				 Game::HEIGHT - Game::AREA_MARGE_Y()),	lerpPos);
		default:
			return sf::Vector2f(0, 0);
	}
};