#include "Game.hpp"
#include "World.hpp"

World world;

World::World() {
}
bool World::collides(float x, float y) {
	if (x > Game::WIDTH / Cst::CELL_SIZE)	return true;
	if (y > Game::HEIGHT / Cst::CELL_SIZE)	return true;
	else if (x < 0)							return true;
	else if (y < 0)							return true;
	return false;
};